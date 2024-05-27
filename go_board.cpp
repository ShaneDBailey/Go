#include <iostream>
#include <vector>


const int BOARD_SIZE = 9;

enum class Stone {NONE, BLACK, WHITE};

class GoBoard {
    
    private:
        Stone board[BOARD_SIZE][BOARD_SIZE];
        Stone player;

    public:
        GoBoard() {
            for (int row = 0; row < BOARD_SIZE; ++row) {
                for (int column = 0; column < BOARD_SIZE; ++column) {
                    this->board[row][column] = Stone::NONE;
                }
            }

            this->player = Stone::WHITE;
        }

        void user_input() {
            std::cout << "It is player " << (this->player == Stone::WHITE ? "WHITE" : "BLACK") << "'s move." << std::endl;
            int row;
            int column;
            std::cout << "Enter row and column (0-8): ";
            std::cin >> row >> column;

            if (is_valid_move(row,column,this->player)) {
                place_stone(row, column);

            } else {
                std::cout << "Invalid input." <<std::endl << "Please enter row and column within the range 0-8, that is a free space." << std::endl;
            }
        }

        void place_stone(int row, int column){
            this->board[row][column] = this->player;
            Stone opponent = (this->player == Stone::WHITE) ? Stone::BLACK : Stone::WHITE;
            handle_captures(opponent);
            handle_captures(this->player);
            this->player = (this->player == Stone::WHITE) ? Stone::BLACK : Stone::WHITE;

        };

        void handle_captures(Stone opponent) {
            bool has_visited[BOARD_SIZE][BOARD_SIZE] = {false};
            
            for (int row = 0; row < BOARD_SIZE; row++) {
                for (int column = 0; column < BOARD_SIZE; column++) {
                    if (!has_visited[row][column] && board[row][column] == opponent) {
                        std::vector<std::pair<int, int>> connected;
                        find_connected_stones(row, column, opponent, connected, has_visited);
                        
                        if (is_surrounded(connected)) {
                            remove_group(connected);
                        }
                    }
                }
            }
        };

        void find_connected_stones(int row, int column, Stone stone, std::vector<std::pair<int, int>>& connected, bool (&has_visited)[BOARD_SIZE][BOARD_SIZE]) {
            if (row < 0 || row >= BOARD_SIZE || column < 0 || column >= BOARD_SIZE || has_visited[row][column] || this->board[row][column] != stone) {
                return;
            }
            
            has_visited[row][column] = true;
            connected.push_back({row, column});

            find_connected_stones(row - 1, column, stone, connected, has_visited); // Up
            find_connected_stones(row + 1, column, stone, connected, has_visited); // Down
            find_connected_stones(row, column - 1, stone, connected, has_visited); // Left
            find_connected_stones(row, column + 1, stone, connected, has_visited); // Right
        };

        bool is_surrounded(const std::vector<std::pair<int, int>>& connected) {
            for (const auto& stone : connected) {
                int row = stone.first;
                int column = stone.second;
                
                if (row - 1 >= 0 && board[row - 1][column] == Stone::NONE) return false;            // Up
                if (row + 1 < BOARD_SIZE && board[row + 1][column] == Stone::NONE) return false;    // Down
                if (column - 1 >= 0 && board[row][column - 1] == Stone::NONE) return false;         // Left
                if (column + 1 < BOARD_SIZE && board[row][column + 1] == Stone::NONE) return false; // Right
            }
            
            return true;
        };

        void remove_group(const std::vector<std::pair<int, int>>& connected) {
            for (const auto& stone : connected) {
                int row = stone.first;
                int column = stone.second;
                board[row][column] = Stone::NONE;
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

