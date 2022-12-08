//
// Created by Maximilian_Li on 2022/11/19.
//

#ifndef ONLINE_BOOKING_SYSTEM_USER_H
#define ONLINE_BOOKING_SYSTEM_USER_H

#include <string>
#include <vector>
#include <ostream>
#include <sstream>

using std::string;
using std::vector;
using std::stringstream;

class user {
private:
    string id_;
    string name_;
    string sex_;
    string phone_;
    int age_{};
    // 在version2中添加是否是管理员这一属性
    int is_auth_{};

public:
    /* 构造函数 */
    user(string id, string name, string sex, string phone, int age, int is_auth);

    user();

    /* 析构函数 */
    virtual ~user();

public:
    /* 重载流输出运算符 */
    friend std::ostream &operator<<(std::ostream &os, const user &user);

    /* 功能性代码 */
    vector<string> to_vector();

    static user *from_string(string &line);

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

    int getIsAuth() const;

    void setIsAuth(int isAuth);

};


#endif //ONLINE_BOOKING_SYSTEM_USER_H
