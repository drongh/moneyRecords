#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;

#include "Category.h"

string get_time()
{
    time_t now;
    time(&now);
    string time_str;
    time_str.assign(asctime(gmtime(&now)));  // 时间char类型转换到string类型

    // 把时间中的空格换成“－”
    int space_index = time_str.find(' ');
    while (space_index != -1)
    {
        time_str.replace(space_index, 1, "-");
        space_index = time_str.find(' ');
    }
    return time_str.substr(0, time_str.size() - 1);
}

int choose_menu(string prompt, int min_range, int max_range)
{
    string choice_str;

    while (true)
    {
        cout << prompt << ": ";
        getline(cin, choice_str);

        if (choice_str.size() == 1)
        {
            if (min_range <= isalnum(choice_str[0]) || isalnum(choice_str[0]) <= max_range)
            {
                return atoi(choice_str.c_str());
            }
            else
            {
                cout << "The number you entered is out of range!!! Enter again.." << endl;
            }
        }
        else
        {
            cout << "Wrong input. Please input a number between "
                 << min_range << " and " << max_range << "!!!" << endl;
            continue;
        }
    }
}

int select_category_menu()
{
    cout << "--------Category Selection Menu--------" << endl;
    cout << "         0.   Dinner" << endl;
    cout << "         1.   Traffic" << endl;
    cout << "         2.   Commodity" << endl;
    cout << "         3.   Coat" << endl;
    cout << "         4.   Entertainment" << endl;
    cout << "         5.   Family" << endl;
    cout << "         6.   Others" << endl;
    cout << endl;

    int choice = choose_menu("Enter an integer between 0 and 6 as category selection", 0, 6);
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

void edit_record(vector<Category>& records)
{

    if (records.size() == 0)
    {
        cout << "There is no any record to manipulate, Please create it." << endl;
        return;
    }

    int category_choice = select_category_menu();

    cout << "Please input index of item to edit: ";
    int index_of_item;
    cin >> index_of_item;

    cout << "In category " << records[category_choice].get_category_name() << " this item will be edited: " << endl;
    records[category_choice].print_a_record(index_of_item);

    cout << "Please input comment for that item: ";
    string new_comment;
    cin >> new_comment;

    // 删除多余的字符
    string remainder;
    getline(cin, remainder);

    cout << "Please input money for that item: ";
    double new_money;
    cin >> new_money;

    records[category_choice].edit_record(index_of_item, new_comment, new_money);

}

void append_record(vector<Category>& records)
{

    if (records.size() == 0)
    {
        cout << "There is no any category to manipulate, Please create it." << endl;
        return;
    }

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

    records[category_choice].append_record(new_time, new_comment, new_money);
}

void print_records_of_category(const vector<Category>& records)
{

    if (records.size() == 0)
    {
        cout << "There is no any record to manipulate, Please create it." << endl;
        return;
    }

    int category_choice = select_category_menu();
    records[category_choice].print_records();
}

void delete_record(vector<Category>& records)
{

    if (records.size() == 0)
    {
        cout << "There is no any record to manipulate, Please create it." << endl;
        return;
    }

    int category_choice = select_category_menu();
    records[category_choice].print_records();

    cout << "which item do you want to delete? Please input an index: ";
    int index_of_item;
    cin >> index_of_item;

    records[category_choice].delete_record(index_of_item);
}

void print_all_records(const vector<Category>& records)
{

    if (records.size() == 0)
    {
        cout << "There is no any record to manipulate, Please create it." << endl;
        return;
    }

    for (int i = 0; i < records.size(); i++)
    {
        records[i].print_records();
    }
}

void statistics(const vector<Category>& records)
{

    if (records.size() == 0)
    {
        cout << "There is no any record to manipulate, Please create it." << endl;
        return;
    }

    double total_costs = 0;
    for (int i = 0; i < records.size(); i++)
    {
        double category_costs = records[i].get_category_costs();
        total_costs += category_costs;
    }

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    for (int i = 0; i < records.size(); i++)
    {
        double category_costs = records[i].get_category_costs();
        if (category_costs > 0)
        {
            string category_name = records[i].get_category_name();
            cout << "There is " << category_costs << " RMB costs in category " << category_name
                 << " and it takes " << category_costs / total_costs * 100 << "% in total costs\n";
        }
    }
}

void write_category_to_file(Category category)
{
    string filename = category.get_category_name() + ".txt";
    fstream output(filename.c_str(), ios::out);

    vector<item> items = category.get_category_items();
    for (int i = 0; i < items.size(); i++)
    {
        string time_cost = items[i].time_cost;
        double money = items[i].money;
        string comment = items[i].comment;
        output << time_cost << '#' << money << '#' << comment << endl;
    }
    output.close();
}

void write_to_file(vector<Category> records)
{

    for (int i = 0; i < records.size(); i++)
    {
        write_category_to_file(records[i]);
    }

    cout << "Done" << endl;
}

Category read_category_from_file(string category_name)
{
    string filename = category_name + ".txt";
    fstream input(filename.c_str(), ios::in);

    if (input.fail())
    {
        cout << "This file does not exist." << endl;
        cout << "Please write to file first.." << endl;
        exit(1);
    }

    Category category(category_name);

    string line;
    getline(input, line);

    string time_cost;
    string money_str;
    double money;
    string comment;

    while (!input.eof())
    {

        int first_space_index = line.find('#');
        int second_space_index = line.find('#', first_space_index + 1);

        time_cost = line.substr(0, first_space_index);

        money_str = line.substr(first_space_index + 1, second_space_index - first_space_index - 1);
        money = atof(money_str.c_str());

        comment = line.substr(second_space_index + 1);
        category.append_record(time_cost, comment, money);

        getline(input, line);
    }

    return category;
}

vector<Category> read_from_file()
{
    vector<Category> records;

    Category dinner = read_category_from_file("Dinner");
    records.push_back(dinner);

    Category traffic = read_category_from_file("Traffic");
    records.push_back(traffic);

    Category commodity = read_category_from_file("Commodity");
    records.push_back(commodity);

    Category coats = read_category_from_file("Coats");
    records.push_back(coats);

    Category entertainment = read_category_from_file("Entertainment");
    records.push_back(entertainment);

    Category family = read_category_from_file("Family");
    records.push_back(family);

    Category other = read_category_from_file("Others");
    records.push_back(other);

    return records;

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
    while (more)
    {

        int function_choice = select_function_menu();

        switch (function_choice)
        {
            case 0 :
            {
                append_record(records);
                break;
            }
            case 1:
            {
                print_records_of_category(records);
                break;
            }
            case 2:
            {
                print_all_records(records);
                break;
            }
            case 3:
            {
                edit_record(records);
                break;
            }
            case 4:
            {
                delete_record(records);
                break;
            }
            case 5:
            {
                statistics(records);
                break;
            }
            case 6:
            {
                records = read_from_file();
                break;
            }
            case 7:
            {
                write_to_file(records);
                break;
            }
            case 8:
            {
                more = false;
                cout << "Bye Bye" << endl;
                break;
            }
            default:
                cout << "Never get here!!!" << endl;
                break;
        }
    }

    return 0;
}