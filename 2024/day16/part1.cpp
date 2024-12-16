#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <set>

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

long move(vector<vector<char>>& map, int i, int j, long res, int acci, int accj,set<pair<int,int>> set_mvt) {
    // cout << "i, j: "<<i<<", "<<j<< ", acci, accj: "<<acci<<", "<<accj<<endl;
    if (map[i][j]=='E') {
        return res;
    }
    // if (map[i][j]=='#') {
    //     return LONG_MAX;
    // }
    long rl=LONG_MAX;
    long ud=LONG_MAX;
    long u=LONG_MAX;
    long d=LONG_MAX;
    long r=LONG_MAX;
    long l=LONG_MAX;
    if (acci==0) {
        pair<int,int> nxtRL=make_pair(i,j+accj);
        pair<int,int> nxtU=make_pair(i+1,j);
        pair<int,int> nxtD=make_pair(i-1,j);
        if (map[i][j+accj]!='#' && set_mvt.count(nxtRL)==0) {
            set_mvt.insert(nxtRL);
            rl=move(map, i,j+accj,res+1,0,accj,set_mvt);
        } 
        if (map[i+1][j]!='#'&& set_mvt.count(nxtU)==0) {
            set_mvt.insert(nxtU);
            u=move(map, i+1,j,res+1001,1,0,set_mvt);
        }    
        if (map[i-1][j]!='#'&& set_mvt.count(nxtD)==0) {
            set_mvt.insert(nxtD);
            d=move(map, i-1,j,res+1001,-1,0,set_mvt);
        }
        return min(rl,min(u,d));
    }
    else {
        pair<int,int> nxtUD=make_pair(i+acci,j);
        pair<int,int> nxtR=make_pair(i,j+1);
        pair<int,int> nxtL=make_pair(i,j-1);
        if (map[i+acci][j]!='#'&& set_mvt.count(nxtUD)==0) {
            set_mvt.insert(nxtUD);
            ud=move(map, i+acci,j,res+1,acci,0,set_mvt);
        } 
        if (map[i][j+1]!='#'&& set_mvt.count(nxtR)==0) {
            set_mvt.insert(nxtR);
            r=move(map, i,j+1,res+1001, 0,1,set_mvt);
        }    
        if (map[i][j-1]!='#'&& set_mvt.count(nxtL)==0) {
            set_mvt.insert(nxtL);
            l=move(map, i,j-1,res+1001,0,-1,set_mvt);
        }
        return min(ud,min(r,l));
    }
}

int main() {
    ifstream file("input.txt");

    if (!file.is_open()) {
    cout << "Could not open file!\n";
    return 1;
    }
    string line;;

    vector<vector<char>> map;
    int iStart, jStart;
    int i=0;

    while (getline(file, line)) {
        vector<char> line_map;
        for (unsigned long j=0; j<line.length();j++) {
            line_map.push_back(line[j]);
            if (line[j] == 'S') {
                iStart = i;
                jStart = j;
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
    long res = move(map,iStart,jStart,0,0,1,set_mvt);

    auto stop = chrono::high_resolution_clock::now();

    cout << "result: " <<res<<endl;
    // printf("%20.llu\n",res);
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time: " << duration.count() << "ms" << endl;

    return 0;
}