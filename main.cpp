#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

#include "Record.h"

string get_time()
{
    time_t now;
    time(&now);
    string time_str;
    time_str.assign(asctime(gmtime(&now)));  // 时间char类型转换到string类型
    return time_str;
}

int choose_menu(string prompt)
{
    int choice;
    cout << prompt << ": ";

    while (cin >> choice) {
        cout << "Wrong input. please input an integer again!!";
    }

    string remainder;
    getline(cin, remainder);
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
    cout << "         5.   Delete Record" << endl;
    cout << "         6.   Family" << endl;
    cout << "         7.   Others" << endl;
    cout << "         8.   Exit Programme" << endl;
    cout << "---------------------------------------" << endl;

    int choice = choose_menu("Enter an integer to select category");
    return choice;
}

int select_function_menu()
{
    cout << "--------Function Selection Menu--------" << endl;
    cout << "       0.   Append Function" << endl;
    cout << "       1.   Append Cost Record" << endl;
    cout << "       2.   Check Cost Record" << endl;
    cout << "       3.   Display All Record" << endl;
    cout << "       4.   Edit Record" << endl;
    cout << "       5.   Delete Record" << endl;
    cout << "       6.   Statistics" << endl;
    cout << "       7.   Read From Files" << endl;
    cout << "       8.   Write To Files" << endl;
    cout << "       9.   Exit" << endl;
    cout << "---------------------------------------" << endl;

    int choice = choose_menu("Enter an integer to select function");
    return choice;
}

int main()
{
//"Dinner", "Traffic", "Commodity", "Coat", "Entertainment", "Family", "Other"};
// 餐饮、     交通、      日用品、   服饰、       娱乐、        家用       其他
    vector<Record> records;
    records.push_back(Record("Differ"));
    records.push_back(Record("Traffic"));
    records.push_back(Record("Commodity"));
    records.push_back(Record("Coat"));
    records.push_back(Record("Entertainment"));
    records.push_back(Record("Family"));
    records.push_back(Record("Others"));

    bool more_function_selection = true;
    while (more_function_selection) {

        int function_choice = select_function_menu();

        switch (function_choice) {
            case 0 :
                append_records(records);
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                check_records(records);
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                more_function_selection = false;
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
//（1）添加功能：程序能够任意添加上述支出的记录，可提供选择界面供用户选择所要添加的类别。
//（2）备注功能：对所添加的记录进行详细解说。
//（3）查询功能：可根据支出记录对已添加的记录进行查询，如果未找到，给出相应的提示信息，如果找到，则显示相应的记录信息。
//（4）显示功能：可显示当前系统中所有记录，每条记录占据一行。
//（5）编辑功能：可根据查询结果对相应的记录进行修改。
//（6）删除功能：主要实现对已添加的支出记录进行删除。
//（7）统计功能：能根据多种参数进行支出的统计。能统计总支出、以及每类支出占总支出的百分比以便完成财务报表。
//（8）保存功能：可将当前系统中各类支出记录存入文件中，存入方式任意。
//（9）读取功能：可将保存在文件中的支出信息读入到当前系统中，供用户进行使用。