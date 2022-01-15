#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <stack>
#include <vector>

#include "colors.hpp"

using namespace std;

// store ascii values of a, d, w, s in left, right, top, bottom respectively
enum MOVES { LEFT = 97, RIGHT = 100, TOP = 119, BOTTOM = 115};

class Game
{
    private:
        vector<vector<int> > game_state;
        int grid_size;
        int winning_score;
        int base_value;
        vector<int> moves;

        void MakeLeftRightMove(int move) {
            int i = 0, j = 0;
            stack<int> s;
            int curr, next;
            while (i < this->grid_size) {
                if (move == LEFT) {
                    j = this->grid_size-1;
                    while (j >= 0) {
                        if (this->game_state[i][j] != 0) {
                            s.push(game_state[i][j]);
                            game_state[i][j] = 0;
                        }
                        j--;
                    }
                    j = 0;
                } else if (move == RIGHT) {
                    j = 0;
                    while (j < this->grid_size) {
                        if (this->game_state[i][j] != 0) {
                            s.push(game_state[i][j]);
                            game_state[i][j] = 0;
                        }
                        j++;
                    }
                    j = this->grid_size-1;
                }
                while (!s.empty()) {
                    curr = s.top();
                    s.pop();
                    if (s.empty()) {
                        this->game_state[i][j] = curr;
                        break;
                    } else {
                        next = s.top();
                        s.pop();
                        if (curr == next) {
                            // collision case
                            this->game_state[i][j] = 2 * curr;
                        } else {
                            // non-collision case
                            this->game_state[i][j] = curr;
                            s.push(next);
                        }
                        if (move == LEFT)
                            j++;
                        else if (move == RIGHT)
                            j--;
                    }
                }
                i++;
            }
            return;
        }

        void MakeTopBottomMove(int move){
            int i = 0, j = 0;
            stack<int> s;
            int curr, next;
            while (j < this->grid_size) {
                if (move == TOP) {
                    i = this->grid_size-1;
                    while (i >= 0) {
                        if (this->game_state[i][j] != 0) {
                            s.push(game_state[i][j]);
                            game_state[i][j] = 0;
                        }
                        i--;
                    }
                    i = 0;
                } else if (move == BOTTOM) {
                    i = 0;
                    while (i < this->grid_size) {
                        if (this->game_state[i][j] != 0) {
                            s.push(game_state[i][j]);
                            game_state[i][j] = 0;
                        }
                        i++; 
                    }
                    i = this->grid_size-1;
                }
                while (!s.empty()) {
                    curr = s.top();
                    s.pop();
                    if (s.empty()) {
                        this->game_state[i][j] = curr;
                        break;
                    } else {
                        next = s.top();
                        s.pop();
                        if (curr == next) {
                            // collision case
                            this->game_state[i][j] = 2 * curr;
                        } else {
                            // non-collision case
                            this->game_state[i][j] = curr;
                            s.push(next);
                        }
                        if (move == TOP)
                            i++;
                        else if (move == BOTTOM)
                            i--;
                    }
                }
                j++;
            }
            return;
        }


    public:
        void Restart(int grid_size, int winning_score, int base_value) {
            for (int i=0; i<grid_size; i++) {
                for (int j=0; j<grid_size; j++) {
                    this->game_state[i][j] = 0;
                }
            }
            this->DisplayGameState();
            return;
        }

        Game(int grid_size, int winning_score, int base_value) {
            vector<int> temp(grid_size, 0);
            this->grid_size = grid_size;
            for (int i=0; i<grid_size; i++) {
               this->game_state.push_back(temp);
            }
            this->winning_score = winning_score;
            this->base_value = base_value;
            this->moves.clear();
            return;
        }

        void DisplayGameState() {
            cout << BLUE;
            for (int i = 0; i <= 2 * this->grid_size; i++) {
                for (int j = 0; j <= 2 * this->grid_size; j++) {
                    if (i % 2 == 0) {
                        cout << "--";
                    } else {
                        if (j % 2 == 0) {
                            cout << "|";
                        } else {
                            cout << GREEN << " " << this->game_state[i/2][j/2] << " " << BLUE;
                        }
                    }
                }
                cout << endl;
            }
            cout << RESET;
            return;
        }

        bool IsGameEnd() {
            int empty_squares = 0;
            for (int i=0; i<this->grid_size; i++) {
                for (int j=0; j<this->grid_size; j++) {
                    if (this->game_state[i][j] == this->winning_score) {
                        this->DisplayGameState();
                        cout << GREEN << "Congratulations" << RESET << endl;
                        return true;
                    } else if (this->game_state[i][j] == 0) {
                        empty_squares++;
                    }
                }
            }
            if (empty_squares != 0){
                return false;
            }
            // all squares filled case
            int curr, right, down; 
            for (int i=0; i<this->grid_size; i++) {
                for (int j=0; j<this->grid_size; j++) {
                    curr = this->game_state[i][j];
                    right = 0;
                    down = 0;
                    if (j+1 <this->grid_size) {
                        right = this->game_state[i][j+1];
                    }
                    if (i+1 < this->grid_size) {
                        down = this->game_state[i+1][j];
                    }
                    if (curr == right || curr == down) {
                        return false;
                    }
                }
            }
            this->DisplayGameState();
            cout << RED << "Game Over" << RESET << endl;
            return true;
        }

        void GenerateRandomTile() {
            vector<pair<int,int> > empty_squares;

            for (int i=0; i<this->grid_size; i++) {
                for (int j=0; j<this->grid_size; j++) {
                    if (this->game_state[i][j] == 0) {
                        empty_squares.push_back(make_pair(i,j));
                    }
                }
            }
            srand(time(0));
            int rand_idx = rand()%empty_squares.size();
            int x = empty_squares[rand_idx].first;
            int y = empty_squares[rand_idx].second;
            this->game_state[x][y] = this->base_value;
            return;
        }

        void MakeMove(int move) {
            switch (move)
            {
            case LEFT:
                this->MakeLeftRightMove(move);
                break;
            case RIGHT:
                this->MakeLeftRightMove(move);
                break;
            case TOP:
                this->MakeTopBottomMove(move);
                break;
            case BOTTOM:
                this->MakeTopBottomMove(move);
                break;
            default:
                break;
            }
            this->moves.push_back(move);
            return;
        }
};