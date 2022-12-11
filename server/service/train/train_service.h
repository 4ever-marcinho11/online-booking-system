//
// Created by Maximilian_Li on 2022/12/1.
//

#ifndef ONLINE_BOOKING_SYSTEM_TRAIN_SERVICE_H
#define ONLINE_BOOKING_SYSTEM_TRAIN_SERVICE_H

#include<string>
#include<cmath>

#include "../../mapper/train/train_mapper.h"
#include "../../eneity/result/result.h"

using std::string;

class train_service {
private:
    train_mapper tm;
public:
    result list_trains_constraint(string &from, string &to);

    /* 得到a站到b站的花费 */
    result get_cost(string &train_id, string &at, string &to);

    result add_train(train &t);

    result see_all();

    result remove_train(string &tid);

private:
    /* 放票策略 */
    int ticket_strategy(train &tr, string &at, string &to);

};


#endif //ONLINE_BOOKING_SYSTEM_TRAIN_SERVICE_H
