#include <chrono>
#include <climits>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <list>
#include <queue>
#include <map>

using namespace std;

typedef pair<int,int> iPair;
typedef pair<int, pair<int,int>> dijPair;
// typedef pair<iPair,iPair> cheatPair;

void print_map(vector<vector<char>>& map) {
    for (vector<char>& line:map) {
        for (char& c:line) {
            cout << c;
        }
        cout<<endl;
    }
    cout<<endl;
}

list<iPair> get_adjacents(vector<vector<char>>& map, iPair ij) {
    list<iPair> lst_adj;
    int i=ij.first;
    int j=ij.second;
    int n=map.size();
    int m=map[0].size();
    if (i+1<n && map[i+1][j] != '#') {
        lst_adj.push_back(make_pair(i+1,j));
    }
    if (i-1>=0 && map[i-1][j] != '#') {
        lst_adj.push_back(make_pair(i-1,j));
    }
    if (j+1<m && map[i][j+1] != '#') {
        lst_adj.push_back(make_pair(i,j+1));
    }
    if (j-1>=0 && map[i][j-1] != '#') {
        lst_adj.push_back(make_pair(i,j-1));
    }
    return lst_adj;
}

list<iPair> get_adjacents_blocks(vector<vector<char>>& map, iPair ij) {
    list<iPair> lst_adj;
    int i=ij.first;
    int j=ij.second;
    if (map[i+1][j] == '#') {
        lst_adj.push_back(make_pair(i+1,j));
    }
    if (map[i-1][j] == '#') {
        lst_adj.push_back(make_pair(i-1,j));
    }
    if (map[i][j+1] == '#') {
        lst_adj.push_back(make_pair(i,j+1));
    }
    if (map[i][j-1] == '#') {
        lst_adj.push_back(make_pair(i,j-1));
    }
    return lst_adj;
}

int dijkstra(vector<vector<char>>& map, iPair start, iPair end) {
    // queue<pair<int,int>> q;  
    priority_queue<dijPair, vector<dijPair>, greater<dijPair>> pq;

    vector<vector<int>> dist;
    for (unsigned int i=0;i<map.size();i++) {
        vector<int> line_dist(map[0].size(),INT_MAX);
        dist.push_back(line_dist);
    }

    dist[start.first][start.second] = 0;
    pq.push(make_pair(0,start));

    while (!pq.empty()) {
      
        iPair curr = pq.top().second;
        pq.pop();
        // cout << "curr: "<<curr.first << ", "<<curr.second<<endl;
        list<iPair> lst_adj = get_adjacents(map, curr);
        for (iPair neighbor:lst_adj) {
            // cout << "adj: "<<p.first <<", "<<p.second<<endl;
            int old_w = dist[neighbor.first][neighbor.second];
            int new_w = dist[curr.first][curr.second]+1;
            if (new_w<old_w) {
                dist[neighbor.first][neighbor.second]=new_w;
                pq.push(make_pair(new_w, neighbor));
            }
        }
    }
    return dist[end.first][end.second];
}

int main() {
    ifstream file("input.txt");

    if (!file.is_open()) {
    cout << "Could not open file!\n";
    return 1;
    }
    string line;
    iPair start, end;
    int i=0;
    int j;
    vector<vector<char>> mapMaze;
    while (getline(file,line)) {
        vector<char> line_map;
        j=0;
        for (unsigned int k=0;k<line.length();k++) {
            line_map.push_back(line[k]);
            if (line[k]=='S') {
                start = make_pair(i,j);
            }
            else if (line[k]=='E') {
                end = make_pair(i,j);
            }
            j++;
        }
        mapMaze.push_back(line_map);
        i++;
    }
    file.close();

    print_map(mapMaze);
    cout << "start: " << start.first << ", "<<start.second<<endl;
    cout << "end: " << end.first << ", "<<end.second<<endl;

    auto tstart = chrono::high_resolution_clock::now();

    int no_cheat_time = dijkstra(mapMaze,start,end);
    cout << "no_cheat_time: "<<no_cheat_time<<endl;

    // list<cheatPair> lst_cheat;
    list<iPair> lst_cheat;
    for (unsigned int i=1;i<mapMaze.size()-1;i++) {
        for (unsigned int j=1;j<mapMaze[0].size()-1;j++) {
            iPair ij = make_pair(i,j);
            if (mapMaze[i][j]=='#') {
                list<iPair> lst_ajd = get_adjacents(mapMaze,ij);
                // for (iPair adj:lst_ajd) {
                //     lst_cheat.push_back(make_pair(ij, adj));
                // }
                lst_cheat.push_back(ij);



                // list<iPair> lst_block_ajd = get_adjacents_blocks(map,ij);
                // for (iPair ip:lst_block_ajd) {
                //     list<iPair> lst_adj2 = get_adjacents(map,ip);
                //     if (!lst_adj2.empty()) {
                //         lst_cheat.push_back(make_pair(ij, ip));
                //     }
                // }
            }
        }
    }
    cout << "lst_cheats.size(): "<<lst_cheat.size()<<endl;

    map<int, int> map_cheat_times;

    for (iPair cheat:lst_cheat) {
        vector<vector<char> > map_copy = mapMaze;
        // iPair c1 = cheat.first;
        // iPair c2 = cheat.second;
        // cout << "c1: "<<c1.first<<", "<<c1.second<<endl;
        // cout << "c2: "<<c2.first<<", "<<c2.second<<endl;
        map_copy[cheat.first][cheat.second]='.';
        // map_copy[c2.first][c2.second]='.';
        int res = dijkstra(map_copy,start,end);
        // cout << "diff:" <<no_cheat_time-res<<endl;
        if (res<no_cheat_time) {
            // vct_cheat_times.push_back(res-no_cheat_time);
            // cout << "res: "<<res<<endl;
            map_cheat_times[no_cheat_time-res]++;
        }
    }

    int res=0;
    for (pair<int,int> p:map_cheat_times) {
        // cout << p.first << ": "<<p.second <<endl;
        if (p.first >= 100) {
            res+=p.second;
        }
    }

    auto tstop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(tstop - tstart);
    cout << "result: "<<res<<endl;
    cout << "time: " << duration.count() << " microseconds" << endl;

    return 0;
}