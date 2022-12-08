//
// Created by Maximilian_Li on 2022/12/4.
//

#ifndef ONLINE_BOOKING_SYSTEM_USER_CLI_H
#define ONLINE_BOOKING_SYSTEM_USER_CLI_H


#include <unordered_map>
#include "../../server/controller/user/user_controller.h"
#include "../../server/controller/train/train_controller.h"
#include "../../server/controller/order/order_controller.h"
# include "../../server/utils/time_handler/time_handler.h"

using std::cin;
using std::unordered_map;

class user_cli {
private:
    string id_buf;
    string train_buf;
    string from;
    string to;
    unordered_map<string, int> tic_remain_map;
    result r{0, ""};
private:
    user_mapper um;
    user_controller uc;
    train_controller tc;
    order_controller oc;
public:
    void user_page();

    void auth_page();

    void welcome_page();

    void register_page();

    void login_page();

    void search_trains();

    void create_order();

    void view_orders();

    void remove_order();

    void logout();

    void error_page(int flag, int sec);

    void revenue();

    void add_train();

    void update_train();

    void update_stations();

    void remove_train();


private:
    void sleep(int seconds);
};


#endif //ONLINE_BOOKING_SYSTEM_USER_CLI_H
