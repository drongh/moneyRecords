#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

#include "Category.h"

string get_time()
{
    time_t now;
    time(&now);
    string time_str;
    time_str.assign(asctime(gmtime(&now)));  // 时间char类型转换到string类型

    string new_time_str = time_str.substr(0, time_str.size() - 1);
    return new_time_str;
}

int choose_menu(string prompt, int min_range, int max_range)
{
    int choice = -1;
    cout << prompt << ": ";

    bool more = true;
    while (more) {

        cin >> choice;

        if (cin.fail()) {
            cout << "Wrong input. please input an integer again!!";
            continue;
        }

        if (choice < min_range || choice > max_range) {
            cout << "The input integer is out of range!!, please input again!!";
            continue;
        }

        more = false;

        string remainder;
        getline(cin, remainder);
    }
    return choice;
}

int select_category_menu()
{
    cout << "--------Category Selection Menu--------" << endl;
    cout << "         0.   Dinner" << endl;
    cout << "         1.   Traffic" << endl;
    cout << "         2.   Commodity" << endl;
    cout << "         3.   Coat" << endl;
    cout << "         4.   Entertainment" << endl;
    cout << "         5.   Delete Category" << endl;
    cout << "         6.   Family" << endl;
    cout << "         7.   Others" << endl;
    cout << endl;

    int choice = choose_menu("Enter an integer between 0 and 7 as category selection", 0, 7);
    return choice;
}

int select_function_menu()
{
    cout << "--------Function Selection Menu--------" << endl;
    cout << "       0.   Append item Records" << endl;
    cout << "       1.   Print Category Records" << endl;
    cout << "       2.   Print All Records" << endl;
    cout << "       3.   Edit Records" << endl;
    cout << "       4.   Delete Records" << endl;
    cout << "       5.   Statistics" << endl;
    cout << "       6.   Read From Files" << endl;
    cout << "       7.   Write To Files" << endl;
    cout << "       8.   Exit" << endl;
    cout << endl;
    int choice = choose_menu("Enter an integer between 0 and 8 as function selection", 0, 8);
    return choice;
}

void edit_records(vector<Category>& category_records)
{
    int category_choice = select_category_menu();

    cout << "Please input index of item to edit: ";
    int index_of_item;
    cin >> index_of_item;

    cout << "Please input comment for that item: ";
    string new_comment;
    getline(cin, new_comment);

    cout << "Please input money for that item: ";
    double new_money;
    cin >> new_money;

    category_records[category_choice].edit_record(index_of_item, new_comment, new_money);

}
void append_cost_records(vector<Category>& records)
{
    int category_choice = select_category_menu();
    string new_time = get_time();

    cout << "Please input item comments: ";
    string new_comment;
    getline(cin, new_comment);

    cout << "Please input item money: ";
    double new_money;
    cin >> new_money;

    string remainder;
    getline(cin, remainder);
    cout << "remainder" << remainder << endl;

    records[category_choice].append_record(new_time, new_comment, new_money);
}

void print_category_records(const vector<Category>& records)
{
    int category_choice = select_category_menu();
    records[category_choice].print_records();
}

void delete_category_record(vector<Category>& records)
{
    int category_choice = select_category_menu();
    records[category_choice].print_records();

    cout << "Please input index of item to delete: ";
    int index_of_item;
    cin >> index_of_item;

    records[category_choice].delete_record(index_of_item);
}

void print_all_records(const vector<Category>& records)
{
    for (int i = 0; i < records.size(); i++) {
        records[i].print_records();
    }
}

void statistics(const vector<Category>& records)
{
    double total_costs = 0;
    for (int i = 0; i < records.size(); i++) {
        double category_costs = records[i].get_category_costs();
        total_costs += category_costs;
    }

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    for (int i = 0; i < records.size(); i++) {
        double category_costs = records[i].get_category_costs();
        if (category_costs > 0) {
            string category_name = records[i].get_category_name();
            cout << "There is " << category_costs << " RMB costs in category " << category_name
                 << " and it takes " << category_costs / total_costs * 100 << " percent in total costs\n";
        }
    }
}

int main()
{
    vector<Category> records;
    records.push_back(Category("Dinner"));        //  餐饮
    records.push_back(Category("Traffic"));       //  交通
    records.push_back(Category("Commodity"));     //  日用品
    records.push_back(Category("Coats"));         //  服饰
    records.push_back(Category("Entertainment")); //  娱乐
    records.push_back(Category("Family"));        //  家用
    records.push_back(Category("Others"));        //  其他

    bool more = true;
    while (more) {

        int function_choice = select_function_menu();

        switch (function_choice) {
            case 0 : {
                append_cost_records(records);
                break;
            }
            case 1: {
                print_category_records(records);
                break;
            }
            case 2: {
                print_all_records(records);
                break;
            }
            case 3: {
                edit_records(records);
                break;
            }
            case 4: {
                delete_category_record(records);
                break;
            }
            case 5: {
                statistics(records);
                break;
            }
            case 6:
                break;
            case 7:
                break;
            case 8:
                more = false;
                break;
            default:
                cout << "Never get here!!!";
                break;
        }
    }

    return 0;
}


//记账手册
//    一、	定义记账种类，（包括餐饮、交通、日用品、服饰、娱乐、家用以及其他），且每月算出总支出，并做份财务报表。
//    二、	功能要求
//（1）添加功能：程序能够任意添加上述支出的记录，可提供选择界面供用户选择所要添加的类别。  //in class function
//（2）备注功能：对所添加的记录进行详细解说。  // in class member
//（3）查询功能：只显示指定种类下的记录。     // in class member
//（4）显示功能：可显示当前系统中所有记录，每条记录占据一行。    //已完成
//（5）编辑功能：可根据查询结果对相应的记录进行修改。  //  in class function
//（6）删除功能：主要实现对已添加的支出记录进行删除。 // in class function
//（7）统计功能：能根据多种参数进行支出的统计。能统计总支出、以及每类支出占总支出的百分比以便完成财务报表。
//（8）保存功能：可将当前系统中各类支出记录存入文件中，存入方式任意。
//（9）读取功能：可将保存在文件中的支出信息读入到当前系统中，供用户进行使用。
// time information   Tue Feb 28 12:50:57 2017