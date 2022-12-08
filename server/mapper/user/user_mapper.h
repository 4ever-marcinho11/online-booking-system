//
// Created by Maximilian_Li on 2022/11/19.
//

#ifndef ONLINE_BOOKING_SYSTEM_USER_MAPPER_H
#define ONLINE_BOOKING_SYSTEM_USER_MAPPER_H

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include "../../eneity/user/user.h"
#include "../../utils/string_handler/string_handler.h"

using std::string;
using std::stringstream;
using std::fstream;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::cout;
using std::endl;

class user_mapper {
private:
    const string user_source = "D:/coding/cpp/codes/learning/online-booking-system/data-source/user.csv";
public:
    /* construct */
    user_mapper();

    /* deconstruct */
    virtual ~user_mapper();

    /* select one */
    string select_one(string &id);

    /* insert one */
    bool insert_one(user &u);

};


#endif //ONLINE_BOOKING_SYSTEM_USER_MAPPER_H
