//
// Created by Administrator on 2017/2/28.
//

#include "Category.h"

Category::Category()
{

}
Category::Category(string new_category)
{
    name = new_category;
}

void Category::append_record(string new_time, string new_comment, double new_money)
{
    item new_item;
    new_item.time = new_time;
    new_item.comment = new_comment;
    new_item.money = new_money;
    items.push_back(new_item);
}

void Category::delete_record(int index_of_item)
{
    if (index_of_item >= 0 && index_of_item < items.size()) {
        for (int i = index_of_item; i < items.size() - 1; i++) {
            items[i] = items[i + 1];
        }
        items.pop_back();
    }
}

void Category::print_records() const
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    if (items.size() > 0) {
        cout << "-------------------------------" << name << "-------------------------------" << endl;
        for (int i = 0; i < items.size(); i++) {
            cout << setw(3) << i << ": "
                 << setw(25) << items[i].time
                 << setw(10) << items[i].money << " "
                 << left << setw(30) << items[i].comment << endl;
        }
        cout << endl;
    }
}

void Category::edit_record(int index_of_item, string new_comment, double new_money)
{
    items[index_of_item].comment = new_comment;
    items[index_of_item].money = new_money;
}

double Category::get_category_costs() const
{
    double money_in_category = 0;
    for (int i = 0; i < items.size(); i++) {
        money_in_category += items[i].money;
    }
    return money_in_category;
}

string Category::get_category_name() const
{
    return name;
}