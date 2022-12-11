//
// Created by Maximilian_Li on 2022/12/4.
//

#ifndef ONLINE_BOOKING_SYSTEM_TRAIN_CONTROLLER_H
#define ONLINE_BOOKING_SYSTEM_TRAIN_CONTROLLER_H


#include "../../service/train/train_service.h"

class train_controller {
private:
    train_service ts;
public:
    result _list(string &from, string &to);

    result _price(string &train_id, string &at, string &to);

    result _add(train &t);

    result _see_all();

    result _remove(string &tid);
};


#endif //ONLINE_BOOKING_SYSTEM_TRAIN_CONTROLLER_H
