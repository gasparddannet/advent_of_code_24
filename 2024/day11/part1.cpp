#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;

void print_stones(vector<string>& stones) {
    for (string& s:stones) {
        cout << s<<" ";
    }
    cout << endl;
}

string ld_to_string(long double& ld) {
    string str = to_string(ld);
    str.erase(str.find_last_not_of('0') + 1, string::npos);
    str.erase(str.find_last_not_of('.') + 1, string::npos);
    return str;
}

void blink(vector<string>& stones) {
    long double num;
    string s;
    long double tmp1,tmp2;
    for (long unsigned int i=0;i<stones.size();) {
        s = stones[i];
        if (s == "0") {
            stones[i]="1";
            i++;
        }
        else if (s.length() % 2 ==0) {
            tmp1 = stold(s.substr(0,s.length()/2));
            stones[i] = ld_to_string(tmp1);
            tmp2 = stold(s.substr(s.length()/2));
            stones.insert(stones.begin()+i+1,ld_to_string(tmp2));
            i+=2;
        }
        else {
            num=stold(s);
            tmp1 = 2024*num;
            stones[i] = ld_to_string(tmp1);
            i++;
        }
    }
}

int main() { 
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }
    string line, s; 
    vector<string> stones;

    getline(file, line);

    stringstream ss(line);
    while (getline(ss, s, ' ')) {
        stones.push_back(s);
    }

    print_stones(stones);

    int nb_blinking = 25;
    auto start = chrono::high_resolution_clock::now();
    for (int i=0;i<nb_blinking;i++) {
        blink(stones);
        // print_stones(stones);
    }
    int res = stones.size();
    auto stop = chrono::high_resolution_clock::now();

    cout << "result: " <<res<<endl;
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    cout << "time: "<<duration.count() <<"s"<< endl;

    return 0;
}