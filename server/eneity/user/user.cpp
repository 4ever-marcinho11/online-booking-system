//
// Created by Maximilian_Li on 2022/11/19.
//

#include "user.h"

#include <utility>

const string &user::getId() const {
    return id_;
}

void user::setId(const string &id) {
    id_ = id;
}

const string &user::getName() const {
    return name_;
}

void user::setName(const string &name) {
    name_ = name;
}

const string &user::getSex() const {
    return sex_;
}

void user::setSex(const string &sex) {
    sex_ = sex;
}

const string &user::getPhone() const {
    return phone_;
}

void user::setPhone(const string &phone) {
    phone_ = phone;
}

int user::getAge() const {
    return age_;
}

void user::setAge(int age) {
    age_ = age;
}

int user::getIsAuth() const {
    return is_auth_;
}

void user::setIsAuth(int isAuth) {
    is_auth_ = isAuth;
}

user::user(string id, string name, string sex, string phone, int age, int is_auth)
        : id_(std::move(id)),
          name_(std::move(name)),
          sex_(std::move(sex)),
          phone_(std::move(phone)),
          age_(age),
          is_auth_(is_auth) {}

std::ostream &operator<<(std::ostream &os, const user &user) {
    os << "user: " << user.id_
       << "\nname: " << user.name_ << ", age: " << user.age_ << ", sex: " << user.sex_
       << "\nphone: " << user.phone_
       << "\nis_auth: " << user.is_auth_;
    return os;
}

vector<string> user::to_vector() {
    vector<string> result;

    result.push_back(this->id_);
    result.push_back(this->name_);
    result.push_back(this->sex_);
    result.push_back(this->phone_);
    using std::to_string;
    result.push_back(to_string(this->age_));
    result.push_back(to_string(this->is_auth_));

    return result;
}

user *user::from_string(string &line) {
    stringstream ss(line);
    string id, name, sex, phone, age, is_auth;

    ss >> id >> name >> sex >> phone >> age >> is_auth;
    int age_int = stoi(age);
    int is_auth_int = stoi(is_auth);

    auto* u = new user(id, name, sex, phone, age_int, is_auth_int);
    return u;
}

user::~user() = default;

user::user() = default;
