#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
                        int& res) {
    int n=map.size(); 
    int m=map[0].size();

    if (hgt==9) {
        res++;
    }
    else {
        if (i+1<n && (map[i+1][j] == (hgt+1))) {
            rec_score_trailhead(map,i+1,j,hgt+1,res);
        }
        if (j+1<m && (map[i][j+1] == (hgt+1))) {
            rec_score_trailhead(map,i,j+1,hgt+1,res);
        }
        if (i>0 && (map[i-1][j]==(hgt+1))) {
            rec_score_trailhead(map,i-1,j,hgt+1,res);
        }
        if (j>0 && (map[i][j-1]==(hgt+1))) {
            rec_score_trailhead(map,i,j-1,hgt+1,res);
        }
    }
}

int scores_trailheads(vector<vector<int>>& map, vector<pair<int,int>>& vct_0) {
    int res=0;
    for (pair<int,int> p:vct_0) {
        rec_score_trailhead(map, p.first, p.second, 0, res);
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
    return 0;
}