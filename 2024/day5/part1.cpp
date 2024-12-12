#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <utility>

using namespace std;


void print_rules(vector<pair<int,int>> rules) {
    cout << "rules:" << endl;
    for (pair<int,int> p : rules) {
        cout << p.first << "|" << p.second << endl;
    }
}

void print_updates(vector<vector<int>> updates) {
    cout << "updates:" << endl;
    for (vector<int> update : updates) {
        for (int i : update) {
            cout << i << ",";
        }
        cout << endl;
    }
}

void print_safe(vector<bool> safe) {
    cout << "safe: " << endl;
    for (bool b : safe) {
        cout << b << endl;
    }
}

int main() { 
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }

    string line, s1,s2; 
    vector<pair<int,int>> rules;
    vector<vector<int>> updates;
    bool cond_rules = true;
    while (getline(file, line)) {
        if (line.empty()) {
            cond_rules = false;
            continue;
        }
        if (cond_rules) {
            stringstream ss(line);
            getline(ss, s1, '|');
            getline(ss, s2, '|');
            rules.push_back(make_pair(stoi(s1),stoi(s2)));
        }
        else {
            vector<int> update;
            stringstream ss(line);
            while (getline(ss, s1, ',')) {
                update.push_back(stoi(s1));
            }
            updates.push_back(update);
        }
    }

    // print_rules(rules);
    // print_updates(updates);

    vector<bool> corr_up;
    for (vector<int> update : updates) {
        bool safe = true;
        for (int i=1;i<update.size();i++) {
            if (safe) {
                for (int j=0;j<i;j++) {
                    if (safe) {
                        for (pair<int,int> p : rules) {
                            if (p.first == update[i] && p.second == update[j]) {
                                safe = false;
                                break;
                            }
                        }
                    }
                }
            }
        }
        corr_up.push_back(safe);
    }

    assert(corr_up.size() == updates.size());

    // print_safe(corr_up);

    int res = 0;
    for (int i=0; i<updates.size();i++) {
        if (corr_up[i]) {
            int l = updates[i].size();
            res += updates[i][l/2];
        }
    }

    cout << "result: " << res << endl;

    return 0;
}