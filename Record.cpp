//
// Created by Administrator on 2017/2/28.
//

#include "Record.h"
#include <iostream>
using std::cout;

Record::Record()
{

}
Record::Record(string new_category)
{
    category = new_category;
}

void Record::append_record(string new_time, string new_comment, double new_money)
{
    Cost new_cost;
    new_cost.time = new_time;
    new_cost.comment = new_comment;
    new_cost.money = new_money;
    cost.push_back(new_cost);
}

void Record::delete_record(int choice)
{
    for (int i = choice; i < cost.size() - 1; i++) {
        cost[i] = cost[i + 1];
    }
    cost.pop_back();
}

void Record::print_records()
{
    cout << "          " << category << "      " << endl;
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < cost.size(); i++) {
        cout << i << " : " << cost[i].time << " "
             << cost[i].money << " "
             << cost[i].comment << endl;
    }
    cout << "--------------------------------------" << endl;
}
void Record::edit_record(int choice, string new_comment, double new_money)
{
    cost[choice].comment = new_comment;
    cost[choice].money = new_money;
}
