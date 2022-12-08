//
// Created by Maximilian_Li on 2022/11/30.
//

#ifndef ONLINE_BOOKING_SYSTEM_USER_SERVICE_H
#define ONLINE_BOOKING_SYSTEM_USER_SERVICE_H

#include <string>
#include <sstream>
#include "../../eneity/result/result.h"
#include "../../eneity/user/user.h"
#include "../../mapper/user/user_mapper.h"

using std::string;
using std::stringstream;

class user_service {
private:
    string current_usr = "D:/coding/cpp/codes/learning/online-booking-system/data-source/current_usr.csv";
    user_mapper um;

public:
    result usr_register(string &name, string &id, string &sex, string &phone, string &age, string& is_auth);

    result usr_login(string &name, string &id);

    result usr_logout(string &id);
};


#endif //ONLINE_BOOKING_SYSTEM_USER_SERVICE_H
