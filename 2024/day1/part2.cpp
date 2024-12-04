#include <iostream>
#include <fstream>
#include <string>
// #include <list>
#include <vector>
#include <cassert>
#include <utility>
#include <algorithm>

using namespace std;

int nb_occ(vector<int> v, int val) {
    int res = 0;
    auto it = find(v.begin(), v.end(), val);

    while (it != v.end()) {
        // cout << distance(v2.begin(), it) << " ";
        res += 1;
        it = find(it + 1, v.end(), val);
    }
    return res;
}

int main() { 
    ifstream file("input.txt");
    string str; 
    string del = "   ";
    vector<int> v1, v2;
    while (getline(file, str)) {
        auto pos = str.find(del);

        v1.push_back(stoi(str.substr(0, pos)));
        str.erase(0, pos + del.length());
        v2.push_back(stoi(str));
        }
    
    assert(v1.size() == v2.size());

    int res = 0;
    for (int i : v1) {
        res += i * nb_occ(v2, i);
    }

    cout << "result: " << res << endl;
    return 0;
}