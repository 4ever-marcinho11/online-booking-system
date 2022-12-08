//
// Created by Maximilian_Li on 2022/11/19.
//

#include "order.h"

#include <utility>

const string &order::getUserId() const {
    return user_id;
}

void order::setUserId(const string &userId) {
    user_id = userId;
}

const string &order::getTrainId() const {
    return train_id;
}

void order::setTrainId(const string &trainId) {
    train_id = trainId;
}

const string &order::getFrom() const {
    return from;
}

void order::setFrom(const string &from) {
    order::from = from;
}

const string &order::getTo() const {
    return to;
}

void order::setTo(const string &to) {
    order::to = to;
}

int order::getPrice() const {
    return price;
}

void order::setPrice(int price) {
    order::price = price;
}

int order::getTicketNum() const {
    return ticket_num;
}

void order::setTicketNum(int ticketNum) {
    ticket_num = ticketNum;
}

int order::getTotalPrice() const {
    return total_price;
}

void order::setTotalPrice(int totalPrice) {
    total_price = totalPrice;
}

std::ostream &operator<<(std::ostream &os, const order &order) {
    os << "user_id: " << order.user_id << " train_id: " << order.train_id <<
       "\nfrom: " << order.from << " to: " << order.to <<
       "\nprice: " << order.price << " ticket_num: " << order.ticket_num <<
       " total_price: " << order.total_price;
    return os;
}

vector<string> order::to_vector() {
    vector<string> result;

    result.push_back(this->user_id);
    result.push_back(this->train_id);
    result.push_back(this->from);
    result.push_back(this->to);

    using std::to_string;
    result.push_back(to_string(this->price));
    result.push_back(to_string(this->ticket_num));
    result.push_back(to_string(this->total_price));

    return result;
}

bool order::operator==(const order &rhs) const {
    return user_id == rhs.user_id &&
           train_id == rhs.train_id &&
           from == rhs.from &&
           to == rhs.to &&
           price == rhs.price &&
           ticket_num == rhs.ticket_num &&
           total_price == rhs.total_price;
}

bool order::operator!=(const order &rhs) const {
    return !(rhs == *this);
}

order *order::from_string(string &line) {
    stringstream ss(line);
    string id, tr, de, ar, pr, ti, tt;
    ss >> id >> tr >> de >> ar >> pr >> ti >> tt;
    int single_cost = stoi(pr);
    int tickets = stoi(ti);
    int total_cost = stoi(tt);

    auto *o = new order(id, tr, de, ar, single_cost, tickets, total_cost);
    return o;
}

order::order(string userId, string trainId, string from, string to, int price,
             int ticketNum, int totalPrice) : user_id(std::move(userId)), train_id(std::move(trainId)),
                                              from(std::move(from)), to(std::move(to)), price(price),
                                              ticket_num(ticketNum), total_price(totalPrice) {}



