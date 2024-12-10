#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>
#include <set>
#include <charconv>

using namespace std;

void print_line(vector<int>& line) {
    for (int& i:line) {
        cout << i;
    }
    cout<<endl;
}

void print_map(vector<vector<int>>& map) {
    for (vector<int>& map_l:map) {
        print_line(map_l);
    }
    cout << endl;
}

void print_vect_pair(vector<pair<int,int>>& vect_p) {
    for (pair<int,int>& p:vect_p) {
        cout << p.first <<", "<<p.second<<endl;
    }
}

void rec_score_trailhead(vector<vector<int>>& map, int i, int j, int hgt, 
                        int& res, set<pair<int,int>>& set_9) {
    int n=map.size(); 
    int m=map[0].size();
    // cout <<"i,j: " <<i<<", "<<j<<endl;

    if (hgt==9 && set_9.count(make_pair(i,j))==0) {
        res++;
        set_9.insert(make_pair(i,j));
        // cout << "res+1"<<endl;
        // cout << "set_9:";
        // for (const pair<int,int>& p:set_9) {
        //     cout << p.first<<","<<p.second<<endl;
        // }
    }
    else {
        if (i+1<n && (map[i+1][j] == (hgt+1))) {
            rec_score_trailhead(map,i+1,j,hgt+1,res,set_9);
        }
        if (j+1<m && (map[i][j+1] == (hgt+1))) {
            rec_score_trailhead(map,i,j+1,hgt+1,res,set_9);
        }
        if (i>0 && (map[i-1][j]==(hgt+1))) {
            rec_score_trailhead(map,i-1,j,hgt+1,res,set_9);
        }
        if (j>0 && (map[i][j-1]==(hgt+1))) {
            rec_score_trailhead(map,i,j-1,hgt+1,res,set_9);
        }
    }
}

int scores_trailheads(vector<vector<int>>& map, vector<pair<int,int>>& vct_0) {
    int res=0;
    set<pair<int,int>> set_9;
    for (pair<int,int> p:vct_0) {
        set_9.clear();
        // cout <<"0_"<< p.first<<", "<<p.second<<": "<<res<<endl;
        rec_score_trailhead(map, p.first, p.second, 0, res,set_9);
    }
    return res;
}

int chr_to_int(char& c) {
    int i = c - '0';
    return i;
}

int main() { 
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }
    string line; 
    vector<vector<int>> map;
    int map_ij;

    vector<pair<int,int>> vct_0;
    int i=0;
    int j=0;

    while (getline(file, line)) {
        vector<int> map_line;
        for (long unsigned int k=0; k<line.length();k++) {
            map_ij = chr_to_int(line[k]);
            map_line.push_back(map_ij);
            if (map_ij==0) {
                vct_0.push_back(make_pair(i,j));
            }
            j++;
        }
        i++;
        j=0;
        map.push_back(map_line);
    }

    cout << "map:"<<endl;
    print_map(map);

    // print_vect_pair(vct_0);

    int res=scores_trailheads(map, vct_0);
    
    cout << "result: "<<res<<endl;
    // printf("%20.Lf\n",res);
    return 0;
}