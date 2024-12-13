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

// long euclide(long a, long b) {
//     long tmp;
//     while (b!=0) {
//         tmp=b;
//         b = a % b;
//         a = tmp;
//     }
//     return a;
// }

// tuple<long,long,long> rec_euclide_etendu(long a, long b) {
//     if (b==0) {
//         return make_tuple(a,1,0);
//     }
//     tuple<long,long,long> t = rec_euclide_etendu(b, a%b);
//     return make_tuple(get<0>(t), get<2>(t), get<1>(t)-(a%b)*get<2>(t));
// }

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

pair<bool,long long> get_tokens(pair<int,int> xAB, long pX, pair<int,int> yAB, long pY) {
    long a = xAB.first;
    long b = xAB.second;
    bool res=false;
    tuple<long,long,long> tuple_x =bezout(a,b);
    // cout << "aX: "<<a<<", bX: "<<b<<", pX:"<<pX<<endl;
    // cout << "aY: "<<yAB.first<<", bY: "<<yAB.second<<", pY:"<<pY<<endl;
    long pgcd = get<0>(tuple_x);
    long long nb_tokens = LONG_MAX;
    cout << nb_tokens<<endl;
    if (pX % pgcd == 0) {
        long mult = pX /pgcd;

        long coefA, coefB;
        int kA = b/pgcd;
        int kB = a/pgcd;
        long long tmp;
        coefA = get<1>(tuple_x) * mult;
        coefB = get<2>(tuple_x) * mult;
        // cout << p << "="<<coefA*a+coefB*b<<endl;
        // cout << "coefA: "<<coefA<<endl;
        // cout << "coefB: "<<coefB<<endl;

        if (coefA > 0 && coefB > 0) {
            cout << "cas1" <<endl;

            long nbMax = coefA / kA ;
            long nbMin = -coefB / kB ;
            for (long i=nbMin; i<=nbMax;i++) {
                // cout <<"i: "<<i<<endl;
                long cA = (coefA+i*kA);
                long cB = (coefB-i*kB);
                if (cA >=0 && cB>=0) {
                    tmp = cA*3+cB;
                    if (tmp<nb_tokens) {
                        nb_tokens=tmp;
                        if (!res) {
                            res=true;
                        }
                        // cout << "cA: "<<cA<<", cB: "<<cB<<endl;
                        // cout << "nb_tokens: "<<nb_tokens<<endl;
                    }
                }
            }
        }
        else if (coefA < 0 && coefB > 0) {
            cout << 2<<endl;
            // cout << "kA: "<<kA<<", kB: "<<kB<<endl;
            long nbMin = -coefA/kA -1;
            long nbMax = coefB / kB + 1;
            // cout << "nbMin: "<<nbMin<<endl;
            // cout << "nbMax: "<<nbMax<<endl;
            // long coefAmin = (coefA+nbMin*kA);
            // long coefAmax = (coefA+(nbMax)*kA);
            // long coefBmin = (coefB-nbMin*kB);
            // long coefBmax = (coefB-(nbMax)*kB);
            // cout << "Amin: "<<coefAmin <<endl;
            // cout << "Amax: "<<coefAmax <<endl;
            // cout << "Bmin: "<<coefBmin <<endl;
            // cout << "Bmax: "<<coefBmax <<endl;
            // cout << "Px: " <<pX <<", Py: "<<pY<<endl; 
            // cout << coefAmin*a + coefBmin*b << endl;
            // cout << coefAmax*a + coefBmax*b << endl;
            // cout << coefAmin*yAB.first + coefBmin*yAB.second << endl;
            // cout << coefAmax*yAB.first + coefBmax*yAB.second << endl;

            // (coefA + i*ka ) * yab = py
            // coefB - (i*kb) *yab = p
            long i1 = ((pY/yAB.first)-coefA)/kA;
            long i2 = ((pY/yAB.second)-coefB)/(-kB);
            // cout << "i1: " << i1<<endl;
            // cout << "i2: " << i2<<endl;
            // cout << (coefA+i1*kA)*yAB.first<<endl;
            // cout << (coefB-i2*kB)*yAB.second<<endl;
            // long iv = 2688338496719;
            // cout << (coefA+iv*kA)*yAB.first + (coefB-iv*kB)*yAB.second<<endl;
            // coefA-i*ka * yad = py
            // cout << (coefA-pY)/(kA*yAB.first) <<endl;
            // cout << (coefA-pY)/(kA*yAB.second) <<endl;

            long iMin = max(nbMin, min(i1,i2));
            long iMax = min(nbMax, max(i1,i2));
            // cout << "iMin: " <<iMin<<endl;
            // cout << "iMax: " <<iMax<<endl;
            for (long i=iMin; i<=iMax;i++) {
                long cA = (coefA+(i*kA));
                long cB = (coefB-(i*kB));
                // cout <<"i: "<<i<<endl;
                // cout << "cA: " <<cA<<endl;
                // cout << "cB: " <<cB<<endl;
                // cout << cA*a+cB*b<<endl;
                // if (cA*a+cB*b) {

                // cout << cA*yAB.first+cB*yAB.second <<endl;
                // cout << "pY: " <<pY<<endl;
                if (cA >=0 && cB>=0 && (cA*yAB.first+cB*yAB.second==pY)) {
                    tmp = cA*3+cB;
                    cout << "vrai"<<endl;
                    if (tmp<nb_tokens) {
                        nb_tokens=tmp;
                        if (!res) {
                            res=true;
                        }
                        // cout << "i: "<<i<<endl;
                        // cout << "cA: "<<cA<<", cB: "<<cB<<endl;
                        // cout << "nb_tokens: "<<nb_tokens<<endl;
                    }
                }
            }
        }
        else if (coefA > 0 && coefB < 0) {
            cout << 3<<endl;
            long nbMax = coefA / kA + 1;
            long nbMin = -coefB / kB - 1;
            // cout << "nbMin: "<<nbMin<<endl;
            // cout << "nbMax: "<<nbMax<<endl;
            // long coefAmin = (coefA-nbMin*kA);
            // long coefAmax = (coefA-(nbMax)*kA);
            // long coefBmin = (coefB+nbMin*kB);
            // long coefBmax = (coefB+(nbMax)*kB);
            // cout << "Amin: "<<coefAmin <<endl;
            // cout << "Amax: "<<coefAmax <<endl;
            // cout << "Bmin: "<<coefBmin <<endl;
            // cout << "Bmax: "<<coefBmax <<endl;
            // cout << "Px: " <<pX <<", Py: "<<pY<<endl; 
            // cout << coefAmin*a + coefBmin*b << endl;
            // cout << coefAmax*a + coefBmax*b << endl;
            // cout << coefAmin*yAB.first + coefBmin*yAB.second << endl;
            // cout << coefAmax*yAB.first + coefBmax*yAB.second << endl;

            // (coefA-i*ka) * yad = py
            // cout << (coefA-pY)/(kA*yAB.first) <<endl;
            // cout << (coefA-pY)/(kA*yAB.second) <<endl;

            long i1 = ((pY/yAB.first)-coefA)/(-kA);
            long i2 = ((pY/yAB.second)-coefB)/(kB);
            // cout << "i1: " << i1<<endl;
            // cout << "i2: " << i2<<endl;
            // long iv = 2688338496719;
            // cout << (coefA+iv*kA)*yAB.first + (coefB-iv*kB)*yAB.second<<endl;
            // coefA-i*ka * yad = py
            // cout << (coefA-pY)/(kA*yAB.first) <<endl;
            // cout << (coefA-pY)/(kA*yAB.second) <<endl;

            long iMin = max(nbMin, min(i1,i2));
            long iMax = min(nbMax, max(i1,i2));
            // cout << "iMin: " <<iMin<<endl;
            // cout << "iMax: " <<iMax<<endl;

            // if ()
            for (long i=iMin; i<=iMax;i++) {
                // cout <<"i: "<<i<<endl;
                long cA = (coefA-i*kA);
                long cB = (coefB+i*kB);
                // cout << cA*yAB.first+cB*yAB.second <<endl;
                // cout << "pY: " <<pY<<endl;
                if (cA >=0 && cB>=0 && (cA*yAB.first+cB*yAB.second==pY)) {
                    tmp = cA*3+cB;
                    cout << "vrai"<<endl;
                    if (tmp<nb_tokens) {
                        nb_tokens=tmp;
                        if (!res) {
                            res=true;
                        }
                        // cout << "cA: "<<cA<<", cB: "<<cB<<endl;
                        // cout << "nb_tokens: "<<nb_tokens<<endl;
                    }
                }
            }
        }
        else {
            res = false;
            cout << "false"<<endl;
        }
        return make_pair(res, nb_tokens);
    }
    else {
        cout << "p mod pgcd != 0" <<endl;
        return make_pair(res, nb_tokens);
    }
    
}

long get_nb_tokens(tuple<pair<int,int>, pair<int,int>,pair<long,long>> mch) {
    // long nb_tokens;
    // long tmp;
    // bool b=false;
    pair<int,int> xyA = get<0>(mch);
    pair<int,int> xyB = get<1>(mch);
    pair<long,long> xyP = get<2>(mch);

    // cout << xyP.first / xyA.first << endl;
    // cout << xyP.first / xyB.first << endl;

    // long nbMaxA = min(xyP.first/xyA.first, xyP.second/xyA.second);
    // long nbMaxB = min(xyP.first/xyB.first, xyP.second/xyB.second);
    // cout << "nbMaxA: "<<nbMaxA<<", nbMaxB: "<<nbMaxB<<endl;
    
    // // long nbMinA = min(xyP.first )
    // // cout << "euclide: "<<euclide(17, 84) << endl;
    // // cout << "euclide: "<<euclide(86 , 37) << endl;
    // int a1=26;
    // int b1=66;
    // int a2=67;
    // int b2=21;
    // int ka, kb;
    // cout << "euclide: "<<euclide(a1, b1) << endl;
    // cout << "euclide: "<<euclide(a2, b2) << endl;
    // tuple<long,long,long> t =bezout(a1,b1);
    // cout <<"bezout: "<<get<0>(t)<<", "<<get<1>(t)<<", "<<get<2>(t)<<endl;
    // // t =bezout(a2,b2);
    // // cout <<"bezout: "<<get<0>(t)<<", "<<get<1>(t)<<", "<<get<2>(t)<<endl;

    // cout << "c % PGCD(a,b): " <<10000000007870%(euclide(a1,b1)) <<endl;
    // cout << "c % PGCD(a,b): " <<10000000006450%(euclide(a2,b2)) <<endl;

    // long c1 = 10000000007870;
    // long mult = c1 / (euclide(a1, b1));

    // long coef1, coef2;
    // coef1 = get<1>(t) * mult;
    // coef2 = get<2>(t) * mult;

    // cout << "coef1: "<<coef1 << ", coef2: "<<coef2<<endl;
    // cout << c1 << "=" << coef1*a1+coef2*b1 <<endl; 


    // ka = b1/get<0>(t);
    // kb = a1/get<0>(t);
    // cout << "ka: "<<ka<<", kb: "<<kb<<endl;

    // long nbMin = -coef1 / ka ;
    // cout << "nbMin: "<<nbMin<<endl;

    // long nbMax = coef2 / kb ;
    // cout << "nbMax: "<<nbMax<<endl;

    // cout << (coef1 + nbMin*ka) << endl;
    // cout << (coef1 + nbMin*ka)*a1 + (coef2-nbMin*kb)*b1 <<endl;
    // cout << (coef1 - nbMin*ka)*a1 + (coef2+nbMin*kb)*b1 <<endl;


    // X

    // Y
    // cout << "X"<<endl;
    pair<bool, long long> p = get_tokens(make_pair(xyA.first,xyB.first), xyP.first,
                                    make_pair(xyA.second, xyB.second), xyP.second);

    // if (pX.first) { 
    //     pair<bool, long> pY = get_tokens(make_pair(xyA.second,xyB.second), xyP.second);
    // }
    // if (b) {
    //     // cout << "nb_tokens: "<<nb_tokens<<endl;
    //     return nb_tokens;
    // }
    // else {
    //     // cout << "nb_tokens: "<<0<<endl;
    //     return 0;
    // }

    if (p.first) {
        return p.second;
    }

    else {
        return 0;
    }

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