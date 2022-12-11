//
// Created by Maximilian_Li on 2022/12/1.
//

#include "train_service.h"

result train_service::get_cost(string &train_id, string &at, string &to) {
    vector<string> stations = tm.select_stations_of(train_id);
    int begin_idx = string_handler::index_of(stations, at);
    int end_idx = string_handler::index_of(stations, to);
    if (begin_idx == -1 || end_idx == -1) {
        return {0, "站点有误，请进行检查"};
    }
    return {1, (end_idx - begin_idx) * 100};
}

int train_service::ticket_strategy(train &tr, string &at, string &to) {
    // 某列车所有站点
    string train_id = tr.getId();
    vector<string> all_stations = tm.select_stations_of(train_id);

    // 某站位置
    int idx_at = string_handler::index_of(all_stations, at);
    int idx_to = string_handler::index_of(all_stations, to);

    // 策略的实现
    int processed;
    int numerator = idx_to - idx_at + 1;
    int denominator = (int) all_stations.size();

    // floor(剩余车票数目 * 两节点之间元素数目 / 所有节点数目)
    // 向下取整保证车票不会溢出
    processed = floor(tr.getRemain() * numerator / denominator);

    return processed < 1 ? 1 : processed;
}

result train_service::list_trains_constraint(string &from, string &to) {
    vector<string> raw = tm.select_trains_constraint(from, to);
    if (raw.empty()) {
        return {0, "没有从" + from + "到" + to + "的火车信息"};
    }

    vector<string> done;
    for (auto &a: raw) {
        // 根据放票策略处理剩余座位信息
        train *t_ptr = train::from_string(a);
        t_ptr->setRemain(ticket_strategy(*t_ptr, from, to));
        string info;
        info = t_ptr->to_string(info);
        done.push_back(info);

        // 删除在堆中开辟的空间
        delete t_ptr;
    }

    return {1, done};
}

result train_service::add_train(train &t) {
    bool b = tm.insert_a_train(t);
    if (!b) {
        return {0, "新增列车失败"};
    } else {
        return {1, "新增列车成功"};
    }
}

result train_service::see_all() {
    vector<string> vec = tm.select_trains();
    if (vec.empty()) {
        return {0, "无法读取列车信息"};
    }
    return {1, vec};
}

result train_service::remove_train(string &tid) {
    bool b = tm.delete_a_train(tid);
    if (b) {
        return {1, "删除成功"};
    } else {
        return {0, "删除失败"};
    }
}

