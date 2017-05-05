//
// Created by Administrator on 2017/2/28.
//

#ifndef HOMEWORK_RECORDS_H
#define HOMEWORK_RECORDS_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

struct item {
    string time_cost;
    double money;
    string comment;
};

class Category {
public:
    explicit Category();

    explicit Category(string new_category);

    void append_record(string new_time, string new_comment, double new_money);

    void delete_record(int index_of_item);

    void print_a_record(int index) const;

    void print_records() const;

    void edit_record(int index_of_item, string new_comment, double new_money);

    double get_category_costs() const;

    string get_category_name() const;

    vector<item> get_category_items() const;

private:
    string name;
    vector<item> items;
};


#endif //HOMEWORK_RECORDS_H
