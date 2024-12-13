#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <tuple>

using namespace std;

pair<int,int> get_xy_btn(string& btn) {
    int x,y;
    string delimiter = ", ";
    size_t pos = btn.find(delimiter);
    x = stoi(btn.substr(2,pos-2));
    y = stoi(btn.substr(pos+delimiter.length()+2));
    return make_pair(x,y);
}

long get_nb_tokens(tuple<pair<int,int>, pair<int,int>,pair<int,int>> mch) {
    long nb_tokens;
    long tmp;
    bool b=false;
    pair<int,int> xyA = get<0>(mch);
    pair<int,int> xyB = get<1>(mch);
    pair<int,int> xyP = get<2>(mch);

    // cout << xyP.first / xyA.first << endl;
    // cout << xyP.first / xyB.first << endl;

    int nbMaxA = min(xyP.first/xyA.first, xyP.second/xyA.second);
    int nbMaxB = min(xyP.first/xyB.first, xyP.second/xyB.second);
    // cout << "nbMaxA: "<<nbMaxA<<", nbMaxB: "<<nbMaxB<<endl;
    
    nb_tokens = nbMaxA*3+nbMaxB;
    for (int i=0;i<=nbMaxA;i++) {
        for (int j=0;j<=nbMaxB;j++) {
            if ((i*xyA.first+j*xyB.first==xyP.first) &&
                (i*xyA.second+j*xyB.second==xyP.second)) {
                tmp = 3*i + j;
                if (tmp<nb_tokens) {
                    nb_tokens=tmp;
                    if (!b) {
                        b=true;
                    }
                }
            }
        }
    }
    if (b) {
        // cout << "nb_tokens: "<<nb_tokens<<endl;
        return nb_tokens;
    }
    else {
        // cout << "nb_tokens: "<<0<<endl;
        return 0;
    }

}

int main() {
    ifstream file("input.txt");

    if (!file.is_open()) {
    cout << "Could not open file!\n";
    return 1;
    }
    string lineA, lineB, lineP, lineN, s;
    string btnA, btnB, prize;
    pair<int,int> xyA, xyB, xyP;
    tuple<pair<int,int>, pair<int,int>,pair<int,int>> mch;
    list<tuple<pair<int,int>, pair<int,int>,pair<int,int>>> lst_mch;

    while (getline(file, lineA) && 
            getline(file, lineB) && 
            getline(file, lineP)) {
        btnA = lineA.substr(10);
        xyA = get_xy_btn(btnA);
        // cout << xyA.first <<", "<<xyA.second<<endl;
        btnB = lineB.substr(10);
        xyB = get_xy_btn(btnB);
        prize = lineP.substr(7);
        xyP = get_xy_btn(prize);
        mch = make_tuple(xyA,xyB,xyP);
        lst_mch.push_back(mch);
        
        getline(file, lineN);
    }

    file.close();
    auto start = chrono::high_resolution_clock::now();

    long res = 0;
    for (tuple<pair<int,int>, pair<int,int>,pair<int,int>> mch:lst_mch) {
        res += get_nb_tokens(mch);
    }


    auto stop = chrono::high_resolution_clock::now();

    cout << "result: " <<res<<endl;
    // printf("%20.llu\n",res);
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time: " << duration.count() << "ms" << endl;

    return 0;
}