//
// Created by Maximilian_Li on 2022/11/12.
//

#ifndef ONLINE_BOOKING_SYSTEM_TRAIN_MAPPER_H
#define ONLINE_BOOKING_SYSTEM_TRAIN_MAPPER_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include "../../eneity/train/train.h"
#include "../../utils/string_handler/string_handler.h"

using std::string;
using std::stringstream;
using std::fstream;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::ios;


class train_mapper {
private:
    const string train_source = "D:/coding/cpp/codes/learning/online-booking-system/data-source/train.csv";
    const string station_source = "D:/coding/cpp/codes/learning/online-booking-system/data-source/stations.csv";

public:
    /* 构造函数 */
    train_mapper();

    /* 析构函数 */
    virtual ~train_mapper() = default;

    /* 增加一条列车数据 */
    bool insert_a_train(train &t);

    /* 增加多条列车数据 */
    bool insert_trains(vector<train> &ts);

    /* 删除一条列车数据，同时删除其站点数据 */
    // todo
    bool delete_a_train(string &train_id);

    /* 查询一条列车数据 */
    string select_a_train(string &train_id);

    /* 查询全部列车数据 */
    vector<string> select_trains();

    /* 根据两个站点（有序），查询多条列车数据 */
    vector<string> select_trains_constraint(string &from, string &to);

    /* 修改一条列车数据 */
    bool update_a_train(train &t);

    /* 为一辆列车增加站点数据 */
    bool insert_stations_of(string &train_id, vector<string> &stations);

    /* 查询一辆列车的站点数据 */
    vector<string> select_stations_of(string &train_id);
};


#endif //ONLINE_BOOKING_SYSTEM_TRAIN_MAPPER_H
