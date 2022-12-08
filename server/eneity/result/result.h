//
// Created by Maximilian_Li on 2022/11/30.
//

#ifndef ONLINE_BOOKING_SYSTEM_RESULT_H
#define ONLINE_BOOKING_SYSTEM_RESULT_H

# include<string>
#include <utility>
# include<vector>
#include <utility>
#include <ostream>

using std::string;
using std::vector;

class result {
private:
    int code_;
    string msg_;
    int val_ = 0;
    long long_val_ = 0;
    vector<string> vec_;
public:
    /* 得到反馈码 */
    int getCode() const;

    /* 得到string类型信息 */
    const string &getMsg() const;

    /* 得到int类型信息 */
    int getVal() const;

    /* 得到long类型信息 */
    long getLongVal() const;

    /* 得到vector<string>类型信息 */
    const vector<string> &getVec() const;

public:
    result(int code, string msg)
            : code_(code), msg_(std::move(msg)) {}

    result(int code, vector<string> vec)
            : code_(code), vec_(std::move(vec)) {}

    result(int code, int val)
            : code_(code), val_(val) {}

    result(int code, long long_val)
            : code_(code), long_val_(long_val) {}

    friend std::ostream &operator<<(std::ostream &os, const result &result);
};


#endif //ONLINE_BOOKING_SYSTEM_RESULT_H
