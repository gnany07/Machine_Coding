#include "app.hpp"
#include "colors.hpp"

using namespace std;

class Driver
{
    public:
        void StartGame() {
            string user_input;
            cout << YELLOW << "Welcome to 2048 game" << RESET << endl; 
            int grid_size, winning_score, base_value;
            char move;
            cout << MAGENTA << "Enter grid size, winning score and base value" << RESET << endl;
            cin >> grid_size >> winning_score >> base_value;
            Game game(grid_size, winning_score, base_value);
            game.GenerateRandomTile();
            game.DisplayGameState();
            while (true) {
                //cout << MAGENTA << "Make move" << RESET << endl;
                cin >> move;
                game.MakeMove(move);
                if (game.IsGameEnd() == true) {
                    cout << CYAN << "Do you want to Restart?" << RESET << endl;
                    cin >> user_input;
                    if (user_input == "YES" || user_input == "yes" || user_input == "y") {
                        game.Restart(grid_size, winning_score, base_value);
                    } else {
                        break;
                    }
                }
                game.GenerateRandomTile();
                game.DisplayGameState();
            }

        }
};

int main() {
    Driver driver;
    driver.StartGame();
    return 0;
}