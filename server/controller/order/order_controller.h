//
// Created by Maximilian_Li on 2022/12/4.
//

#ifndef ONLINE_BOOKING_SYSTEM_ORDER_CONTROLLER_H
#define ONLINE_BOOKING_SYSTEM_ORDER_CONTROLLER_H


#include "../../service/order/order_service.h"

class order_controller {
private:
    order_service os;
public:
    result _create(string &id, string &train_id, string &from, string &to, int nums);

    result _view(string &id);

    result _remove(string &id, string &train_id);

    result _revenue();
};


#endif //ONLINE_BOOKING_SYSTEM_ORDER_CONTROLLER_H
