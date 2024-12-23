#include <chrono>
#include <climits>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <cmath>
#include <list>
#include <queue>

using namespace std;

int NBL=71;
int NBC=71;
// int NBL=7;
// int NBC=7;

void print_map(vector<vector<char>>& map) {
    for (vector<char>& line:map) {
        for (char& c:line) {
            cout << c;
        }
        cout<<endl;
    }
    cout<<endl;
}

list<pair<int,int>> get_adjacents(vector<vector<char>>& map, int i, int j) {
    list<pair<int, int>> lst_adj;
    if (i+1<NBL && map[i+1][j] != '#') {
        lst_adj.push_back(make_pair(i+1,j));
    }
    if (i-1>=0 && map[i-1][j] != '#') {
        lst_adj.push_back(make_pair(i-1,j));
    }
    if (j+1<NBC && map[i][j+1] != '#') {
        lst_adj.push_back(make_pair(i,j+1));
    }
    if (j-1>=0 && map[i][j-1] != '#') {
        lst_adj.push_back(make_pair(i,j-1));
    }
    return lst_adj;
}

int bfs(vector<vector<char>>& map, int iStart, int jStart) {
    queue<pair<int,int>> q;  
    vector<vector<bool>> visited;
    for (unsigned int i=0;i<map.size();i++) {
        vector<bool> line_visited(map[0].size(),false);
        visited.push_back(line_visited);
    }

    visited[iStart][jStart] = true;
    q.push(make_pair(iStart, jStart));

    while (!q.empty()) {
        pair<int,int> curr = q.front();
        q.pop();
        // cout << "curr: "<<curr.first << ", "<<curr.second<<endl;
        list<pair<int,int>> lst_adj = get_adjacents(map, curr.first, curr.second);
        for (pair<int,int> p:lst_adj) {
            // cout << "adj: "<<p.first <<", "<<p.second<<endl;
            if (!visited[p.first][p.second]) {
                visited[p.first][p.second]=true;
                q.push(p);
            }
        }
    }
    return visited[NBL-1][NBC-1];
}

void add_byte(vector<vector<char>>& map, pair<int,int> byte) {
    map[byte.second][byte.first]='#';
}

int main() {
    ifstream file("input.txt");

    if (!file.is_open()) {
    cout << "Could not open file!\n";
    return 1;
    }
    string line, s;
    vector<pair<int,int>> vct_bytes;
    while (getline(file,line)) {
        pair<int,int> p;
        stringstream ss(line);
        getline(ss, s, ',');
        p.first = stoi(s);
        getline(ss, s, ',');
        p.second = stoi(s);
        vct_bytes.push_back(p);
    }
    file.close();

    // for (pair<int,int> p:vct_bytes) {
    //     cout << p.first <<", "<<p.second<<endl;
    // }

    vector<vector<char>> map;
    for (int i=0;i<NBL;i++) {
        vector<char> line_map(NBC,'.');
        map.push_back(line_map);
    }

    // print_map(map);

    auto start = chrono::high_resolution_clock::now();

    unsigned int i=0;
    bool is_possible = bfs(map,0,0);
    while (is_possible && i<vct_bytes.size()) {
        add_byte(map, vct_bytes[i]);
        is_possible = bfs(map,0,0);
        i++;
    }
    cout << "i: "<<i-1<<endl;
    cout << "res: " <<vct_bytes[i-1].first <<","<<vct_bytes[i-1].second<<endl;

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time: " << duration.count() << "ms" << endl;

    return 0;
}