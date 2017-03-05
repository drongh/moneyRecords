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

struct Cost {
    string time;
    string comment;
    double money;
};

class Record
{
public:
    explicit Record();
    explicit Record(string new_category);
    void append_record(string new_time, string new_comment, double new_money);
    void delete_record(int choice);
    void print_record();
    void edit_record(int choice, string new_comment, double new_money);
private:
    string category;
    vector<Cost> cost;
};


#endif //HOMEWORK_RECORDS_H
