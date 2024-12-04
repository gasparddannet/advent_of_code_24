#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <utility>
#include <algorithm>

using namespace std;


/*--------------*/
//----Part 1----//
/*--------------*/

int print_vec(vector<pair<int,int>> v1, vector<pair<int,int>> v2) {
    for (int i = 0 ; i<v1.size(); i++) {
        cout << "(" << v1[i].first << ", " << v1[i].second << ") " << 
        "(" << v2[i].first << ", " << v2[i].second << ")" << endl;
    }
    return 0;
}

int main() 
{ 
    ifstream file("input.txt");
    string str; 
    string del = "   ";
    vector<pair<int, int>> v1, v2;
    while (getline(file, str)) {
        auto pos = str.find(del);

        v1.push_back(make_pair(stoi(str.substr(0, pos)), v1.size()));
        str.erase(0, pos + del.length());
        v2.push_back(make_pair(stoi(str), v2.size()));
        
        }
    
    assert(v1.size() == v2.size());

    // print_vec(v1, v2);

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    // cout << "sort vector\n";
    // print_vec(v1, v2);

    int res = 0;
    for (int i=0; i<v1.size(); i++) {
        res += abs(v1[i].first - v2[i].first);
        // j'avais compris les différences d'indices, 
        // c'est pour ça que j'ai fait des pair, mais ça ne sert à rien
    }
    cout << "result: " << res << endl;
    return 0;
}


/*--------------*/
//----Part 2----//
/*--------------*/
