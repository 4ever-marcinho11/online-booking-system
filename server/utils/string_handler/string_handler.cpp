//
// Created by Maximilian_Li on 2022/11/19.
//

#include "string_handler.h"

/**
 * 将使用,分隔的字符串转换为使用\\t分割的形式
 * @param origin 原字符串
 * @return 转换后的字符串
 */
string string_handler::change_separator(string &origin) {
    size_t loc;
    for (size_t i = 0; i < origin.size(); i++) {
        loc = origin.find(',', i);
        if (loc < origin.size() && loc != -1) {
            origin.replace(loc, 1, "\t");
            i = loc + 1;
        }
    }
    return origin;
}

string string_handler::recover_separator(string &origin) {
    size_t loc;
    for (size_t i = 0; i < origin.size(); i++) {
        loc = origin.find('\t', i);
        if (loc < origin.size() && loc != -1) {
            origin.replace(loc, 1, ",");
            i = loc + 1;
        }
    }
    return origin;
}

int string_handler::index_of(vector<string> &vec, string &str) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == str) {
            return i;
        }
    }
    return -1;
}
