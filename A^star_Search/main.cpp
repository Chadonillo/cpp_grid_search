#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using std::istringstream;
using std::string;
using std::ifstream;
using std::vector;
using std::cout;

enum class State {kEmpty, kObstacle, kClosed, kPath, kGoal, kStart, kUnknown};
const int deltas[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

string CellString(State currState){
    switch (currState){
        case State::kObstacle: return "⛰️";
        break;
        case State::kEmpty: return "⬛";
        break;
        case State::kClosed: return "🚧";
        break;
        case State::kPath: return "🚘";
        break;
        case State::kGoal: return "🏁";
        break;
        case State::kStart: return "🚦";
        break;
        default: return "?";
    }
}

void PrintBoard(const vector<vector<State>> &board){
    for(const vector<State> &row: board){
        for(const State &data: row){
            cout << CellString(data) << "\t";
        }
        cout << "\n";
    }
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

class Node{
    public:
        int x;
        int y;
        int g;
        int h;
        Node(int x, int y){
            this->x = x;
            this->y = y;
        }
        std::string toString() {
            std::ostringstream strout;
            strout<< "x: " << x << "  y: " << y << "  g: " << g << "  h: " << h;
            return strout.str();
        }
        bool operator <(const Node& compNode)const{
            return (g+h)<(compNode.g+compNode.h);
        }
        bool operator >(const Node& compNode)const{
            return (g+h)>(compNode.g+compNode.h);
        }
        bool operator ==(const Node& compNode)const{
            return (compNode.y==y) and (compNode.x==x);
        }
        int ManhattanDistance(const Node &toNode){
            return abs(toNode.x - this->x) + abs(toNode.y - this->y); 
        }
        void SetCost(const int &g, const Node &toNode){
            this->g = g;
            this->h = this->ManhattanDistance(toNode);
        }
};

void CellSort(vector<Node> *v) {
  sort(v->begin(), v->end(), std::greater<>());
}

bool CheckValidCell(Node &currNode, vector<vector<State>> &grid) {
  bool on_grid_x = (currNode.x >= 0 && currNode.x < grid.size());
  bool on_grid_y = (currNode.y >= 0 && currNode.y < grid[0].size());
  if (on_grid_x && on_grid_y)
    return grid[currNode.x][currNode.y] == State::kEmpty;
  return false;
}
void addToOpen(Node currNode, vector<Node> &openList, vector<vector<State>> &grid){
    openList.push_back(currNode);
    grid[currNode.x][currNode.y]=State::kClosed;
}

void ExpandNeighbors(Node &currNode, vector<Node> &openList, vector<vector<State>> &grid , Node &goalNode){
    for (auto delta:deltas){
        int new_x = delta[0]+currNode.x;
        int new_y = delta[1]+currNode.y;
        Node newNode = Node(new_x, new_y);
        if(CheckValidCell(newNode, grid)){
            newNode.SetCost(currNode.g+1, goalNode);
            addToOpen(newNode, openList, grid);
        }
    }
}

void AddStartStop(vector<vector<State>> &map, Node &startNode, Node &goalNode){
    map[startNode.x][startNode.y]=State::kStart;
    map[goalNode.x][goalNode.y]=State::kGoal;
}

vector<vector<State>> Search(vector<vector<State>> map, Node &startNode, Node &goalNode){
    vector<Node> openList {};
    startNode.SetCost(0, goalNode);
    addToOpen(startNode, openList, map);

    while(not openList.empty()){
        CellSort(&openList);
        Node currNode = openList.back();
        openList.pop_back();
        map[currNode.x][currNode.y]=State::kPath;
        if (currNode == goalNode){
            cout << "Goal Found\n";
            return map;
        }
        ExpandNeighbors(currNode, openList, map, goalNode);
        
    }
    cout << "Goal Not Found\n";
    return map;
}

int main() {
    vector<vector<State>> board1 = ReadBoardFile("1");
    Node startNode = Node(0, 0);
    Node goalNode = Node(4, 5);
    vector<vector<State>> solution = Search(board1, startNode, goalNode);
    AddStartStop(solution, startNode, goalNode);
    PrintBoard(solution);
}