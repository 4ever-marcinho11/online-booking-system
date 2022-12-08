//
// Created by Maximilian_Li on 2022/12/4.
//

#ifndef ONLINE_BOOKING_SYSTEM_USER_CONTROLLER_H
#define ONLINE_BOOKING_SYSTEM_USER_CONTROLLER_H

#include "../../service/user/user_service.h"

class user_controller {
private:
    user_service us;

public:
    result _register(string &name, string &id, string &sex, string &phone, string &age);
    result _login(string &id, string &name);

    result _logout(string &id);
};


#endif //ONLINE_BOOKING_SYSTEM_USER_CONTROLLER_H
