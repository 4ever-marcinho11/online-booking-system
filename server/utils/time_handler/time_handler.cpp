//
// Created by Maximilian_Li on 2022/11/12.
//

#include "time_handler.h"

/**
 * 将年月日时分秒整合并转换为字符串
 * @param year 年
 * @param month 月
 * @param day 日
 * @param hour 时
 * @param minute 分
 * @param second 秒
 * @return 整合后的字符串(已去掉结尾的换行符)
 */
string time_handler::aggregate(int year, int month, int day, int hour, int minute, int second) {
    tm structure = {.tm_min=minute, .tm_hour=hour, .tm_mday=day, .tm_mon=month - 1, .tm_year=year - 1900};
    string string_date = asctime(&structure);
    size_t loc = -1;
    for (size_t i = 0; i < string_date.size(); i++) {
        loc = string_date.find(' ', i);
        if (loc < string_date.size() && loc != -1) {
            string_date.replace(loc, 1, "/");
            i = loc + 1;
        }
    }
    return string_date.substr(0, string_date.length() - 1);
}



