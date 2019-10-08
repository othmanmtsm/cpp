#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::cout;
using std::vector;
using std::string;
using std::istringstream;

enum class State {kEmpty, kObstacle, kClosed};

string CellString(State square){
    switch (square)
    {
    case State::kObstacle : return "/\\  ";
        break;
    default: return "0   ";
        break;
    }
}

void PrintBoard(vector<vector<State>> b){
    for(auto v : b){
        for(auto i : v){
            cout << CellString(i);
        }
        cout << "\n";
    }
}


vector<vector<State>> Parseline(string path){
    string a;
    ifstream my_file;
    my_file.open(path);
    vector <vector<State>> v;
    if (my_file)
    {
        string line;
        while (getline(my_file,line))
        {
            istringstream my_stream(line);
            int a;
            char c;
            vector <State> test;
            while (my_stream >> a >> c)
            { 
                if (a == 0)
                {
                    test.push_back(State::kEmpty);
                }else
                {
                    test.push_back(State::kObstacle);
                }  
            }
            v.push_back(test);
        }
    }
    return v;
}

// A STAR


//the Manhattan Distance from one coordinate to the other: |x2-x1|+|y2-y1|
int heuristic(int x1,int y1,int x2,int y2){
    return abs(x2-x1) + abs(y2-y1);
}

void AddToOpen(int x,int y, int g,int h,vector<vector<int>> &o_nodes,vector<vector<State>> &grid){
    vector<int> node{x,y,g,h};
    o_nodes.push_back(node);
    grid[x][y] = State::kClosed;
}

vector<vector<State>> Search(vector<vector<State>> Board, int init[], int goal[]){
    
    vector<vector<int>> open{};

    int x{init[0]};
    int y{init[1]};
    int g = 0;

    int h = heuristic(x,y,goal[0],goal[1]);

    AddToOpen(x,y,g,h,open,Board);

    cout << "No path found !!" << std::endl;
    return vector<vector<State>>{};
}

int main(){
    int init[]{0,0};
    int goal[]{4,5};
    vector<vector<State>> a {Parseline("./files/1.board")};
    vector<vector<State>> solution = Search(a,init,goal);
    PrintBoard(solution);
}