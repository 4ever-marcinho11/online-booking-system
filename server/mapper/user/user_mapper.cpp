//
// Created by Maximilian_Li on 2022/11/19.
//

#include "user_mapper.h"

/**
 * 构造函数，文件不存在或为空的时候创建文件并写入表头
 */
user_mapper::user_mapper() {
    ifstream ifs(user_source, ios::in);
    string line;
    getline(ifs, line);
    if (!ifs.good() || line.empty()) {
        // 新建文件，写入表头
        ofstream ofs(user_source, ios::out | ios::app);
        ofs << "id,name,age,sex,phone,is_auth" << endl;
        ofs.close();
    }
    ifs.close();
}

string user_mapper::select_one(string &id_searched) {
    ifstream ifs(user_source, ios::in);
    string line;
    while (std::getline(ifs, line)) {
        line = string_handler::change_separator(line);

        stringstream ss(line);
        string id_stored;
        ss >> id_stored;

        if (id_stored == id_searched) {
            string ret_str;
            ret_str += id_searched + "\t";
            string item;
            while (ss >> item) {
                ret_str += item + "\t";
            }

            return ret_str;
        }
    }

    string msg = "找不到 " + id_searched + " 的记录";
    cout << msg << endl;
    ifs.close();

    return "";
}

bool user_mapper::insert_one(user &u) {
    ofstream ofs(user_source, ios::app);
    if (!ofs.good()) {
        return false;
    }
    vector<string> v = u.to_vector();
    for (int i = 0; i < v.size() - 1; i++) {
        ofs << v[i] << ",";
    }
    ofs << v[v.size() - 1];
    ofs << endl;
    ofs.close();
    return true;
}

user_mapper::~user_mapper() = default;
