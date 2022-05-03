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

string CellString(State currState){
    switch (currState){
        case State::kObstacle: return "█ ";
        break;
        case State::kEmpty: return "- ";
        break;
        default: return "? ";
    }
}

void PrintBoard(const vector<vector<State>> &board){
    for(const vector<State> &row: board){
        for(const State &data: row){
            cout << CellString(data);
        }
        cout << "\n";
    }
    cout << "\n";
    return;
}

vector<State> ParseLineToVector(string line){
    istringstream my_stream(line);
    vector<State> row {};
    int boardChar;
    char comma;
    while(my_stream >> boardChar >> comma){
        if(my_stream){
            State currState;
            switch(boardChar){
                case 1: currState = State::kObstacle;
                break;
                case 0: currState = State::kEmpty;
                break;
                default: State::kUnknown;
            }
            row.push_back(currState);
        }
    }
    return row;
}

vector<vector<State>> ReadBoardFile(string fileName){
    ifstream board_file;
    vector<vector<State>> board{};
    board_file.open("boards/"+fileName+".board");
    if (board_file){
        string line;
        while (getline(board_file, line)){
            board.push_back(ParseLineToVector(line));
        }
    }
    return board;
}

int main() {
    vector<vector<State>> board1 = ReadBoardFile("1");
    PrintBoard(board1);
}