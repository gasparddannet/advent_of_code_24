#include <chrono>
#include <climits>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <queue>

using namespace std;

typedef tuple<string,string,int,string> wires;

int main() {
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }

    string line;
    string gate1, gate2, gate3,op;
    int val_op;
    int val;
    bool cond=true;
    string s;
    map<string,int> map_gate;
    queue<wires> q_wires;

    while (getline(file,line)) {
        if (line.empty()) {
            cond = false;
            continue;
        }
        if (cond) {
            gate1=line.substr(0,3);
            val=stoi(line.substr(5));
            map_gate[gate1] = val;
            // cout << gate1<<":"<<val<<endl;
        }
        else {
            stringstream ss(line);
            getline(ss, gate1, ' ');
            getline(ss, op, ' ');
            getline(ss, gate2, ' ');
            getline(ss, s, ' ');
            getline(ss, gate3, ' ');
            if (op=="XOR") {
                val_op=0;
            }
            else if (op=="OR") {
                val_op=1;
            }
            else {
                val_op=2;
            }
            q_wires.push(make_tuple(gate1,gate2,val_op,gate3));
            // cout << gate1<<" "<<op<<" "<<gate2<<" -> "<<gate3<<endl;
        }

    }
    file.close();

    auto tstart = chrono::high_resolution_clock::now();

    wires wire;
    int val_gate1, val_gate2;
    while (!q_wires.empty()) {
        wire = q_wires.front();
        q_wires.pop();
        gate1=get<0>(wire);
        gate2=get<1>(wire);
        val_op=get<2>(wire);
        gate3=get<3>(wire);
        if (map_gate.count(gate1) && map_gate.count(gate2)) {
            val_gate1=map_gate[gate1];
            val_gate2=map_gate[gate2];
            switch (val_op) {
                case 0: map_gate[gate3]=val_gate1^val_gate2 ;break;
                case 1:  map_gate[gate3]=val_gate1|val_gate2 ;break;
                case 2: map_gate[gate3]=val_gate1&val_gate2 ;break;
                default :throw invalid_argument("invalid operator");
            }
        }
        else {
            q_wires.push(wire);
        }
    }

    int i=0;
    long res=0;
    for (auto& gate:map_gate) {
        if (gate.first[0]=='z') {
            if (gate.second) {
                res += pow(2,i);
            }
            i++;
        }
        // cout << gate.first << ": "<<gate.second<<endl;
    }

    auto tstop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(tstop - tstart);
    cout << "result: "<<res<<endl;
    cout << "time: " << duration.count() << " milliseconds" << endl;

    return 0;
}