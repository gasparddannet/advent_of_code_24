#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>
#include <set>

using namespace std;

void print_vect_ant(vector<tuple<char,int,int>>& vect_ant) {
    for (tuple<char,int,int> t:vect_ant) {
        cout << get<0>(t) << ", " <<get<1>(t)<<", "<<get<2>(t)<<endl;
    }
}

void print_antinode(set<pair<int,int>>& set_antinode) {
    for (pair<int,int> p:set_antinode) {
        cout << p.first<<", "<<p.second<<endl;
    }
}

vector<tuple<char,int,int>> get_ant_char(vector<tuple<char,int,int>>& vect_ant, set<char>& ant_checked) {
    vector<tuple<char,int,int>> ant_not_checked;

    for (tuple<char,int,int> t: vect_ant) {
        char ant = get<0>(t);
        if (!ant_checked.count(ant)) {
            for (tuple<char,int,int> t:vect_ant) {
                char c = get<0>(t);
                if (c==ant) {
                    ant_not_checked.push_back(t);
                }
            }
            ant_checked.insert(ant);
            break;
        }
    }
    return ant_not_checked;
}

set<pair<int,int>> place_antinode(vector<tuple<char,int,int>> ant_not_checked, int& n, int& m, set<pair<int,int>>& set_antinode) {
    int i1,j1,i2,j2,pos1i,pos1j,pos2i,pos2j,idiff,jdiff;
    for (long unsigned int i=0; i<ant_not_checked.size()-1;i++) {
        for (long unsigned int j=i+1; j<ant_not_checked.size(); j++) {
            tuple<char,int,int> ant1 = ant_not_checked[i];
            tuple<char,int,int> ant2 = ant_not_checked[j];
            i1 = get<1>(ant1); j1 = get<2>(ant1);
            i2 = get<1>(ant2); j2 = get<2>(ant2);
            set_antinode.insert(make_pair(i1,j1));
            set_antinode.insert(make_pair(i2,j2));

            idiff = i1-i2; jdiff = j1-j2;
            pos1i = i1+idiff; pos1j = j1+jdiff;
            while (0<=pos1i && pos1i<n && 0<=pos1j && pos1j <m) {
                set_antinode.insert(make_pair(pos1i,pos1j));
                pos1i += idiff; pos1j += jdiff;

            }
            pos2i = i1-2*idiff; pos2j = j1-2*jdiff;
            while (0<=pos2i && pos2i<n && 0<=pos2j && pos2j <m) {
                set_antinode.insert(make_pair(pos2i,pos2j));
                pos2i -= idiff; pos2j -= jdiff;
            }
        }
    }
    return set_antinode;
}

int main() { 
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }
    string line; 
    char c;
    vector<tuple<char,int,int>> vec_ant;
    int i=0;
    int j=0;
    vector<vector<char>> mat;
    while (getline(file, line)) {
        vector<char> mat_ln;
        for (long unsigned int k=0; k<line.length();k++) {
            c = line[k];
            mat_ln.push_back(c);
            if (c != '.') {
                vec_ant.push_back(make_tuple(c,i,j));
            }
            j++;
        }
        mat.push_back(mat_ln);
        j=0;
        i++;
    }

    set<char> ant_checked;
    vector<tuple<char,int,int>> ant_not_checked;

    int n = mat.size();
    int m = mat[0].size();
    set<pair<int,int>> set_antinode;

    ant_not_checked = get_ant_char(vec_ant, ant_checked);
    while (!(ant_not_checked.empty())) {
        place_antinode(ant_not_checked,n,m,set_antinode);
        ant_not_checked = get_ant_char(vec_ant, ant_checked);
    }

    int nb_anti_node = set_antinode.size();
    // cout<<"antinodes: "<<endl;
    // print_antinode(set_antinode); 
    cout << "result: "<<nb_anti_node << endl;

    return 0;
}