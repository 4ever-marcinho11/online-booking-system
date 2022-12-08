//
// Created by Maximilian_Li on 2022/12/4.
//

#include "order_controller.h"

result order_controller::_create(string &id, string &train_id, string &from, string &to, int nums) {
    return os.create_order(id, train_id, from, to, nums);
}

result order_controller::_view(string &id) {
    return os.view_order(id);
}

result order_controller::_remove(string &id, string &train_id) {
    return os.remove_order(id, train_id);
}
