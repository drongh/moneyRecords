//
// Created by Administrator on 2017/2/28.
//

#include "Category.h"

Category::Category() {

}

Category::Category(string new_category) {
    name = new_category;
}

void Category::append_record(string new_time, string new_comment, double new_money) {
    item new_item;
    new_item.time_cost = new_time;
    new_item.comment = new_comment;
    new_item.money = new_money;
    items.push_back(new_item);
}

void Category::delete_record(int index_of_item) {
    if (index_of_item >= 0 && index_of_item < items.size()) {
        items.erase(items.begin() + index_of_item);
    }
}

void Category::print_a_record(int index) const {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << right << setw(3) << index << ": "
         << setw(25) << items[index].time_cost
         << setw(10) << items[index].money << " "
         << left << setw(30) << items[index].comment << endl;

}

void Category::print_records() const {
    if (items.size() > 0) {
        cout << "-------------------------------" << name << "-------------------------------" << endl;
        for (int i = 0; i < items.size(); i++) {
            print_a_record(i);
        }
        cout << endl;
    }
}

void Category::edit_record(int index_of_item, string new_comment, double new_money) {
    if (index_of_item >= 0 && index_of_item < items.size()) {
        items[index_of_item].comment = new_comment;
        items[index_of_item].money = new_money;
    }
}

double Category::get_category_costs() const {
    double money_in_category = 0;
    for (int i = 0; i < items.size(); i++) {
        money_in_category += items[i].money;
    }
    return money_in_category;
}

string Category::get_category_name() const {
    return name;
}

vector<item> Category::get_category_items() const {
    return items;
}
