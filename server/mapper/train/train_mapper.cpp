//
// Created by Maximilian_Li on 2022/11/12.
//
#include "train_mapper.h"

train_mapper::train_mapper() {
    ifstream ifs(train_source, ios::in);
    string line;
    getline(ifs, line);
    if (!ifs.good() || line.empty()) {
        // 新建文件，写入表头
        ofstream ofs(train_source, ios::out | ios::app);
        ofs << "train_id,from,to,depart_time,arrive_time,remain" << endl;
        ofs.close();
    }
    ifs.close();
}

bool train_mapper::insert_a_train(train &t) {
    ofstream ofs(train_source, ios::app);
    if (!ofs.good()) {
        return false;
    }
    vector<string> v = t.to_vector();
    for (int i = 0; i < v.size() - 1; i++) {
        ofs << v[i] << ",";
    }
    ofs << v[v.size() - 1];
    ofs << endl;
    ofs.close();


    // 向stations中添加起始站
    ofstream ofs_sta(station_source, ios::app);
    string line;
    line += t.getId();
    line += ",";
    line += t.getSrc();
    line += ",";
    line += t.getDst();
    ofs_sta << line << endl;
    ofs_sta.close();

    return true;
}

bool train_mapper::insert_trains(vector<train> &ts) {
    ofstream ofs(train_source, ios::app);
    if (!ofs.good()) {
        return false;
    }

    for (auto &t: ts) {
        vector<string> v = t.to_vector();
        for (int i = 0; i < v.size() - 1; i++) {
            ofs << v[i] << ",";
        }
        ofs << v[v.size() - 1];
        ofs << endl;
    }

    ofs.close();
    return true;
}

bool train_mapper::delete_a_train(string &train_id) {
    // 列车
    ifstream ifs(train_source, ios::in);
    string temp = "D:/coding/cpp/codes/learning/online-booking-system/data-source/temp.csv";
    ofstream ofs(temp, ios::app);

    string t_str = select_a_train(train_id);
    train *t = train::from_string(t_str);

    string line;
    while (std::getline(ifs, line)) {
        string_handler::change_separator(line);

        // 表头
        stringstream ss(line);
        string s;
        ss >> s;
        if (s == "train_id") {
            string_handler::recover_separator(line);
            ofs << line << endl;
            continue;
        }

        // 数据
        train *t_ptr = train::from_string(line);
        if (*t_ptr != *t) {
            // 将原数据写入temp
            string_handler::recover_separator(line);
            ofs << line << endl;
        }

        delete t_ptr;
    }
    delete t;

    ifs.close();
    ofs.close();

    remove(train_source.c_str());
    if (0 == rename(temp.c_str(), train_source.c_str())) {
        // 站点
        ifstream ifs_sta(station_source, ios::in);
        ofstream ofs_sta(temp, ios::app);

        line.clear();
        while (std::getline(ifs_sta, line)) {
            string_handler::change_separator(line);

            stringstream ss(line);
            string tid;
            ss >> tid;
            if (tid != train_id) {
                string_handler::recover_separator(line);
                ofs_sta << line << endl;
            }
        }

        ifs_sta.close();
        ofs_sta.close();

        remove(station_source.c_str());
        if (0 == rename(temp.c_str(), station_source.c_str())) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

string train_mapper::select_a_train(string &train_id) {
    ifstream ifs(train_source, ios::in);
    string line;
    while (std::getline(ifs, line)) {
        line = string_handler::change_separator(line);

        stringstream ss(line);
        string id_stored;
        ss >> id_stored;

        if (id_stored == train_id) {
            return line;
        }
    }
    cout << "无法获取列车：" << train_id << endl;
    ifs.close();

    return {};
}

vector<string> train_mapper::select_trains() {
    vector<string> result;

    ifstream ifs(train_source, ios::in);
    string line;

    if (!ifs.good()) {
        cout << "在读取train.csv的过程中出错" << endl;
        cout << "建议检查train.csv的路径是否正确" << endl;
        return result;
    }

    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        } else {
            // 将一条信息内的分隔符从,修改为\t
            line = string_handler::change_separator(line);
            result.push_back(line);
        }
    }

    ifs.close();
    return result;
}

vector<string> train_mapper::select_trains_constraint(string &from, string &to) {
    bool need_not_to_buy = false;
    bool contain_invalid_stat = false;
    bool reverse_stats = false;

    vector<string> result;

    ifstream ifs(train_source, ios::in);
    string line;

    if (!ifs.good()) {
        cout << "在读取train.csv的过程中出错" << endl;
        cout << "建议检查train.csv的路径是否正确" << endl;
        return result;
    }

    string train_id;
    std::getline(ifs, line);
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        } else {
            // 将一条信息内的分隔符从,修改为\t
            line = string_handler::change_separator(line);
            // 获得列车站点集合
            stringstream ss(line);
            ss >> train_id;
            vector<string> all_stations = select_stations_of(train_id);

            // 判断用户起始是否包含在站点集合中，并且顺序一致
            int from_idx = string_handler::index_of(all_stations, from);
            int to_idx = string_handler::index_of(all_stations, to);

            // 处理异常事件与正常事件
            if (from_idx == all_stations.size() - 1) {
                need_not_to_buy = true;
            } else if (from_idx == -1 || to_idx == -1) {
                contain_invalid_stat = true;
            } else if (from_idx >= to_idx) {
                reverse_stats = true;
            } else {
                need_not_to_buy = false;
                contain_invalid_stat = false;
                reverse_stats = false;
                result.push_back(line);
            }
        }
    }

    ifs.close();

    if (need_not_to_buy) {
        cout << "您目前处于列车：" << train_id << " 的终点站" << endl;
        return {};
    } else if (contain_invalid_stat) {
        cout << "包含无效站点" << endl;
        return {};
    } else if (reverse_stats) {
        cout << "出发站与到达站顺序相反" << endl;
        return {};
    } else {
        return result;
    }
}

bool train_mapper::update_a_train(train &t) {
    // 复制
    ifstream ifs(train_source, ios::in);
    string temp_fl = "D:/coding/cpp/codes/learning/online-booking-system/data-source/temp.csv";
    ofstream ofs(temp_fl, ios::app | ios::out);

    string line;
    while (std::getline(ifs, line)) {
        if (!line.empty()) {
            // l是\t分隔，line是,分隔
            string_handler::change_separator(line);

            // 把表头写入temp
            stringstream ss(line);
            string s;
            ss >> s;
            if (s == "train_id") {
                string_handler::recover_separator(line);
                ofs << line << endl;
                continue;
            }

            train *t_ptr = train::from_string(line);
            if (t_ptr->getId() != t.getId()) {
                // 将无关信息写入temp
                string_handler::recover_separator(line);
                ofs << line << endl;
            } else {
                // 将修改后的新信息写入temp
                string new_info_str;
                t.to_string(new_info_str);
                string_handler::recover_separator(new_info_str);
                ofs << new_info_str << endl;
            }
            delete t_ptr;
        }
    }
    ifs.close();
    ofs.close();

    // 给新文件改名为原文件的名字
    remove(train_source.c_str());
    if (0 == rename(temp_fl.c_str(), train_source.c_str())) {
        return true;
    } else {
        return false;
    }
}

bool train_mapper::insert_stations_of(string &train_id, vector<string> &stations) {
    // station_source存在，附加；不存在：创建
    ofstream ofs(station_source, ios::out | ios::app);
    ofs << train_id << ",";
    for (int i = 0; i < stations.size() - 1; i++) {
        ofs << stations[i] << ",";
    }
    ofs << stations[stations.size() - 1] << endl;
    ofs.close();
    return true;
}

vector<string> train_mapper::select_stations_of(string &train_id) {
    vector<string> res;

    if (train_id.empty()) {
        res.emplace_back("参数：train_id为空");
        return res;
    }

    ifstream ifs(station_source, ios::in);
    if (!ifs.good()) {
        res.emplace_back("找不到文件：" + station_source);
        return res;
    }

    string line;
    int flag = 0;
    while (std::getline(ifs, line)) {
        line = string_handler::change_separator(line);

        stringstream ss(line);
        string id;
        ss >> id;

        if (id == train_id) {
            flag = 1;
            string item;
            while (ss >> item) {
                res.emplace_back(item);
            }
        }
    }
    if (flag == 0) {
        res.emplace_back("找不到列车：" + train_id + " 的信息");
    }
    ifs.close();
    return res;
}


