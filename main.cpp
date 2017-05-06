#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <memory>

#include "simpio.h"

using namespace std;

#include "Category.h"

string get_time() {
    time_t now;
    time(&now);
    string time_str;
    time_str.assign(asctime(gmtime(&now)));  // 时间char类型转换到string类型

    // 把时间中的空格换成“－”
    size_t space_index = time_str.find(' ');
    while (space_index != -1) {
        time_str.replace(space_index, 1, "-");
        space_index = time_str.find(' ');
    }
    return time_str.substr(0, time_str.size() - 1);
}

int select_category_menu() {
    cout << "--------Category Selection Menu--------" << endl;
    cout << "         0.   Dinner" << endl;
    cout << "         1.   Traffic" << endl;
    cout << "         2.   Commodity" << endl;
    cout << "         3.   Coat" << endl;
    cout << "         4.   Entertainment" << endl;
    cout << "         5.   Family" << endl;
    cout << "         6.   Others" << endl;
    cout << "         7.   Back" << endl;
    cout << endl;

    int choice = getIntegerBetween("Enter an integer between 0 and 7 as category selection: ", 0, 7);
    return choice;
}

int select_function_menu() {
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
    int choice = getIntegerBetween("Enter an integer between 0 and 8 as function selection: ", 0, 8);
    return choice;
}

void edit_record(vector<shared_ptr<Category>>& records) {

    if (records.size() == 0) {
        cout << "There is no any record to manipulate, Please create it." << endl;
        return;
    }

    int category_choice = select_category_menu();
    if (category_choice == 7) {
        return;
    }

    int index_of_item = getInteger("Please input index of item to edit: ", "Illegal integer format. Try again.");

    cout << "In category " << records[category_choice]->get_category_name() << " this item will be edited: " << endl;
    records[category_choice]->print_a_record(index_of_item);

    string new_comment = getLine("Please input comment for that item: ");
    double new_money = getReal("Please input money for that item: ", "Illegal integer format. Try again");

    records[category_choice]->edit_record(index_of_item, new_comment, new_money);

}

void append_record(vector<shared_ptr<Category>>& records) {

    if (records.size() == 0) {
        cout << "There is no any category to manipulate, Please create it." << endl;
        return;
    }

    int category_choice = select_category_menu();
    if (category_choice == 7) {
        return;
    }

    string new_time = get_time();
    string new_comment = getLine("Please input comment for that item: ");
    double new_money = getReal("Please input item money: ", "Illegal integer format. Try again.");

    records[category_choice]->append_record(new_time, new_comment, new_money);
}

void print_records_of_category(const vector<shared_ptr<Category>>& records) {

    if (records.size() == 0) {
        cout << "There is no any record to manipulate, Please create it." << endl;
        return;
    }

    int category_choice = select_category_menu();

    if (category_choice == 7) {
        return;
    }
    records[category_choice]->print_records();
}

void delete_record(vector<shared_ptr<Category>>& records) {

    if (records.size() == 0) {
        cout << "There is no any record to manipulate, Please create it." << endl;
        return;
    }

    int category_choice = select_category_menu();
    if (category_choice == 7) {
        return;
    }

    records[category_choice]->print_records();
    int index_of_item = getInteger("Which item do you want to delete? Please input an index: ",
                                   "Illegal integer format. Try again.");

    records[category_choice]->delete_record(index_of_item);
}

void print_all_records(const vector<shared_ptr<Category>>& records) {

    if (records.size() == 0) {
        cout << "There is no any record to manipulate, Please create it." << endl;
        return;
    }

    for (int i = 0; i < records.size(); ++i) {
        records[i]->print_records();
    }
}

void statistics(const vector<shared_ptr<Category>>& records) {

    if (records.size() == 0) {
        cout << "There is no any record to manipulate, Please create it." << endl;
        return;
    }

    double total_costs = 0;
    for (int i = 0; i < records.size(); ++i) {
        double category_costs = records[i]->get_category_costs();
        total_costs += category_costs;
    }

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    for (int i = 0; i < records.size(); ++i) {
        double category_costs = records[i]->get_category_costs();
        if (category_costs > 0) {
            string category_name = records[i]->get_category_name();
            cout << "There is " << category_costs << " RMB costs in category " << category_name
                 << " and it takes " << category_costs / total_costs * 100 << "% in total costs\n";
        }
    }
}

void write_category_to_file(const shared_ptr<Category>& p_category) {
    string filename = p_category->get_category_name() + ".txt";
    fstream output(filename.c_str(), ios::out);

    vector<item> items = p_category->get_category_items();
    for (int i = 0; i < items.size(); i++) {
        string time_cost = items[i].time_cost;
        double money = items[i].money;
        string comment = items[i].comment;
        output << time_cost << '#' << money << '#' << comment << endl;
    }
    output.close();
}

void write_to_file(const vector<shared_ptr<Category>>& records) {

    for (int i = 0; i < records.size(); ++i) {
        write_category_to_file(records[i]);
    }
    cout << "Done" << endl;
}

shared_ptr<Category> read_category_from_file(const string& category_name) {
    string filename = category_name + ".txt";
    fstream input(filename.c_str(), ios::in);

    if (input.fail()) {
        cout << "This file does not exist." << endl;
        cout << "Please write to file first.." << endl;
        exit(1);
    }

    auto p_category = make_shared<Category>(category_name);

    string line;
    getline(input, line);

    string time_cost;
    string money_str;
    double money;
    string comment;

    while (!input.eof()) {

        size_t first_space_index = line.find('#');
        size_t second_space_index = line.find('#', first_space_index + 1);

        time_cost = line.substr(0, first_space_index);

        money_str = line.substr(first_space_index + 1, second_space_index - first_space_index - 1);
        money = atof(money_str.c_str());

        comment = line.substr(second_space_index + 1);
        p_category->append_record(time_cost, comment, money);

        getline(input, line);
    }
    return p_category;
}

vector<shared_ptr<Category>> read_from_file(const vector<string>& category_name) {
    vector<shared_ptr<Category>> records;

    for (const auto& name : category_name) {
        auto p_category = read_category_from_file(name);
        records.emplace_back(p_category);
    }
    return move(records);
}

int main() {

    vector<string> category_name{"Dinner", "Traffic", "Commodity", "Coats", "Entertainment", "Family", "Others"};

    vector<shared_ptr<Category>> records;
    for (const auto& name : category_name) {
        auto p_category = make_shared<Category>(name);
        records.emplace_back(p_category);
    }

    bool more = true;
    while (more) {

        int function_choice = select_function_menu();

        switch (function_choice) {
            case 0 : {
                append_record(records);
                break;
            }
            case 1: {
                print_records_of_category(records);
                break;
            }
            case 2: {
                print_all_records(records);
                break;
            }
            case 3: {
                edit_record(records);
                break;
            }
            case 4: {
                delete_record(records);
                break;
            }
            case 5: {
                statistics(records);
                break;
            }
            case 6: {
                records = read_from_file(category_name);
                break;
            }
            case 7: {
                write_to_file(records);
                break;
            }
            case 8: {
                more = false;
                cout << "Bye Bye" << endl;
                break;
            }
            default: {
                more = false;
                cout << "Never get here!!!" << endl;
                break;
            }
        }
    }

    return 0;
}