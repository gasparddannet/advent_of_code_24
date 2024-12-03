#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <utility>
#include <algorithm>

using namespace std;

int main() { 
    ifstream file("input.txt");
    string str; 
    string del = "   ";
    vector<pair<int, int>> v1, v2;
    while (getline(file, str)) {
        auto pos = str.find(del);

        v1.push_back(make_pair(stoi(str.substr(0, pos)), v1.size()));
        str.erase(0, pos + del.length());
        v2.push_back(make_pair(stoi(str), v2.size()));
        
        }
    
    assert(v1.size() == v2.size());

}