//
// Created by Maximilian_Li on 2022/11/12.
//

#ifndef ONLINE_BOOKING_SYSTEM_TIME_HANDLER_H
#define ONLINE_BOOKING_SYSTEM_TIME_HANDLER_H

#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>

using std::string;

/*
 * 把time_t时间转换为tm结构
 */
class time_handler {
public:
    static string aggregate(int year, int month, int day, int hour, int minute, int second);
};


#endif //ONLINE_BOOKING_SYSTEM_TIME_HANDLER_H
