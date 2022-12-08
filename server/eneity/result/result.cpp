//
// Created by Maximilian_Li on 2022/11/30.
//

#include "result.h"

int result::getCode() const {
    return code_;
}

const string &result::getMsg() const {
    return msg_;
}

std::ostream &operator<<(std::ostream &os, const result &result) {
    os << result.code_ << ", " << result.msg_;
    return os;
}

int result::getVal() const {
    return val_;
}

const vector<string> &result::getVec() const {
    return vec_;
}
