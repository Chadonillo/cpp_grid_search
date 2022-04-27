#include <iostream>
#include <vector>
using std::vector;
using std::cout;

void PrintBoard (const vector<vector<int>> &board){
    for(const vector<int> &row: board){
        for(const int &data: row){
            cout << data;
        }
        cout << "\n";
    }
    return;
}

vector<vector<int>> SimpleBoard(){
    vector<vector<int>> board{{0, 1, 0, 0, 0, 0},
                              {0, 1, 0, 0, 0, 0},
                              {0, 1, 0, 0, 0, 0},
                              {0, 1, 0, 0, 0, 0},
                              {0, 0, 0, 0, 1, 0}};
    return board;
}

int main() {
    vector<vector<int>> board = SimpleBoard();
    PrintBoard(board);
}