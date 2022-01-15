#include <iostream>
#include <unordered_map>
#include <vector>
#include "colors.hpp"

using namespace std;

#define HUNDRED_PERCENT 100
static uint32_t expenses_id = 1;
enum Expense_Type { EQUAL, EXACT, PERCENT, INVALID };

Expense_Type StringToExpenseType(string expense_type){
    if (expense_type == "EQUAL")
        return EQUAL;
    else if (expense_type == "EXACT")
        return EXACT;
    else if (expense_type == "PERCENT")
        return PERCENT;
    return INVALID; 
}

class Address
{
    private:
        string house_no;
        string street;
        string city;
        string state;
        string country;
        string pin_code;
};

class Person 
{
    public:
        string name;
        string email;
        string mobile_no;
        Address address;
};

class User : public Person
{
    public:
        uint8_t id;
        string password;

        User() {
            return;
        }
        User(uint8_t id, string name, string email, string mobile, string password) {
            this->id = id;
            this->name = name;
            this->email = email;
            this->mobile_no = mobile;
            this->password = password;
            return;
        }
};

class Expense
{
    public:
        uint64_t id;
        uint64_t amount;
        Expense_Type type;
        User paid_user = User(0, "0", "0", "0", "0");
        uint8_t num_of_users;
        vector<User> users_involved;
        unordered_map<uint8_t, uint64_t> split;
        string description;
    
    public:
        Expense(uint64_t amount, Expense_Type type, User paid_user, 
        uint8_t num_of_users, vector<User> users_involved, unordered_map<uint8_t, uint64_t> split, string description) {
            this->id = expenses_id++;
            this->amount = amount;
            this->type = type;
            this->paid_user = paid_user;
            this->num_of_users = num_of_users;
            this->users_involved = users_involved;
            this->split = split;
            this->description = description;
            return;
        }

        bool IsValid() {
            uint64_t total_amount = 0;
            uint8_t total_percent = 0;
            bool is_valid = true;

            switch (this->type)
            {
            case EXACT:
                for (auto it = this->split.begin(); it != this->split.end(); it++)
                    total_amount += it->second;
                if (total_amount != this->amount)
                    is_valid = false;
                break;
            
            case PERCENT:
                for (auto it = this->split.begin(); it != this->split.end(); it++)
                    total_percent += it->second;
                if (total_percent != HUNDRED_PERCENT)
                    is_valid = false;
                break;

            default:
                break;
            }
            return is_valid;
        }
};

class SplitwiseService
{
    private:
        vector<User> users;
        unordered_map<string, User> username_user_map;
        vector<Expense> expenses;
        unordered_map<string, vector<Expense> > user_expenses_map;
        vector<vector<int> > balances;
        uint8_t num_of_users;

        void UpdateBalances(Expense e) {
            int local_split = 0;
            uint8_t percent = 0; 

            switch (e.type)
            {
            case EQUAL:
                local_split = e.amount/ e.num_of_users; 
                for (auto user : e.users_involved) {
                    if (user.id == e.paid_user.id)
                        continue;
                    this->balances[e.paid_user.id][user.id] += local_split;
                    this->balances[user.id][e.paid_user.id] -= local_split;
                }
                break;
            
            case EXACT:
                for (auto user : e.users_involved) {
                    if (user.id == e.paid_user.id)
                        continue;
                    local_split = e.split[user.id];
                    cout << "split:" << local_split << endl;
                    this->balances[e.paid_user.id][user.id] += local_split;
                    this->balances[user.id][e.paid_user.id] -= local_split;
                    cout << "balance:" << this->balances[e.paid_user.id][user.id] << endl;
                }

            case PERCENT:
                for (auto user : e.users_involved) {
                    if (user.id == e.paid_user.id)
                        continue;
                    percent = e.split[user.id];
                    local_split = int((percent * e.amount))/ HUNDRED_PERCENT;
                    this->balances[e.paid_user.id][user.id] += local_split;
                    this->balances[user.id][e.paid_user.id] -= local_split;
                }

            default:
                break;
            }
            return;
        }

        void UpdateUserExpensesMap(Expense e) {
            for (auto user : e.users_involved) {
                this->user_expenses_map[user.name].push_back(e);
            }
            return;
        }

        void UpdateExpenses(Expense e) {
            this->expenses.push_back(e);
            return;
        }

    public:
        SplitwiseService(uint8_t num_of_users) {
            this->num_of_users = num_of_users;
            vector<int> temp(num_of_users, 0);
            for (int i=0; i<num_of_users; i++)
               this->balances.push_back(temp);
            return;
        }

        bool AddUser(User user) {
            // add validation to check if user-id don't exist already
            this->users.push_back(user);
            this->username_user_map[user.name] = user;
            return true;
        }

        User GetUser(string user_name) {
            return this->username_user_map[user_name];
        }

        void ShowBalance(string user_name) {
            uint8_t user_id = GetUser(user_name).id;
            int balance = 0;
            bool no_balances = true;

            cout << GREEN << this->users[user_id].name << " balances : " << RESET << endl;
            cout <<  MAGENTA << "------------------------------" << RESET << endl;
            for (int i=0; i<this->num_of_users; i++) {
                balance = this->balances[user_id][i];
                if (balance != 0) {
                    no_balances = false;
                    if (balance > 0) {
                        cout << BLUE << this->users[i].name << " owes " << this->users[user_id].name << ":" << balance <<  RESET << endl;
                    } else {
                        cout << CYAN << this->users[user_id].name << " owes " << this->users[i].name << ":" << abs(balance) << RESET <<  endl;
                    }
                }
            }
            if (no_balances == true) {
                cout << RED << "No balances" << RESET << endl;
            }
            cout <<  MAGENTA << "------------------------------" << RESET << endl;
        }

        void ShowAllBalances() {
            for (int i=0; i<this->num_of_users; i++) {
                ShowBalance(this->users[i].name);
            }
            return;
        }
        
        bool AddExpense(Expense e) {
            if (e.IsValid() == false) {
                cout << RED << "Invalid expense" << RESET << endl;
                return false;
            }
            UpdateExpenses(e);
            UpdateBalances(e);
            UpdateUserExpensesMap(e);
            return true;
        }
};