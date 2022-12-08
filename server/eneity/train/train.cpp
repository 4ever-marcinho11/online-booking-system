//
// Created by Maximilian_Li on 2022/11/12.
//

#include "train.h"
#include <utility>

train::train(string id,
             string src, string dst,
             string depart, string arrive,
             int remain) :
        id_(std::move(id)),
        src_(std::move(src)), dst_(std::move(dst)),
        depart_(std::move(depart)), arrive_(std::move(arrive)),
        remain_(remain) {}

const string &train::getId() const {
    return id_;
}

void train::setId(const string &id) {
    id_ = id;
}

const string &train::getSrc() const {
    return src_;
}

void train::setSrc(const string &src) {
    src_ = src;
}

const string &train::getDst() const {
    return dst_;
}

void train::setDst(const string &dst) {
    dst_ = dst;
}

const string &train::getDepart() const {
    return depart_;
}

void train::setDepart(const string &depart) {
    depart_ = depart;
}

const string &train::getArrive() const {
    return arrive_;
}

void train::setArrive(const string &arrive) {
    arrive_ = arrive;
}

int train::getRemain() const {
    return remain_;
}

void train::setRemain(int remain) {
    remain_ = remain;
}

std::ostream &operator<<(std::ostream &os, const train &train) {
    os << "train: " << train.id_ <<
       "\nfrom: " << train.src_ << ", to: " << train.dst_ <<
       "\nleaves on: " << train.depart_ <<
       "arrives on: " << train.arrive_ << "tickets remain: " << train.remain_;
    return os;
}

vector<string> train::to_vector() {
    vector<string> result;

    result.push_back(this->id_);
    result.push_back(this->src_);
    result.push_back(this->dst_);
    result.push_back(this->depart_);
    result.push_back(this->arrive_);
    using std::to_string;
    result.push_back(to_string(this->remain_));

    return result;
}

train *train::from_string(string &line) {
    stringstream ss(line);
    string id, src, dst, dep, arr, rem;
    ss >> id >> src >> dst >> dep >> arr >> rem;
    int remain = std::stoi(rem);
    auto *t = new train(id, src, dst, dep, arr, remain);
    return t;
}

bool train::operator==(const train &rhs) const {
    return id_ == rhs.id_ &&
           src_ == rhs.src_ &&
           dst_ == rhs.dst_ &&
           depart_ == rhs.depart_ &&
           arrive_ == rhs.arrive_ &&
           remain_ == rhs.remain_;
}

bool train::operator!=(const train &rhs) const {
    return !(rhs == *this);
}

string &train::to_string(string &ori) {
    ori += this->getId();
    ori += "\t";
    ori += this->getSrc();
    ori += "\t";
    ori += this->getDst();
    ori += "\t";
    ori += this->getDepart();
    ori += "\t";
    ori += this->getArrive();
    ori += "\t";
    using std::to_string;
    ori += to_string(this->remain_);
    return ori;
}
