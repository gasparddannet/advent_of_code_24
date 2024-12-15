#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

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

void print_mvt(vector<char>& lst_mvt) {
    for (char& c:lst_mvt) {
        cout << c;
    }
    cout << endl;
}

pair<int,int> move_boxes(vector<vector<char>>& map, int i, int j, int acci, int accj) {
    int istart=i;
    int jstart=j;
    while (map[i+acci][j+accj]=='O') {
        i+=acci;
        j+=accj;
    }
    if (map[i+acci][j+accj]=='.') {
        map[istart][jstart]='.';
        map[istart+acci][jstart+accj]='@';
        map[i+acci][j+accj]='O';
        // cout << istart<<", "<<jstart<<endl;
        // cout << istart+acci<<", "<<jstart+accj<<endl;
        return make_pair(istart+acci, jstart+accj);
    }
    else {
        return make_pair(istart,jstart);
    }
}

pair<int,int> move(vector<vector<char>>& map, int i, int j, int acci, int accj) {
    // cout << map[i+acci][j+accj]<<endl;
    if (map[i+acci][j+accj]=='#') {
        return make_pair(i,j);
    }
    else if (map[i+acci][j+accj]=='O') {
        return move_boxes(map, i, j, acci, accj);
    }
    else if (map[i+acci][j+accj]=='.') {
        map[i][j]='.';
        map[i+acci][j+accj]='@';
        return make_pair(i+acci, j+accj);
    }
    else {
        string err = "invalid block: ";
        err+= to_string(map[i+acci][j+accj]);
        throw invalid_argument(err);
    }
}

void moves_robot(vector<vector<char>>& map, vector<char>& lst_mvt, pair<int,int> rbt) {
    int i,j;
    while (!lst_mvt.empty()) {
        i=rbt.first; j=rbt.second;
        char mvt = lst_mvt.front();
        // cout << "mvt: "<<mvt<<endl;
        switch (mvt) {
            case '^': rbt=move(map, i, j, -1, 0);break;
            case '>': rbt=move(map, i, j, 0, +1);break;
            case 'v': rbt=move(map, i, j, +1, 0);break;
            case '<': rbt=move(map, i, j, 0, -1);break;
            default: throw invalid_argument("invalid mouvement");
        }
        // print_map(map);
        lst_mvt.erase(lst_mvt.begin());
    }
}

long sum_gps(vector<vector<char>>& map) {
    long res=0;
    for (unsigned long i=0; i<map.size();i++) {
        for (unsigned long j=0;j<map[0].size();j++) {
            if (map[i][j]=='O') {
                res+=100*i+j;
            }
        }
    }
    return res;
}

int main() {
    ifstream file("input.txt");

    if (!file.is_open()) {
    cout << "Could not open file!\n";
    return 1;
    }
    string line;;

    vector<vector<char>> map;
    vector<char> lst_mvt;;
    bool b_map=true;
    int posi, posj;
    int i=0;

    while (getline(file, line)) {
        if (line.empty()) {
            b_map=false;
        }
        if (b_map) {
            vector<char> line_map;
            for (unsigned long j=0; j<line.length();j++) {
                line_map.push_back(line[j]);
                if (line[j] == '@') {
                    posi = i;
                    posj = j;
                }
            }
            map.push_back(line_map);
        }
        else {
            for (unsigned long j=0; j<line.length();j++) {
                if (line[j] != '\n') {
                    lst_mvt.push_back(line[j]);
                }
            }
        }
        i++;
        
    }
    file.close();

    auto start = chrono::high_resolution_clock::now();
    // print_map(map);
    // print_mvt(lst_mvt);
    // cout << posi << ", " <<posj<<endl;

    moves_robot(map, lst_mvt, make_pair(posi, posj));
    long res = sum_gps(map);

    auto stop = chrono::high_resolution_clock::now();

    cout << "result: " <<res<<endl;
    // printf("%20.llu\n",res);
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time: " << duration.count() << "ms" << endl;

    return 0;
}