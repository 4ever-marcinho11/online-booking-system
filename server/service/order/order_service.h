//
// Created by Maximilian_Li on 2022/12/2.
//

#ifndef ONLINE_BOOKING_SYSTEM_ORDER_SERVICE_H
#define ONLINE_BOOKING_SYSTEM_ORDER_SERVICE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

#include "../train/train_service.h"
#include "../user/user_service.h"
#include "../../mapper/order/order_mapper.h"

class order_service {
private:
    train_service ts;
    train_mapper tm;
    user_service us;
    order_mapper om;
public:
    /* 创建订单 */
    result create_order(string &id, string &train_id, string &from, string &to, int nums);

    /* 查看用户所有订单 */
    result view_order(string &id);

    /* 撤回订单 */
    result remove_order(string &id, string &train_id);
};


#endif //ONLINE_BOOKING_SYSTEM_ORDER_SERVICE_H
