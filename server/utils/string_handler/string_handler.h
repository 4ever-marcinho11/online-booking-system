//
// Created by Maximilian_Li on 2022/11/19.
//

#ifndef ONLINE_BOOKING_SYSTEM_STRING_HANDLER_H
#define ONLINE_BOOKING_SYSTEM_STRING_HANDLER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class string_handler {
public:
    static string change_separator(string &origin);
    static string recover_separator(string &origin);
    static int index_of(vector<string> &vec, string &str);
};


#endif //ONLINE_BOOKING_SYSTEM_STRING_HANDLER_H
