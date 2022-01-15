#include "app.hpp"
#include "colors.hpp"
#include <string>
#include <sstream>

#define NUM_OF_USERS 4

using namespace std;

class Driver
{
    public:
        void StartApp() {
            // create bunch of users
            User *u1 = new User(0, "u1", "a@gmail", "12", "pass");
            User *u2 = new User(1, "u2", "b@gmail", "12", "pass");
            User *u3 = new User(2, "u3", "c@gmail", "12", "pass");
            User *u4 = new User(3, "u4", "c@gmail", "12", "pass");
            SplitwiseService *s = new SplitwiseService(NUM_OF_USERS);
            s->AddUser(*u1);
            s->AddUser(*u2);
            s->AddUser(*u3);
            s->AddUser(*u4);
            string input;
            string operation;
            string temp;
            uint8_t stream_size = 0;
            vector<string> input_vector;

            cout << BLUE << "Welcome to splitwise" << RESET << endl;
            while (true)
            {
                getline(cin, input);
                stringstream ss(input);
                input_vector.clear();
 
                if (input == "exit") {
                    cout << RED << "Exiting application" << RESET << endl;
                    break;
                }
                while (getline(ss, temp, ' ')) {
                    //cout << temp << endl; 
                    input_vector.push_back(temp);
                }
                if (input_vector.size() == 0)
                    continue;
                operation = input_vector[0];
                if (operation == "SHOW") {
                    if (input_vector.size() == 1) {
                        // show all balances case
                        s->ShowAllBalances();
                    } else {
                        // show specific user's balance case
                        string user_name = input_vector[1];
                        s->ShowBalance(user_name);
                    }
                } else if (operation == "EXPENSE") {
                    int i = 1;
                    string paid_user_name = input_vector[i++];
                    uint64_t amount = stoul(input_vector[i++]);
                    uint8_t num_of_users = stoi(input_vector[i++]);
                    string expense_type;

                    User paid_user = s->GetUser(paid_user_name); 
                    vector<User> users_involved; 
                    for (int j=0; j<num_of_users; j++) {
                        users_involved.push_back(s->GetUser(input_vector[i++]));
                    }
                    expense_type = input_vector[i++];
                    Expense_Type type = StringToExpenseType(expense_type);

                    unordered_map<uint8_t, uint64_t> split;
                    if (type == EXACT || type == PERCENT) {
                        for (int j=0; j<num_of_users; j++) {
                            split[users_involved[j].id] = stoul(input_vector[i++]);
                        }
                    }
                    cout << "Expense amount: " << amount << endl;
                    Expense e = Expense(amount, type, paid_user, num_of_users, users_involved, split, "");
                    s->AddExpense(e);
                } else {
                    cout << RED << "Invalid operation:" << operation << RESET << endl; 
                }
            }
            return;
        }
};

int main() {
    Driver driver;
    driver.StartApp();
    return 0;
}