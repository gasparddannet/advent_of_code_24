#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <sstream>

using namespace std;

int N=103;
int M=101;

void move_1s(vector<tuple<int,int,int,int>>& vect_rbt) {
    for (tuple<int,int,int,int>& t:vect_rbt) {
        int newx =(get<0>(t)+get<2>(t))%M;
        int newy =(get<1>(t)+get<3>(t))%N;
        if (newx<0) {newx+=M;}
        if (newy<0) {newy+=N;}
        get<0>(t) = newx;
        get<1>(t) = newy;
    }
}

int main() {
    ifstream file("input.txt");

    if (!file.is_open()) {
    cout << "Could not open file!\n";
    return 1;
    }
    string line, s;
    string sx,sy,svx,svy;
    vector<tuple<int,int,int,int>> vect_rbt;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss,s,' ');
        s.erase(0,2);
        stringstream ss2(s);
        getline(ss2, sx, ',');
        getline(ss2, sy, ',');
        getline(ss,s,' ');
        s.erase(0,2);
        stringstream ss3(s);
        getline(ss3, svx, ',');
        getline(ss3, svy, ',');
        vect_rbt.push_back((make_tuple(stoi(sx),stoi(sy),stoi(svx),stoi(svy))));
    }
    file.close();

    auto start = chrono::high_resolution_clock::now();

    // for (tuple<int,int,int,int> t:vect_rbt) {
    //     cout << get<0>(t)<<", "<<get<1>(t)<<", "<<get<2>(t)<<", "<<get<3>(t)<<endl;
    // }
    // cout<<endl;

    int nb_sec=100;
    for (int i=0;i<nb_sec;i++) {
        move_1s(vect_rbt);
    }

    // for (tuple<int,int,int,int> t:vect_rbt) {
    //     cout << get<0>(t)<<", "<<get<1>(t)<<", "<<get<2>(t)<<", "<<get<3>(t)<<endl;
    // }

    long res1=0;
    long res2=0;
    long res3=0;
    long res4=0;
    int x,y;

    for (tuple<int,int,int,int>& rbt:vect_rbt) {
        x=get<0>(rbt); 
        y=get<1>(rbt);
        // cout << x<<", "<<y<<endl;
        if (x<M/2 && y<N/2) {
            res1++;
        }
        else if (x<M/2 && y>N/2) {
            res2++;
        }        
        else if (x>M/2 && y>N/2) {
            res3++;
        }        
        else if (x>M/2 && y<N/2) {
            res4++;
        }

    }
    cout <<"res1: "<<res1<<endl;
    cout <<"res2: "<<res2<<endl;
    cout <<"res3: "<<res3<<endl;
    cout <<"res4: "<<res4<<endl;
    long res = res1*res2*res3*res4;

    auto stop = chrono::high_resolution_clock::now();

    cout << "result: " <<res<<endl;
    // printf("%20.llu\n",res);
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time: " << duration.count() << "ms" << endl;


    // cout << (1-2)%N<<endl;
    // cout << 11/2 << ", "<<7/2 <<endl;
    return 0;
}