#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <chrono>
// #include <unordered_map>
#include <map>

using namespace std;

void print_stones(vector<string>& stones) {
    for (string& s:stones) {
        cout << s<<" ";
    }
    cout << endl;
}

void remove_forwarding_zeros(string& s) {
    if (s[0]=='0') {
        s.erase(0,s.find_first_not_of('0'));
    }
    if (s.empty()) {
        s="0";
    }
}

list<string> blink(string& s) {
    long long int num;
    string new_stone1, new_stone2;
    list<string> lst_new_stone;

    if (s == "0") {
        lst_new_stone.push_back("1");
        return lst_new_stone;
    }
    else if (s.length() % 2 ==0) {
        new_stone1 = s.substr(0,s.length()/2);
        remove_forwarding_zeros(new_stone1);
        lst_new_stone.push_back(new_stone1);
        new_stone2 = s.substr(s.length()/2);
        remove_forwarding_zeros(new_stone2);
        lst_new_stone.push_back(new_stone2);
        return lst_new_stone;
    }
    else {
        num = stoll(s);
        new_stone1 = to_string(2024*num);
        lst_new_stone.push_back(new_stone1);
        return lst_new_stone;
    }
}

int main(int argc, char** argv) { 
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

    int nb_blinking = stoi(argv[1]);
    auto start = chrono::high_resolution_clock::now();
    map<string, long long int> hash_map;
    
    for (string& stone:stones) {
        if (hash_map.find(stone) != hash_map.end()) {
            hash_map[stone]++;
        }
        else {
            hash_map.insert({stone, 1});
        }
    }

    list<string> lst_new_stone;
    for (int i=0;i<nb_blinking;i++) {
        map<string, long long int> tmp_hash_map;

        for (auto p: hash_map) {
            string stone = p.first;
            lst_new_stone = blink(stone);
            for (string& s:lst_new_stone) {
                if (tmp_hash_map.find(s) != tmp_hash_map.end()) {
                    tmp_hash_map[s]+= p.second;
                }
                else {
                    tmp_hash_map.insert({s, p.second});
                }
            }
        }
        hash_map = tmp_hash_map;
    }

    auto stop = chrono::high_resolution_clock::now();

    long long res=0;
    for (auto p:hash_map) {
        res+=p.second;
    }
    cout << "result: " <<res<<endl;
    printf("%20.llu\n",res);
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time: "<<duration.count() <<"ms"<< endl;

    return 0;
}