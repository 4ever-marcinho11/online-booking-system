//
// Created by Maximilian_Li on 2022/11/19.
//

#ifndef ONLINE_BOOKING_SYSTEM_ORDER_H
#define ONLINE_BOOKING_SYSTEM_ORDER_H

#include <string>
#include<ctime>
#include <utility>
#include <ostream>
#include <vector>
#include <iostream>
#include <sstream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::stringstream;

class order {
private:
    string user_id;
    string train_id;
    string from;
    string to;
    int price{};
    int ticket_num{};
    int total_price{};

public:
    /* construct */
    order() = default;

    order(string userId, string trainId, string from, string to, int price, int ticketNum,
          int totalPrice);

    /* deconstruct */
    virtual ~order() = default;


    /* functional */
    vector<string> to_vector();

    static order *from_string(string &line);


    /* override */
    friend std::ostream &operator<<(std::ostream &os, const order &order);

    bool operator==(const order &rhs) const;

    bool operator!=(const order &rhs) const;

public:
    /* getter & setter */
    const string &getUserId() const;

    void setUserId(const string &userId);

    const string &getTrainId() const;

    void setTrainId(const string &trainId);

    const string &getFrom() const;

    void setFrom(const string &from);

    const string &getTo() const;

    void setTo(const string &to);

    int getPrice() const;

    void setPrice(int price);

    int getTicketNum() const;

    void setTicketNum(int ticketNum);

    int getTotalPrice() const;

    void setTotalPrice(int totalPrice);
};


#endif //ONLINE_BOOKING_SYSTEM_ORDER_H
