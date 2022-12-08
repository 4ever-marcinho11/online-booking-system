#include <iostream>
#include <string>
#include <ctime>
#include "server/utils/time_handler/time_handler.h"
#include "server/mapper/train/train_mapper.h"
#include "server/mapper/user/user_mapper.h"
#include "server/mapper/order/order_mapper.h"
#include "server/eneity/train/train.h"
#include "server/eneity/user/user.h"
#include "server/eneity/order/order.h"
#include "server/eneity/result/result.h"
#include "server/service/user/user_service.h"
#include "server/service/train/train_service.h"
#include "client/user/user_cli.h"

using namespace std;

vector<string> set_stations() {
    vector<string> v;
    v.emplace_back("北京");
    v.emplace_back("沧州");
    v.emplace_back("德州");
    v.emplace_back("济南");
    v.emplace_back("泰安");
    v.emplace_back("枣庄");
    v.emplace_back("徐州");
    v.emplace_back("南京");
    v.emplace_back("镇江");
    v.emplace_back("苏州");
    v.emplace_back("上海");
    return v;
}

void add_train() {
    string dep = time_handler::aggregate(2022, 12, 30, 14, 20, 00);
    string arr = time_handler::aggregate(2022, 12, 30, 18, 50, 00);
    train tr("G211", "北京", "上海", dep, arr, 203);
    train_mapper tm;
    tm.insert_a_train(tr);
    vector<string> stations = set_stations();
    string id = "G211";
    tm.insert_stations_of(id, stations);
}

void test_usr_cli() {
    user_cli c;
    c.welcome_page();
}

void test_create() {
    train_controller tc;
    order_controller oc;

    string id = "120105200203153456";
    string train_id = "G382";
    string from = "qingdao";
    string to = "zibo";
    int num = 1;

    result r = oc._create(id, train_id, from, to, num);
    cout << r.getMsg() << endl;
}

void test_remove() {
    train_controller tc;
    order_controller oc;

    string id = "120105200203153456";
    string train_id = "G382";

    result r = oc._remove(id, train_id);
    cout << r.getMsg() << endl;
}

void test_get_stations() {
    train_mapper tm;
    string tid = "G211";
    vector<string> stats = tm.select_stations_of(tid);
    for (auto &a: stats) {
        cout << a << endl;
    }
}

int main() {
   test_usr_cli();
    return 0;
}



