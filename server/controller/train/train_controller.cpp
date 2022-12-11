//
// Created by Maximilian_Li on 2022/12/4.
//

#include "train_controller.h"

result train_controller::_list(string &from, string &to) {
    return ts.list_trains_constraint(from, to);
}

result train_controller::_price(string &train_id, string &at, string &to) {
    return ts.get_cost(train_id, at, to);
}

result train_controller::_add(train &t) {
    return ts.add_train(t);
}

result train_controller::_see_all() {
    return ts.see_all();
}

result train_controller::_remove(string &tid) {
    return ts.remove_train(tid);
}
