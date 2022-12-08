//
// Created by Maximilian_Li on 2022/11/19.
//

#ifndef ONLINE_BOOKING_SYSTEM_ORDER_MAPPER_H
#define ONLINE_BOOKING_SYSTEM_ORDER_MAPPER_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include "../../eneity/train/train.h"
#include "../../eneity/user/user.h"
#include "../../eneity/order/order.h"
#include "../../utils/string_handler/string_handler.h"

using std::string;
using std::stringstream;
using std::fstream;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::ios;

class order_mapper {
private:
    const string order_source = "D:/coding/cpp/codes/learning/online-booking-system/data-source/order.csv";

public:
    /* construct */
    order_mapper();

    /* deconstruct */
    virtual ~order_mapper() = default;

    /* insert one */
    bool insert_one(order &o);

    /* select one */
    string select_one(string &user_id,string &train_id);

    /* select all */
    vector<string> select_all(string &user_id);

    /* delete one */
    bool delete_one(order &o);

    /* 管理员接口：查询总体收入信息 */
    long select_total_revenue();
};


#endif //ONLINE_BOOKING_SYSTEM_ORDER_MAPPER_H
