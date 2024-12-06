#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <cassert>
#include <vector>
#include <utility>

using namespace std;

void print_map(vector<vector<char>> map) {
    for (vector<char> line : map) {
        for (char c : line) {
            cout << c;
        }
        cout << endl;
    }
}

pair<vector<vector<char>>, int> rec_path(vector<vector<char>> map, int i, int j, int res) {
    int n = map.size();
    int m = map[0].size();
    char guard = map[i][j];
    // cout << "guard: " << guard << endl;
    // cout << "i: " << i << endl;
    // cout << "j: " << j << endl;

    if (i==0 && guard == '^') {
        map[i][j] = 'X';
        return make_pair(map, res+1);
    }
    if (i==n-1 && guard == 'v') {
        map[i][j] = 'X';
        return make_pair(map, res+1);
    }
    if (j==0 && guard == '<') {
        map[i][j] = 'X';
        return make_pair(map, res+1);
    }
    if (j==m-1 && guard == '>') {
        map[i][j] = 'X';
        return make_pair(map, res+1);
    }

    if (guard == '^' && map[i-1][j] == '.') {
        map[i][j] = 'X';
        map[i-1][j] = '^';
        return rec_path(map, i-1, j, res+1);
    }
    else if (guard == '^' && map[i-1][j] == 'X') {
        map[i][j] = 'X';
        map[i-1][j] = '^';
        return rec_path(map, i-1, j, res);
    }
    else if (guard == '^' && map[i-1][j] == '#') {
        map[i][j] = '>';
        return rec_path(map, i, j, res);
    }
    else if (guard == '>' && map[i][j+1] == '.') {
        map[i][j] = 'X';
        map[i][j+1] = '>';
        return rec_path(map, i, j+1, res+1);
    }
    else if (guard == '>' && map[i][j+1] == 'X') {
        map[i][j] = 'X';
        map[i][j+1] = '>';
        return rec_path(map, i, j+1, res);
    }
    else if (guard == '>' && map[i][j+1] == '#') {
        map[i][j] = 'v';
        return rec_path(map, i, j, res);
    }
    else if (guard == 'v' && map[i+1][j] == '.') {
        map[i][j] = 'X';
        map[i+1][j] = 'v';
        return rec_path(map, i+1, j, res+1);
    }
    else if (guard == 'v' && map[i+1][j] == 'X') {
        map[i][j] = 'X';
        map[i+1][j] = 'v';
        return rec_path(map, i+1, j, res);
    }
    else if (guard == 'v' && map[i+1][j] == '#') {
        map[i][j] = '<';
        return rec_path(map, i, j, res);
    }
    else if (guard == '<' && map[i][j-1] == '.') {
        map[i][j] = 'X';
        map[i][j-1] = '<';
        return rec_path(map, i, j-1, res+1);
    }
    else if (guard == '<' && map[i][j-1] == 'X') {
        map[i][j] = 'X';
        map[i][j-1] = '<';
        return rec_path(map, i, j-1, res);
    }
    else if (guard == '<' && map[i][j-1] == '#') {
        map[i][j] = '^';
        return rec_path(map, i, j, res);
    }

    throw invalid_argument("missing guard !?");
}

// int cond(vector<vector<char>> map, int i, int j, int res) {

// }

pair<vector<vector<char>>, int> path(vector<vector<char>> map, int i, int j) {
    return rec_path(map, i, j, 0);
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
            // if (line[j] == '^') {
            //     check_nb_guards(find);
            //     find = true;
            //     posi = i;
            //     posj = j;
            //     dir = "up";
            // }
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

    print_map(map);
    cout << "find: " << rfind << endl;
    cout << "posi: " << posi << endl;
    cout << "posj: " << posj << endl;
    // cout << "dir: " << dir << endl;


    pair<vector<vector<char>>, int> res = path(map, posi, posj);
    print_map(res.first);
    cout << "result: " << res.second << endl;
    return 0;
}