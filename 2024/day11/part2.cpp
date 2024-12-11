#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>
#include <set>
#include <charconv>
#include <chrono>
#include <unordered_map>
#include <map>
#include <functional>

using namespace std;


struct hash_pair { 
  
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        size_t hash1 = hash<T1>{}(p.first);
        size_t hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    } 
}; 


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

bool check_key(unordered_map<pair<string,int>, int,hash_pair> m, pair<string,int> key)
{
    if (m.find(key) != m.end())
        return true;
    return false;
}

long unsigned int rec_blink_stone(string s, int nb_blinking, unordered_map<pair<string,int>, int,hash_pair>& hash_map, int& nb_found) {
    long unsigned int num;
    string new_stone1, new_stone2;
    long unsigned int val;
    if (nb_blinking==0) {
        return 1;
    }
    if (check_key(hash_map, make_pair(s,nb_blinking))) {
        // cout << "found"<<endl;
        nb_found++;
        return hash_map[make_pair(s,nb_blinking)];
    }   
    if (s == "0") {
        // new_stone1 = "1";
        val = rec_blink_stone("1", nb_blinking-1,hash_map, nb_found);
    }
    else if (s.length() % 2 ==0) {
        new_stone1 = s.substr(0,s.length()/2);
        remove_forwarding_zeros(new_stone1);
        // res++;
        new_stone2 = s.substr(s.length()/2);
        remove_forwarding_zeros(new_stone2);
        val = rec_blink_stone(new_stone1, nb_blinking-1,hash_map, nb_found)+
                rec_blink_stone(new_stone2, nb_blinking-1,hash_map, nb_found);

        // rec_blink_stone(new_stone2, res, nb_blinking-1);
    }
    else {
        num = stoul(s);
        new_stone1 = to_string(2024*num);
        val = rec_blink_stone(new_stone1, nb_blinking-1,hash_map, nb_found);
    }
    hash_map.insert({make_pair(s,nb_blinking),val});
    return val;
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
    long unsigned int res=0;
    int nb_found=0;
    auto start = chrono::high_resolution_clock::now();
    unordered_map<pair<string,int>, int, hash_pair> hash_map;
    // map<pair<string,int>, int> map;

    for (string& stone:stones) {
        res+=rec_blink_stone(stone, nb_blinking, hash_map, nb_found);
    }
    auto stop = chrono::high_resolution_clock::now();

    cout << "result: " <<res<<endl;
    printf("%20.lu\n",res);
    cout << "nb_found: " <<nb_found<<endl;
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time: "<<duration.count() <<"ms"<< endl;
    cout << "time: "<<duration.count()/1000 <<"s"<< endl;

    return 0;
}