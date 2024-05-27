#include <iostream>

const int BOARD_SIZE = 9;

enum class Stone {NONE, BLACK, WHITE};

class GoBoard {
    private:
        Stone board[BOARD_SIZE][BOARD_SIZE];
        Stone player;
    public:
        GoBoard() {
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    board[i][j] = Stone::NONE;
                }
            }

            player = Stone::WHITE;
        }

        void user_input() {
            std::cout << "It is player " << (player == Stone::WHITE ? "WHITE" : "BLACK") << "'s move." << std::endl;
            int row, column;
            std::cout << "Enter row and column (0-8): ";
            std::cin >> row >> column;

            if (row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE) {
                place_stone(row, column, player);

            } else {
                std::cout << "Invalid input. Please enter row and column within the range 0-8." << std::endl;
            }
        }

        void place_stone(int row, int column, Stone stone){
            if(is_valid_move(row,column,stone)){
                this->board[row][column] = stone;
                player = (player == Stone::WHITE) ? Stone::BLACK : Stone::WHITE;
            }else{
                std::cout << "Invalid move" << std::endl;
            }

        };

        bool is_valid_move(int row, int column, Stone stone) {
            if (row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE && board[row][column] == Stone::NONE) {
                return true;
            }
            return false;
        };

        void print_board(){
            for(int row = 0; row < BOARD_SIZE; row++){
                for(int column = 0; column < BOARD_SIZE; column++){
                    switch(this->board[row][column]){
                        case Stone::NONE:
                            std::cout << ".";
                            break;
                        case Stone::BLACK:
                            std::cout << "B";
                            break;
                        case Stone::WHITE:
                            std::cout << "W";
                            break;
                    }
                }
                std::cout << std::endl;
            }

        };

};


int main() {
    GoBoard game;

    while (true) {
        game.print_board();
        game.user_input();
    }
    return 0;
}