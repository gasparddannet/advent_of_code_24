#include <chrono>
#include <climits>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <list>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// typedef tuple<string,string,string> setInterConnec;

class Graph {
    map<string, vector<string>> adjList;

    public:
        void add_edge(string u, string v) {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        set<set<string>> find_inter_connect() {
            set<set<string>> set_tuples;
            for (auto& a:adjList) {
                if (a.first[0]=='t') {
                    int n=a.second.size();
                    for (int i=0;i<n-1;i++) {
                        string u=a.second[i];
                        for (int j=i+1;j<n;j++) {
                            set<string> set2;
                            string v=a.second[j];
                            if(find(adjList[u].begin(), adjList[u].end(), v) != adjList[u].end()) {
                                set2.insert(a.first);
                                set2.insert(u);
                                set2.insert(v);
                                set_tuples.insert(set2);
                            }
                        }
                    }
                }
            }
            return set_tuples;
        }
        
        void print() {
            cout << "Adjacency list: "<<endl;
            for (auto& a:adjList) {
                cout << a.first <<"->";
                for (string& s:a.second) {
                    cout << s<<" ";
                }
                cout << endl;
            }
        }
};

int main() {
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }

    Graph g;

    string line;
    string u,v;
    while (getline(file,line)) {
        u=line.substr(0,2);
        v=line.substr(3);
        g.add_edge(u, v);
    }
    file.close();


    auto tstart = chrono::high_resolution_clock::now();

    g.print();
    set<set<string>> set_tuples=g.find_inter_connect();

    for (set<string> set2:set_tuples) {
        for (string s:set2) {
            cout << s <<", ";
        }
        cout<<endl;
        // cout << get<0>(t) <<", "<<get<1>(t)<<", "<<get<2>(t)<<endl;
    }
    int res = set_tuples.size();

    auto tstop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(tstop - tstart);
    cout << "result: "<<res<<endl;
    cout << "time: " << duration.count() << " milliseconds" << endl;

    return 0;
}