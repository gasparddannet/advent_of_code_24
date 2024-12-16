#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <set>
#include <queue>
#include <list>

using namespace std;

void print_map(vector<vector<char>>& map) {
    for (vector<char>& line_map:map) {
        for (char& c:line_map) {
            cout<<c;
        }
        cout<<endl;
    }
    cout << endl;
}

list<tuple<int,int, int,int,int>> lst_next(vector<vector<char>>& map,int i, int j, int acci, int accj) {
    list<tuple<int,int,int,int,int>> lst_next_pos;
    if (acci==0) {
        if (map[i][j+accj]!='#') {
            lst_next_pos.push_back(make_tuple(i,j+accj,0,accj,1));
        }
        if (map[i+1][j]!='#') {
            lst_next_pos.push_back(make_tuple(i+1,j,1,0,1001));
        }
        if (map[i-1][j]!='#') {
            lst_next_pos.push_back(make_tuple(i-1,j,-1,0,1001));
        }
    }
    else if (accj==0) {
        if (map[i+acci][j]!='#') {
            lst_next_pos.push_back(make_tuple(i+acci,j,acci,0,1));
        }
        if (map[i][j+1]!='#') {
            lst_next_pos.push_back(make_tuple(i,j+1,0,1,1001));
        }
        if (map[i][j-1]!='#') {
            lst_next_pos.push_back(make_tuple(i,j-1,0,-1,1001));
        }
    }
    return lst_next_pos;
}

vector<vector<pair<long,set<pair<int,int>>>>> bfs(vector<vector<char>>& map, int iStart, int jStart) 
{
    // Create a queue for BFS
    queue<tuple<int,int,int,int,int>> q;  
    
    // Initially mark all the vertices as not visited
    // When we push a vertex into the q, we mark it as 
    // visited
    vector<vector<pair<long,set<pair<int,int>>>>> visited;
    for (unsigned long i=0; i<map.size();i++) {
        vector<pair<long,set<pair<int,int>>>> line_visited; //(map[0].size(), LONG_MAX);
        for (unsigned long j=0; j<map[0].size();j++) {
            set<pair<int,int>> s;
            pair<long,set<pair<int,int>>> p = make_pair(LONG_MAX, s);
            line_visited.push_back(p);
        }
        visited.push_back(line_visited);
    }

    // Mark the source node as visited and 
    // enqueue it
    int acci=0;
    int accj=1;
    visited[iStart][jStart].first = 0;
    q.push(make_tuple(iStart,jStart, acci, accj,0));

    // Iterate over the queue
    while (!q.empty()) {
      
        // Dequeue a vertex from queue and print it
        tuple<int,int,int,int,int> curr = q.front();
        q.pop();
        int i=get<0>(curr);
        int j=get<1>(curr);
        int acci=get<2>(curr);
        int accj=get<3>(curr);
        long w=get<4>(curr);
        int ni,nj,nacci,naccj;
        // cout << "i,j: "<<i <<", "<<j<<endl;
        // Get all adjacent vertices of the dequeued 
        // vertex curr If an adjacent has not been 
        // visited, mark it visited and enqueue it
        
        list<tuple<int,int,int,int,int>> neighbours = lst_next(map,i,j,acci,accj);
        for (tuple<int,int,int,int,int> t:neighbours) {
            long new_w = w + get<4>(t);
            ni=get<0>(t);
            nj=get<1>(t);
            nacci=get<2>(t);
            naccj=get<3>(t);
            long old_w = visited[ni][nj].first;
            set<pair<int,int>> s = visited[ni][nj].second;
            auto p=s.begin();
            if (new_w+1000 == old_w && map[ni+nacci][nj+naccj]=='#') {
                cout << "2ni,nj: "<<ni <<", "<<nj<<endl;
                cout << "2i,j: "<<i <<", "<<j<<endl;
                cout << new_w<<", "<<old_w<<endl;
                visited[ni][nj].second.insert(make_pair(i,j));
                q.push(make_tuple(ni,nj,nacci,naccj,new_w));
            }
            else if (new_w == old_w+1000 && map[ni+(ni-(*p).first)][nj+(ni-(*p).second)]=='#') {
                cout << "3ni,nj: "<<ni <<", "<<nj<<endl;
                cout << "3i,j: "<<i <<", "<<j<<endl;
                cout << new_w<<", "<<old_w<<endl;
                visited[ni][nj].second.insert(make_pair(i,j));
                q.push(make_tuple(ni,nj,nacci,naccj,new_w));
            }

            else if (new_w < old_w) {
                cout << "1ni,nj: "<<ni <<", "<<nj<<endl;
                cout << "1i,j: "<<i <<", "<<j<<endl;
                cout << new_w<<", "<<old_w<<endl;
                visited[ni][nj].first=new_w;
                set<pair<int,int>> s{make_pair(i,j)};
                visited[ni][nj].second = s;
                q.push(make_tuple(ni,nj,nacci,naccj,new_w));
            }
        }
    }
    // return visited[iEnd][jEnd].first;
    return visited;
}

void get_nb_seats(vector<vector<pair<long,set<pair<int,int>>>>>& visited, int i, int j, int iStart, int jStart,set<pair<int,int>>& track) {

    if (i==iStart && j==jStart) {
        track.insert(make_pair(i,j));
    }
    
    set<pair<int,int>> lst = visited[i][j].second;
    for (pair<int,int> p:lst) {
        track.insert(make_pair(p.first,p.second));
        get_nb_seats(visited,p.first,p.second, iStart, jStart,track);

    }
}

int main() {
    ifstream file("example2");

    if (!file.is_open()) {
    cout << "Could not open file!\n";
    return 1;
    }
    string line;;

    vector<vector<char>> map;
    int iStart, jStart, iEnd, jEnd;
    int i=0;

    while (getline(file, line)) {
        vector<char> line_map;
        for (unsigned long j=0; j<line.length();j++) {
            line_map.push_back(line[j]);
            if (line[j] == 'S') {
                iStart = i;
                jStart = j;
            }
            else if (line[j] == 'E') {
                iEnd = i;
                jEnd = j;
            }
        }
        map.push_back(line_map);
        i++;
    }
    file.close();

    auto start = chrono::high_resolution_clock::now();
    print_map(map);
    set<pair<int,int>> set_mvt;
    vector<vector<pair<long,set<pair<int,int>>>>> visited = bfs(map,iStart,jStart);
    long res = visited[iEnd][jEnd].first;

    ofstream myfile;
    set<pair<int,int>> set_track{make_pair(iEnd, jEnd)};
    get_nb_seats(visited, iEnd, jEnd, iStart, jStart,set_track);

    // set<pair<int,int>> l1 = visited[7][5].second;
    // set<pair<int,int>> l1 = visited[9][3].second;
    set<pair<int,int>> l1 = visited[10][3].second;
    // set<pair<int,int>> l1 = visited[iEnd][jEnd].second;
    for (pair<int,int> p:l1) {
        cout << p.first<<", "<<p.second<<endl;
    }

    for (pair<int,int> p:set_track) {
        map[p.first][p.second]='0';
    }

    print_map(map);

    auto stop = chrono::high_resolution_clock::now();

    cout << "result: " <<res<<endl;
    cout << "nb_seats: "<<set_track.size()<<endl;
    // printf("%20.llu\n",res);
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time: " << duration.count() << "ms" << endl;

    return 0;
}