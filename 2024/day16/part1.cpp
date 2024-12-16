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

// long move(vector<vector<char>>& map, int i, int j, long res, int acci, int accj,set<pair<int,int>> set_mvt) {
//     cout << "i, j: "<<i<<", "<<j<< ", acci, accj: "<<acci<<", "<<accj<<endl;
//     if (map[i][j]=='E') {
//         return res;
//     }
//     // if (map[i][j]=='#') {
//     //     return LONG_MAX;
//     // }
//     long rl=LONG_MAX;
//     long ud=LONG_MAX;
//     long u=LONG_MAX;
//     long d=LONG_MAX;
//     long r=LONG_MAX;
//     long l=LONG_MAX;
//     if (acci==0) {
//         pair<int,int> nxtRL=make_pair(i,j+accj);
//         pair<int,int> nxtU=make_pair(i+1,j);
//         pair<int,int> nxtD=make_pair(i-1,j);
//         if (map[i][j+accj]!='#' && set_mvt.count(nxtRL)==0) {
//             set_mvt.insert(nxtRL);
//             rl=move(map, i,j+accj,res+1,0,accj,set_mvt);
//         } 
//         if (map[i+1][j]!='#'&& set_mvt.count(nxtU)==0) {
//             set_mvt.insert(nxtU);
//             u=move(map, i+1,j,res+1001,1,0,set_mvt);
//         }    
//         if (map[i-1][j]!='#'&& set_mvt.count(nxtD)==0) {
//             set_mvt.insert(nxtD);
//             d=move(map, i-1,j,res+1001,-1,0,set_mvt);
//         }
//         return min(rl,min(u,d));
//     }
//     else {
//         pair<int,int> nxtUD=make_pair(i+acci,j);
//         pair<int,int> nxtR=make_pair(i,j+1);
//         pair<int,int> nxtL=make_pair(i,j-1);
//         if (map[i+acci][j]!='#'&& set_mvt.count(nxtUD)==0) {
//             set_mvt.insert(nxtUD);
//             ud=move(map, i+acci,j,res+1,acci,0,set_mvt);
//         } 
//         if (map[i][j+1]!='#'&& set_mvt.count(nxtR)==0) {
//             set_mvt.insert(nxtR);
//             r=move(map, i,j+1,res+1001, 0,1,set_mvt);
//         }    
//         if (map[i][j-1]!='#'&& set_mvt.count(nxtL)==0) {
//             set_mvt.insert(nxtL);
//             l=move(map, i,j-1,res+1001,0,-1,set_mvt);
//         }
//         return min(ud,min(r,l));
//     }
// }

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

long bfs(vector<vector<char>>& map, int iStart, int jStart, int iEnd, int jEnd) 
{
    // Create a queue for BFS
    queue<tuple<int,int,int,int,int>> q;  
    
    // Initially mark all the vertices as not visited
    // When we push a vertex into the q, we mark it as 
    // visited
    vector<vector<long>> visited;
    for (unsigned long i=0; i<map.size();i++) {
        vector<long> line_visited(map[0].size(), LONG_MAX);
        visited.push_back(line_visited);
    }

    // Mark the source node as visited and 
    // enqueue it
    int acci=0;
    int accj=1;
    visited[iStart][jStart] = 0;
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
            long old_w = visited[ni][nj];
            if (new_w < old_w) {
                visited[ni][nj]=new_w;
                q.push(make_tuple(ni,nj,nacci,naccj,new_w));
            }
        }
    }
    return visited[iEnd][jEnd];
}

int main() {
    ifstream file("input.txt");

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
    // cout << iStart<<", "<<jStart<<endl;
    set<pair<int,int>> set_mvt;
    // long res = move(map,iStart,jStart,0,0,1,set_mvt);
    long res = bfs(map,iStart,jStart,iEnd, jEnd);

    auto stop = chrono::high_resolution_clock::now();

    cout << "result: " <<res<<endl;
    // printf("%20.llu\n",res);
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time: " << duration.count() << "ms" << endl;

    return 0;
}