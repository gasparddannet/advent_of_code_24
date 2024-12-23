#include <chrono>
#include <climits>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

long mix(long tmp, long l) {
    return tmp ^ l;
}

long prune(long l) {
    return l % 16777216;
}

long generate_scrt_nb(long scrt) {
    long tmp = scrt*64;
    scrt=mix(tmp, scrt);
    scrt=prune(scrt);
    tmp = scrt/32;
    scrt=mix(tmp, scrt);
    scrt=prune(scrt);
    tmp = scrt*2048;
    scrt=mix(tmp, scrt);
    scrt=prune(scrt);
    // cout << "scrt: "<<scrt<<endl;
    return scrt;
}

int main() {
    ifstream file("example2");

    if (!file.is_open()) {
    cout << "Could not open file!\n";
    return 1;
    }
    string line;
    vector<long> vct_init_nb;
    while (getline(file,line)) {
        vct_init_nb.push_back(stol(line));
    }
    file.close();


    auto tstart = chrono::high_resolution_clock::now();

    long res=0;
    for (long &nb:vct_init_nb) {
        // cout << nb<<endl;
        cout << nb%10<<endl;
        int last_digit1, last_digit2,diff;
        for (int i=0;i<2000;i++) {
            last_digit1 = nb % 10;
            nb = generate_scrt_nb(nb);
            last_digit2 = nb % 10;
            cout << last_digit2;
            diff = last_digit2-last_digit1;
            cout << " ("<<diff<<")";
            cout << endl;

        }


        // cout << "nd_final: "<<nb<<endl;
        res += nb;
    }


    auto tstop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(tstop - tstart);
    cout << "result: "<<res<<endl;
    cout << "time: " << duration.count() << " milliseconds" << endl;

    return 0;
}