//
// Created by Maximilian_Li on 2022/11/12.
//

#ifndef ONLINE_BOOKING_SYSTEM_TRAIN_H
#define ONLINE_BOOKING_SYSTEM_TRAIN_H

#include <string>
#include<ctime>
#include <utility>
#include <ostream>
#include <vector>
#include <iostream>
#include <sstream>

using std::string;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;

class train {

private:
    // 列车编号
    string id_;
    // 始发站
    string src_;
    // 终点站
    string dst_;
    // 发车时间
    string depart_;
    // 到达时间
    string arrive_;
    // 剩余座位数目
    int remain_;

public:
    /* construct */
    train() :
            id_({}),
            src_({}), dst_({}),
            depart_({}), arrive_({}),
            remain_(0) {};

    train(string id, string src, string dst, string depart, string arrive,
          int remain);

    /* deconstruct */
    ~train() = default;

    /* functional */
    vector<string> to_vector();

    static train *from_string(string &line);

    string& to_string(string& ori);

    bool operator==(const train &rhs) const;

    bool operator!=(const train &rhs) const;

    /* override */
    friend std::ostream &operator<<(std::ostream &os, const train &train);

public:
    /* getter & setter */
    const string &getId() const;

    void setId(const string &id);

    const string &getSrc() const;

    void setSrc(const string &src);

    const string &getDst() const;

    void setDst(const string &dst);

    const string &getDepart() const;

    void setDepart(const string &depart);

    const string &getArrive() const;

    void setArrive(const string &arrive);

    int getRemain() const;

    void setRemain(int remain);
};


#endif //ONLINE_BOOKING_SYSTEM_TRAIN_H
