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


void PrintBoard(vector<vector<int>> b){
    cout << "printing board from a local vector \n";
    for(auto v : b){
        for(int i : v){
            cout << i;
        }
        cout << "\n";
    }
}


vector<int> Parseline(string path){
    string a;
    ifstream my_file(path);
    if (my_file)
    {
        string line;
        while (getline(my_file,line))
        {
            a += line;
        }
    }
    istringstream my_stream (a);
    int n;
    char c;
    vector <int> v;
    while(my_stream >> n >> c){
        v.push_back(n);
    }
    return v;
}


int main(){
    vector<int> a {Parseline("./files/1.board")};
    for (int i : a)
    {
        cout << i << "\n";
    }
    
}