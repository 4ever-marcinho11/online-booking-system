//
// Created by Maximilian_Li on 2022/12/4.
//

#include "user_cli.h"

void user_cli::welcome_page() {
    cout << "\n您好，欢迎使用在线订票系统!" << endl;
    cout << "如果已有帐户，请先登录；若没有账户，请先注册" << endl;
    cout << "登录(i)，注册(r)，退出(exit) >> ";

    string in;
    cin >> in;

    if (in == "i") {
        login_page();
    } else if (in == "r") {
        register_page();
    } else if (in == "exit") {
        return;
    } else {
        error_page(0, 2);
    }
}

void user_cli::register_page() {
    string name, id, phone, sex, age;
    cout << "\n请输入姓名：";
    cin >> name;
    cout << "请输入身份证号：";
    cin >> id;
    cout << "请输入电话号码：";
    cin >> phone;
    cout << "请输入性别(female/male)：";
    cin >> sex;
    cout << "请输入年龄：";
    cin >> age;

    // 默认注册用户均为非管理员
    string default_mode = "0";
    r = uc._register(name, id, sex, phone, age, default_mode);
    if (r.getCode() == 1) {
        cout << "注册成功，请进行登录" << endl;
        login_page();
    } else {
        cout << "注册失败" << endl;
        welcome_page();
    }
}

void user_cli::login_page() {
    string id, name;
    cout << "\n请输入姓名：";
    cin >> name;
    cout << "请输入身份证号：";
    cin >> id;

    r = uc._login(id, name);
    string user_str = r.getMsg();
    user *usr = user::from_string(user_str);
    int is_auth = usr->getIsAuth();

    if (r.getCode() == 1) {
        cout << "登录成功" << endl;
        // 缓存用户身份信息
        id_buf = usr->getId();

        if (is_auth == 0) {
            delete usr;
            user_page();
        } else {
            delete usr;
            auth_page();
        }
    } else {
        cout << "登录失败" << endl;
        welcome_page();
    }
}

void user_cli::user_page() {
    string user_str = um.select_one(id_buf);
    if (user_str.empty()) {
        cout << "用户信息有误" << endl;
    }
    stringstream ss(user_str);
    string name;
    ss >> name >> name;
    cout << "用户：" << name << "，您好！" << endl;

    cout << "-------------------" << endl;
    cout << " * 搜索火车信息(s)" << endl;
    cout << " * 创建订单信息(c)" << endl;
    cout << " * 查看订单信息(v)" << endl;
    cout << " * 撤销订单信息(r)" << endl;
    cout << " * 退出本次登录(o)" << endl;
    cout << "-------------------" << endl;

    char in;
    cout << "请输入您的操作：";
    cin >> in;
    switch (in) {
        case 's':
            search_trains();
            break;
        case 'c':
            create_order();
            break;
        case 'v':
            view_orders();
            break;
        case 'r':
            remove_order();
            break;
        case 'o':
            logout();
            break;
        default:
            error_page(1, 3);
            break;
    }
}

void user_cli::search_trains() {
    cout << "\n请输入起点：";
    cin >> from;
    cout << "请输入终点：";
    cin >> to;

    r = tc._list(from, to);
    if (r.getCode() == 0) {
        cout << r.getMsg() << endl;
    } else {
        vector<string> trains = r.getVec();
        for (auto &a: trains) {
            // 记录余票上限
            train *t = train::from_string(a);
            string train_id = t->getId();
            int remain = t->getRemain();
            tic_remain_map[train_id] = remain;

            cout << a << endl;
            delete t;
        }
    }

    user_page();
}

void user_cli::create_order() {
    string train_id;
    int ticket_nums;
    cout << "\n请输入您想购买的火车车次号：";
    cin >> train_id;
    cout << "请输入购买数目：";
    cin >> ticket_nums;


    r = tc._price(train_id, from, to);
    int price = r.getVal();
    cout << "本次花费为：" << price * ticket_nums << endl;

    r = oc._create(id_buf, train_id, from, to, ticket_nums);
    cout << r.getMsg() << endl;

    user_page();
}

void user_cli::view_orders() {
    cout << endl;
    r = oc._view(id_buf);
    for (auto &a: r.getVec()) {
        cout << a << endl;
    }

    user_page();
}

void user_cli::remove_order() {
    string in;
    cout << "\n请确认您是否需要撤销订单(是：y，否：其它任意键) >> ";
    cin >> in;
    if (in == "y") {
        cout << "请输入您要删除的订单中的列车号：";
        in.clear();
        cin >> in;
        r = oc._remove(id_buf, in);
        cout << r.getMsg() << endl;
    }
    user_page();
}

void user_cli::logout() {
    cout << endl;
    r = uc._logout(id_buf);
    if (r.getCode() == 0) {
        user_page();
    } else {
        welcome_page();
    }
}

void user_cli::error_page(int flag, int sec) {
    cout << "\n输入有误，正在重定向至主页..." << endl;
    sleep(sec);
    if (flag == 0) {
        welcome_page();
    } else if (flag == 1) {
        user_page();
    } else if (flag == 2) {
        auth_page();
    }
}

void user_cli::sleep(int seconds) {
    clock_t delay = seconds * CLOCKS_PER_SEC;
    clock_t start = clock();
    while (clock() - start < delay);
}

void user_cli::auth_page() {
    cout << endl;
    string auth_str = um.select_one(id_buf);
    if (auth_str.empty()) {
        cout << "管理员信息有误" << endl;
    }
    stringstream ss(auth_str);
    string name;
    ss >> name >> name;
    cout << "管理员：" << name << "，您好！" << endl;

    cout << "-------------------" << endl;
    cout << " * 查看当前收益(r)" << endl;
    cout << " * 新增一列列车(a)" << endl;
    cout << " * 删除列车信息(d)" << endl;
    cout << " * 退出本次登录(o)" << endl;
    cout << "-------------------" << endl;

    char in;
    cout << "请输入您的操作：";
    cin >> in;
    switch (in) {
        case 'r':
            revenue();
            break;
        case 'a':
            add_train();
            break;
        case 'd':
            remove_train();
            break;
        case 'o':
            logout();
            break;
        default:
            error_page(1, 3);
            break;
    }
}

void user_cli::revenue() {
    cout << endl;
    r = oc._revenue();
    cout << "当前系统总收入为：" << r.getLongVal() << " 元" << endl;
    auth_page();
}

void user_cli::add_train() {
    cout << endl;

    string tid, dep, arr;
    int year, month, day, hour, minute, remain;

    cout << "请输入列车编号：";
    cin >> tid;

    cout << "请输入始发站：";
    cin >> dep;

    cout << "请输入终点站：";
    cin >> arr;

    cout << "请输入出发年份：";
    cin >> year;

    cout << "请输入出发月份：";
    cin >> month;

    cout << "请输入出发日期：";
    cin >> day;

    cout << "请输入出发时间：";
    cin >> hour;

    cout << "请输入出发分钟：";
    cin >> minute;

    string dep_time = time_handler::aggregate(year, month, day, hour, minute, 0);

    cout << "请输入持续小时：";
    cin >> hour;
    cout << "请输入持续分钟：";
    cin >> minute;

    string arr_time = time_handler::aggregate(year, month, day, hour, minute, 0);

    cout << "请输入空余座位上限：";
    cin >> remain;

    train tr(tid, dep, arr, dep_time, arr_time, remain);
    r = tc._add(tr);
    cout << r.getMsg();

    auth_page();
}

void user_cli::remove_train() {
    cout << endl;
    cout << "所有列车信息如下：" << endl;
    r = tc._see_all();
    if (r.getCode() == 0) {
        cout << r.getMsg() << endl;
    } else {
        vector<string> res = r.getVec();
        for (auto &a: res) {
            cout << a << endl;
        }
    }

    string flag;
    cout << "请输入是否需要删除指定列车信息(y/n)：";
    cin >> flag;

    if (flag == "y" | flag == "Y") {
        string tid;
        cout << "请输入列车编号：";
        cin >> tid;

        r = tc._remove(tid);
        cout << r.getMsg() << endl;
        auth_page();
    } else if (flag == "n" | flag == "N") {
        cout << "没有修改任何信息" << endl;
        auth_page();
    } else {
        cout << "输入有误" << endl;
        error_page(2, 3);
    }
}
