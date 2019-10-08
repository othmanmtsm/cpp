#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::ifstream;
using std::istringstream;
using std::sort;
using std::string;
using std::vector;

enum class State
{
    kEmpty,
    kObstacle,
    kClosed,
    kPath,
    kStart,
    kFinish
};



string CellString(State square)
{
    switch (square)
    {
    case State::kObstacle:
        return "/\\  ";
        break;
    case State::kPath:
        return "1   ";
        break;
    case State::kStart:
        return "S   ";
        break;
    case State::kFinish:
        return "F   ";
        break;
    default:
        return "0   ";
        break;
    }
}

void PrintBoard(vector<vector<State>> b)
{
    for (auto v : b)
    {
        for (auto i : v)
        {
            cout << CellString(i);
        }
        cout << "\n";
    }
}

vector<vector<State>> Parseline(string path)
{
    string a;
    ifstream my_file;
    my_file.open(path);
    vector<vector<State>> v;
    if (my_file)
    {
        string line;
        while (getline(my_file, line))
        {
            istringstream my_stream(line);
            int a;
            char c;
            vector<State> test;
            while (my_stream >> a >> c)
            {
                if (a == 0)
                {
                    test.push_back(State::kEmpty);
                }
                else
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



const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

//the Manhattan Distance from one coordinate to the other: |x2-x1|+|y2-y1|
int heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

bool CheckValidCell(int x, int y, vector<vector<State>> &grid)
{
    bool gx = ((x >= 0) && (x < grid.size()));
    bool gy = ((y >= 0) && (y < grid[0].size()));
    if (gx && gy)
        return grid[x][y] == State::kEmpty;
    return false;
}

void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &o_nodes, vector<vector<State>> &grid)
{
    vector<int> node{x, y, g, h};
    o_nodes.push_back(node);
    grid[x][y] = State::kClosed;
}

bool Compare(vector<int> v1, vector<int> v2)
{
    int f1 = v1[2] + v1[3];
    int f2 = v2[2] + v2[3];
    return f1 > f2;
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<vector<int>> *v)
{
    sort(v->begin(), v->end(), Compare);
}

void ExpandNeighbors(vector<int> &curr_node,vector<vector<int>> &open, vector<vector<State>> &grid, int goal[]){
    int cx {curr_node[0]};
    int cy {curr_node[1]};
    int cg {curr_node[2]};
    
    for (int i = 0; i < 4; i++) 
    {
        int x2 = cx + delta[i][0];
        int y2 = cy + delta[i][1];
        if ( CheckValidCell(x2, y2, grid) )
        {
            int h = heuristic(x2, y2, goal[0], goal[1]);
            AddToOpen(x2, y2, cg+1, h, open, grid); //increment g
        }
    }
}

vector<vector<State>> Search(vector<vector<State>> grid, int init[], int goal[])
{
    vector<vector<int>> open{};

    int x{init[0]};
    int y{init[1]};
    int g = 0;

    int h = heuristic(x, y, goal[0], goal[1]);

    AddToOpen(x, y, g, h, open, grid);

    while (!open.empty())
    {
        CellSort(&open);
        vector<int> curr_node = open.back(); //gets the lastelement in the vector
        open.pop_back();                     //deletes last element in the vector

        //gets x and y of the current node
        int x{curr_node[0]};
        int y{curr_node[1]};

        grid[x][y] = State::kPath;

        if (x == goal[0] && y == goal[1]){
            grid[init[0]][init[1]] = State::kStart;
            grid[goal[0]][goal[1]] = State::kFinish;
            return grid;
        }
        
        ExpandNeighbors(curr_node, open, grid, goal);
    }

    cout << "No path found !!" << std::endl;
    return vector<vector<State>>{};
}

int main()
{
    int init[]{0, 0};
    int goal[]{4, 5};
    vector<vector<State>> a{Parseline("./1.board")};
    vector<vector<State>> solution = Search(a, init, goal);
    PrintBoard(solution);
}