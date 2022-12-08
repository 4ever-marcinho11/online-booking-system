//
// Created by Maximilian_Li on 2022/11/30.
//

#include "user_service.h"

result user_service::usr_register(string &name, string &id, string &sex, string &phone, string &age, string& is_auth) {
    if (name.empty()) {
        return {0, "用户名为空"};
    }
    if (id.empty()) {
        return {0, "身份证号为空"};
    }
    if (phone.empty()) {
        return {0, "电话号码为空"};
    }
    if (sex.empty()) {
        return {0, "性别为空"};
    }
    if (age.empty()) {
        return {0, "年龄为空"};
    }

    user usr(id, name, sex, phone, std::stoi(age), std::stoi(is_auth));
    um.insert_one(usr);
    return {1, "注册成功"};
}

result user_service::usr_login(string &name, string &id) {
    string user_info = um.select_one(id);
    if (user_info.empty()) {
        return {0, "无法根据输入的身份证号找到对应用户信息"};
    }

    string _id_, _name_;
    stringstream ss(user_info);
    ss >> _id_ >> _name_;

    if (_name_ != name) {
        return {0, "无法根据输入的身份证号找到对应用户信息"};
    }

    // 清空表，向表中新增数据
    ofstream ofs(current_usr, ios::out);
    ofs << id << "," << name << endl;
    ofs.close();

    string user_str = um.select_one(id);

    return {1, user_str};
}

result user_service::usr_logout(string &id) {
    ifstream ifs(current_usr, ios::in);
    string line;
    while (std::getline(ifs, line)) {
        if (!line.empty()) {
            line = string_handler::change_separator(line);
            stringstream ss(line);
            string pk;
            ss >> pk;
            if (pk == id) {
                // 清空文件
                ofstream ofs(current_usr);
                ofs.close();
                return {1, "退出成功"};
            }
        }
    }
    return {0, "当前无登录用户，无需退出登录状态"};
}
