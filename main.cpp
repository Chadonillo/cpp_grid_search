#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using std::istringstream;
using std::string;
using std::ifstream;
using std::vector;
using std::cout;

enum class State {kEmpty, kObstacle, kUnknown};

void PrintBoard (const vector<vector<int>> &board){
    for(const vector<int> &row: board){
        for(const int &data: row){
            cout << data;
        }
        cout << "\n";
    }
    cout << "\n";
    return;
}

vector<int> ParseLineToVector(string line){
    istringstream my_stream(line);
    vector<int> row {};
    int boardChar;
    char comma;
    while(my_stream >> boardChar >> comma){
        if(my_stream){
            row.push_back(boardChar);
        }
    }
    return row;
}

vector<vector<int>> ReadBoardFile(string fileName){
    ifstream board_file;
    vector<vector<int>> board{};
    board_file.open("boards/"+fileName+".board");
    if (board_file){
        string line;
        while (getline(board_file, line)){
            board.push_back(ParseLineToVector(line));
        }
    }
    return board;
}

string CellString(State currState){
    switch (currState){
        case State::kObstacle: return "⛰️ ";
        case State::kEmpty: return "0 ";
        default: return "? ";
    }
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
    vector<vector<int>> board1 = ReadBoardFile("1");
    vector<vector<int>> board2 = SimpleBoard();
    PrintBoard(board1);
    PrintBoard(board2);
    cout << CellString(State::kObstacle) << "\n";
}