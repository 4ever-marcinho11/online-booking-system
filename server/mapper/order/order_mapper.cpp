//
// Created by Maximilian_Li on 2022/11/19.
//

#include "order_mapper.h"

order_mapper::order_mapper() {
    ifstream ifs(order_source, ios::in);
    string line;
    getline(ifs, line);
    if (!ifs.good() || line.empty()) {
        // 新建文件，写入表头
        ofstream ofs(order_source, ios::out | ios::app);
        ofs << "user_id,train_id,from,to,price,ticket_num, total_price" << endl;
        ofs.close();
    }
    ifs.close();
}

/**
 * 找到某一用户所有订单
 * @param user_id 用户身份证号
 * @return 所有订单
 */
vector<string> order_mapper::select_all(string &user_id) {
    vector<string> result;

    ifstream ifs(order_source, ios::in);
    string line;

    if (!ifs.good()) {
        cout << "something wrong when reading from order.csv" << endl;
        cout << "try to make sure that this file is valid." << endl;
        return result;
    }

    std::getline(ifs, line);
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        } else {
            line = string_handler::change_separator(line);
            stringstream ss(line);
            string col_0;
            ss >> col_0;

            if (col_0 == user_id) {
                result.push_back(line);
            }
        }
    }

    ifs.close();
    return result;
}

/**
 * 找一条订单记录
 * @param user_id 用户身份证号
 * @param train_id 火车编号
 * @param at 出发站
 * @param to 到达站
 * @return 记录
 */
string order_mapper::select_one(string &user_id, string &train_id) {
    string result;

    ifstream ifs(order_source, ios::in);
    string line;

    if (!ifs.good()) {
        cout << "在读取 order.csv 时发生异常" << endl;
        cout << "请先检查文件路径是否准确" << endl;
        return {};
    }

    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        } else {
            line = string_handler::change_separator(line);
            stringstream ss(line);
            string user, train;
            ss >> user >> train;

            if (user == user_id && train == train_id) {
                result += line;
                return result;
            }
        }
    }

    ifs.close();
    return {};
}

bool order_mapper::insert_one(order &o) {
    ofstream ofs(order_source, ios::app);
    if (!ofs.good()) {
        return false;
    }
    vector<string> v = o.to_vector();
    for (int i = 0; i < v.size() - 1; i++) {
        ofs << v[i] << ",";
    }
    ofs << v[v.size() - 1];
    ofs << endl;
    ofs.close();
    return true;
}

bool order_mapper::delete_one(order &o) {
    // 读原文件
    ifstream ifs(order_source, ios::in);
    // 写新文件
    string temp = "D:/coding/cpp/codes/learning/online-booking-system/data-source/temp.csv";
    ofstream ofs(temp, ios::app);

    string line;
    while (std::getline(ifs, line)) {
        if (!line.empty()) {
            // l是\t分隔，line是,分隔
            string_handler::change_separator(line);

            // 把表头写入temp
            stringstream ss(line);
            string s;
            ss >> s;
            if (s == "user_id") {
                string_handler::recover_separator(line);
                ofs << line << endl;
                continue;
            }

            order *o_ptr = order::from_string(line);
            if (*o_ptr != o) {
                // 将其他信息写入temp
                string_handler::recover_separator(line);
                ofs << line << endl;
            }

            delete o_ptr;
        }
    }

    ifs.close();
    ofs.close();

    // 给新文件改名为原文件的名字
    remove(order_source.c_str());
    if (0 == rename(temp.c_str(), order_source.c_str())) {
        return true;
    } else {
        return false;
    }
}

