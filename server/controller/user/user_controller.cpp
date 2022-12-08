//
// Created by Maximilian_Li on 2022/12/4.
//

#include "user_controller.h"

result user_controller::_register(string &name, string &id, string &sex, string &phone, string &age, string &is_auth) {
    return us.usr_register(name, id, sex, phone, age, is_auth);
}

result user_controller::_login(string &id, string &name) {
    return us.usr_login(name, id);
}

result user_controller::_logout(string &id) {
    return us.usr_logout(id);
}
