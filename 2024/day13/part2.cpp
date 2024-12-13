#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <utility>
#include <climits>

long gap = 10000000000000;

using namespace std;

tuple<long,long,long> bezout(long a, long b) {
    long r,r1,u,v,u1,v1;
    r=a; r1=b; u=1; v=0; u1=0; v1=1;
    long q, rs, us, vs;
    while (r1 != 0) {
        q = r/r1;
        rs=r; us=u; vs=v;
        r=r1;u=u1;v=v1;
        r1=rs-q*r; u1=us-q*u1; v1=vs-q*v1;
    }
    return make_tuple(r,u,v);
}

pair<int,int> get_xy_btn(string& btn) {
    int x,y;
    string delimiter = ", ";
    size_t pos = btn.find(delimiter);
    x = stoi(btn.substr(2,pos-2));
    y = stoi(btn.substr(pos+delimiter.length()+2));
    return make_pair(x,y);
}

pair<long,long> get_xy_prize(string& btn) {
    long x,y;
    string delimiter = ", ";
    size_t pos = btn.find(delimiter);
    x = stol(btn.substr(2,pos-2));
    y = stol(btn.substr(pos+delimiter.length()+2));
    return make_pair(x+gap,y+gap);
}

long get_nb_tokens(tuple<pair<int,int>, pair<int,int>,pair<long,long>> mch) {
    pair<int,int> xyA = get<0>(mch);
    pair<int,int> xyB = get<1>(mch);
    pair<long,long> xyP = get<2>(mch);
    int aX = xyA.first;
    int aY = xyA.second;
    int bX = xyB.first;
    int bY = xyB.second;
    long pX = xyP.first;
    long pY = xyP.second;
    long nbA,nbB;
    long nb_tokens = 0;
    nbB = (pY-((aY*pX)/aX))/(bY - (aY*bX)/aX);
    nbA = (pX - bX*nbB)/aX;
    long nbA2 = (pY - bY*nbB)/aY;
    cout << (pY - bY*nbB) <<endl;
    cout << aY <<endl;
    cout << (pY - bY*nbB)/aY << endl;
    long double t = (pY - bY*nbB)/aY;
    printf("%20.Lf\n",t);



    cout << "nbB: "<< nbB <<endl;
    cout << "nbA: "<<nbA<<endl;
    cout << "nbA2: "<<nbA2<<endl;
    cout << nbA*aX + nbB*bX << "="<<pX<<endl;
    cout << nbA*aY + nbB*bY << "="<<pY<<endl;

    // printf("nbB: %20.f\n",nbB);
    // printf("nbA: %20.f\n",nbA);
    // printf("nbA2: %20.f\n",nbA2);
    // printf("%20.f=%20.ld\n",nbA*aX + nbB*bX, pX);
    // printf("%20.f=%20.ld\n",nbA*aY + nbB*bY, pY);


    bool cond1,cond2;
    cond1 = nbA*aX + nbB*bX == pX;
    cond2 = nbA*aY + nbB*bY == pY;
    // cout << cond1<<endl;
    if (nbA>=0 && nbB>=0 && cond1 && cond2 ) {
        nb_tokens = 3*nbA + nbB;
        // cout << "vrai"<<endl;
    }
    return nb_tokens;
}

int main() {
    ifstream file("example");

    if (!file.is_open()) {
    cout << "Could not open file!\n";
    return 1;
    }
    string lineA, lineB, lineP, lineN, s;
    string btnA, btnB, prize;
    pair<int,int> xyA, xyB;
    pair<long,long> xyP;
    tuple<pair<int,int>, pair<int,int>,pair<long,long>> mch;
    list<tuple<pair<int,int>, pair<int,int>,pair<long,long>>> lst_mch;

    while (getline(file, lineA) && 
            getline(file, lineB) && 
            getline(file, lineP)) {
        btnA = lineA.substr(10);
        xyA = get_xy_btn(btnA);
        // cout << xyA.first <<", "<<xyA.second<<endl;
        btnB = lineB.substr(10);
        xyB = get_xy_btn(btnB);
        prize = lineP.substr(7);
        xyP = get_xy_prize(prize);
        mch = make_tuple(xyA,xyB,xyP);
        // cout<<get<2>(mch).first<<endl;
        lst_mch.push_back(mch);
        
        getline(file, lineN);
    }

    file.close();
    auto start = chrono::high_resolution_clock::now();

    long res = 0;
    for (tuple<pair<int,int>, pair<int,int>,pair<long,long>> mch:lst_mch) {
        res += get_nb_tokens(mch);
    }


    auto stop = chrono::high_resolution_clock::now();

    cout << "result: " <<res<<endl;
    // printf("%20.llu\n",res);
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time: " << duration.count() << "ms" << endl;

    return 0;
}