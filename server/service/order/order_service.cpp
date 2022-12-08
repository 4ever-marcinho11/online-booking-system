//
// Created by Maximilian_Li on 2022/12/2.
//`

#include "order_service.h"

result order_service::create_order(string &id, string &train_id, string &from, string &to, int nums) {
    vector<string> stats = tm.select_stations_of(train_id);

    // 判空
    if (stats.empty() || id.empty() || from.empty() || to.empty()) {
        return {0, "用户身份证号、列车编号、起始站、到达站存在空值"};
    }

    // 算账
    int price = ts.get_cost(train_id, from, to).getVal();
    if (price == 0) {
        return {0, "车票价格计算时出现异常"};
    }

    // 判断余量
    result r = ts.list_trains_constraint(from, to);
    vector<string> corresponding_trains = r.getVec();
    for (auto &s: corresponding_trains) {
        train *t = train::from_string(s);
        string tid = t->getId();
        if (tid == train_id) {
            int still_remain = t->getRemain();
            if (still_remain < nums) {
                string msg = "余票数量不足以购买 " + std::to_string(nums) + " 张票";
                return {0, msg};
            }
        }
    }

    int ttp = price * nums;
    order o(id, train_id, from, to, price, nums, ttp);
    om.insert_one(o);

    // 减少空余座位数目
    string t_str = tm.select_a_train(train_id);
    if (t_str.empty()) {
        cout << "在根据列车号查询列车信息时出错，请检查列车号是否正确" << endl;
    }

    train *t_ptr = train::from_string(t_str);
    int remain = t_ptr->getRemain();
    t_ptr->setRemain(remain - nums);

    tm.update_a_train(*t_ptr);
    delete t_ptr;

    return {1, "订单创建成功"};
}

result order_service::view_order(string &id) {
    vector<string> orders = om.select_all(id);
    if (orders.empty()) {
        return {0, "订单为空"};
    }
    return {1, orders};
}

result order_service::remove_order(string &id, string &train_id) {
    string order_str = om.select_one(id, train_id);
    if (order_str.empty()) {
        return {0, "根据用户身份证号与列车编号获取订单信息失败"};
    }
    order *o_ptr = order::from_string(order_str);
    int ticket_nums = o_ptr->getTicketNum();
    bool b = om.delete_one(*o_ptr);
    if (!b) {
        return {0, "在删除订单信息时出现错误"};
    }
    delete o_ptr;

    // 增加空余座位数目
    string t_str = tm.select_a_train(train_id);
    train *t_ptr = train::from_string(t_str);
    int remain = t_ptr->getRemain();
    t_ptr->setRemain(remain + ticket_nums);
    tm.update_a_train(*t_ptr);
    delete t_ptr;

    return {1, "删除订单成功"};
}
