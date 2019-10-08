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
    kPath
};

string CellString(State square)
{
    switch (square)
    {
    case State::kObstacle:
        return "/\\  ";
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

        if (x == goal[0] && y == goal[1])
            return grid;
    }

    cout << "No path found !!" << std::endl;
    return vector<vector<State>>{};
}

bool CheckValidCell(int x, int y, vector<vector<State>> &grid)
{
    bool gx = ((x >= 0) && (x <= grid.size()));
    bool gy = ((y >= 0) && (y <= grid[0].size()));
    if (gx && gy)
        return grid[x][y] == State::kEmpty;
    return false;
}

//the Manhattan Distance from one coordinate to the other: |x2-x1|+|y2-y1|
int heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &o_nodes, vector<vector<State>> &grid)
{
    vector<int> node{x, y, g, h};
    o_nodes.push_back(node);
    grid[x][y] = State::kClosed;
}

bool Compare(vector<int> v1, vector<int> v2)
{
    return (v1[2] + v1[3]) > (v2[2] + v2[3]);
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<vector<int>> *v)
{
    sort(v->begin(), v->end(), Compare);
}

int main()
{
    int init[]{0, 0};
    int goal[]{4, 5};
    vector<vector<State>> a{Parseline("./files/1.board")};
    vector<vector<State>> solution = Search(a, init, goal);
    PrintBoard(solution);
}