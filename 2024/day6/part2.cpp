#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <utility>
// #include <variant>
#include <tuple>

using namespace std;

tuple<vector<vector<char>>, int, bool> rec_path(vector<vector<char>>&, int, int, int,vector<pair<int,int>>&);

void print_map(vector<vector<char>>& map) {
    for (vector<char> line : map) {
        for (char c : line) {
            cout << c;
        }
        cout << endl;
    }
}

tuple<vector<vector<char>>, int, bool> move_guard(vector<vector<char>>& map, int i, int j, 
                            int ni, int nj,char g, char ng, int res, vector<pair<int,int>>& vect_block) {
    if (map[ni][nj] == '.') {
        map[i][j] = 'X';
        map[ni][nj] = g;
        return rec_path(map, ni, nj, res+1,vect_block);
    }
    else if (map[ni][nj] == 'X') {
        map[i][j] = 'X';
        map[ni][nj] = g;
        return rec_path(map, ni, nj, res,vect_block);
    }
    else if (map[ni][nj] == '#') {
        pair<int, int> p = make_pair(i,j);
        vect_block.push_back(p);
        int c = count(vect_block.begin(), vect_block.end(), p);
        if (c >= 3) {
            // cout << "count blocks, " << i << ", "<<j<<": "<<c<<endl;
            return make_tuple(map, res, false);
        }
        map[i][j] = ng;
        return rec_path(map, i, j, res,vect_block);
    }
    string err = "Invalid next case: ";
    throw invalid_argument(err + map[ni][nj]);
}  

tuple<vector<vector<char>>, int, bool> rec_path(vector<vector<char>>& map, int i, int j, int res,
                                                 vector<pair<int,int>>& vect_block) {
    int n = map.size();
    int m = map[0].size();
    char guard = map[i][j];
    // cout << "guard: " << guard << ", i: " << i<<", j: "<<j<<endl;
    // cout << "i: " << i << endl;
    // cout << "j: " << j << endl;

    if (i==0 && guard == '^') {
        map[i][j] = 'X';
        return make_tuple(map, res+1, true);
    }
    if (i==n-1 && guard == 'v') {
        map[i][j] = 'X';
        return make_tuple(map, res+1, true);
    }
    if (j==0 && guard == '<') {
        map[i][j] = 'X';
        return make_tuple(map, res+1, true);
    }
    if (j==m-1 && guard == '>') {
        map[i][j] = 'X';
        return make_tuple(map, res+1, true);
    }

    switch (guard) {
        case '^': return move_guard(map,i,j,i-1,j,'^','>',res,vect_block);
        case '>': return move_guard(map,i,j,i,j+1,'>','v',res,vect_block);
        case 'v': return move_guard(map,i,j,i+1,j,'v','<',res,vect_block);
        case '<': return move_guard(map,i,j,i,j-1,'<','^',res,vect_block);
        default: throw invalid_argument("missing guard !?");
    }
}

tuple<vector<vector<char>>, int, bool> path(vector<vector<char>> map, int i, int j) {
    vector<pair<int,int>> vect_block;
    tuple<vector<vector<char>>, int, bool> res= rec_path(map, i, j, 0, vect_block);
    // print_map(map);
    // cout << endl;
    return res;
}

void check_nb_guards(bool& b) {
    if (b) {
        throw invalid_argument("there is two guards !");
    }
}

bool check_guard(char l, char g, bool& find) {
    if (l == g) {
        check_nb_guards(find);
        find = true;
        return true;
    }
    return false;
}

int main() { 
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }

    string line; 
    vector<vector<char>> map;
    vector<char> l;

    bool find = false;
    bool& rfind = find;
    int posi, posj;
    int i=0;
    while (getline(file, line)) {
        for (int j=0; j<line.length();j++) {
            l.push_back(line[j]);
            if (check_guard(line[j], '^', rfind)) {
                posi = i; posj = j;
            }
            if (check_guard(line[j], '<', rfind)) {
                posi = i; posj = j;
            }
            if (check_guard(line[j], '>', rfind)) {
                posi = i; posj = j;
            }
            if (check_guard(line[j], 'v', rfind)) {
                posi = i; posj = j;
            }
        }
        i+=1;
        map.push_back(l);
        l.clear();
    }

    if (!rfind) {
        throw invalid_argument("there is no guards ! Lezgongue");
    }

    print_map(map);
    // cout << "find: " << rfind << endl;
    // cout << "posi: " << posi << endl;
    // cout << "posj: " << posj << endl;
    // cout << "dir: " << dir << endl;

    int nb_loop = 0;
    int n = map.size();
    int m = map[0].size();
    for (int i=0;i<n; i++) {
        for (int j=0;j<m;j++) {
            if (map[i][j] == '.') {
                map[i][j] = '#';
                // print_map(map);
                // cout << endl;
                tuple<vector<vector<char>>, int, bool> res = path(map, posi, posj);
                if (!(get<2>(res))) {
                    nb_loop+=1;
                }
                map[i][j] = '.';
            }
        }
    }

    cout << "result: " << nb_loop << endl;
    return 0;
}