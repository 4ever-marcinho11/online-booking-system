//
// Created by Maximilian_Li on 2022/11/19.
//

#ifndef ONLINE_BOOKING_SYSTEM_USER_H
#define ONLINE_BOOKING_SYSTEM_USER_H

#include <string>
#include <vector>
#include <ostream>

using std::string;
using std::vector;

class user {
private:
    string id_;
    string name_;
    string sex_;
    string phone_;
    int age_{};
public:
    /* getter & setter */
    const string &getId() const;

    void setId(const string &id);

    const string &getName() const;

    void setName(const string &name);

    const string &getSex() const;

    void setSex(const string &sex);

    const string &getPhone() const;

    void setPhone(const string &phone);

    int getAge() const;

    void setAge(int age);

    /* construct */
    user(string id, string name, string sex, string phone, int age);

    user();

    /* deconstruct */
    virtual ~user();

    /* ostream */
    friend std::ostream &operator<<(std::ostream &os, const user &user);

    /* functional */
    vector<string> to_vector();

};


#endif //ONLINE_BOOKING_SYSTEM_USER_H
