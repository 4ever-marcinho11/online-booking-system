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
        error_page(0);
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
    r = uc._register(name, id, sex, phone, age);
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
    if (r.getCode() == 1) {
        cout << "登录成功" << endl;
        // 缓存用户身份信息
        id_buf = r.getMsg();
        base_page();
    } else {
        cout << "登录失败" << endl;
        welcome_page();
    }
}

void user_cli::base_page() {
    cout << endl;
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
            error_page(1);
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

    base_page();
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
    cout << "本次花费为：" << price << endl;

    r = oc._create(id_buf, train_id, from, to, ticket_nums);
    cout << r.getMsg() << endl;

    base_page();
}

void user_cli::view_orders() {
    r = oc._view(id_buf);
    for (auto &a: r.getVec()) {
        cout << a << endl;
    }

    base_page();
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
    base_page();
}

void user_cli::logout() {
    r = uc._logout(id_buf);
    if (r.getCode() == 0) {
        base_page();
    } else {
        welcome_page();
    }
}

void user_cli::error_page(int flag) {
    cout << "\n输入有误，正在重定向至主页..." << endl;
    sleep(3);
    flag == 0 ? welcome_page() : base_page();
}

void user_cli::sleep(int seconds) {
    clock_t delay = seconds * CLOCKS_PER_SEC;
    clock_t start = clock();
    while (clock() - start < delay);
}
