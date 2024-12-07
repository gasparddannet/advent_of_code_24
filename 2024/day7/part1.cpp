#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

void print_vectl(vector<long  double>& v) {
    for (long double i : v) {
        cout << i << " ";
    }
    cout<<endl;
}

void print_vect(vector<vector<long double>>& v) {
    for (vector<long double> vl : v) {
        print_vectl(vl);
    }
}

list<long double> rec_all_res(vector<long double> vl, long double tmp, list<long double> res) {
    if (vl.empty()) {
        res.push_back(tmp);
        return res;
    }
    else {
        long double tmp_p = tmp + vl[0];
        long double tmp_m = tmp * vl[0];
        vl.erase(vl.begin());
        list<long double> res1 = rec_all_res(vl, tmp_p, res);
        res1.merge(rec_all_res(vl, tmp_m, res));
        return res1;
    }
}

list<long double> all_res(vector<long double> vl) {
    long double tmp=vl[0];
    vl.erase(vl.begin());
    list<long double> res;
    return rec_all_res(vl, tmp, res);
}

int main() { 
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }
    string line, fst, lst; 
    vector<vector<long double>> vect;
    size_t pos;
    string delimiter=": ";

    while (getline(file, line)) {
        vector<long double> vect_l;

        pos = line.find(delimiter);
        fst = line.substr(0, pos);
        // cout << "fst: " << fst << endl;
        vect_l.push_back(stold(fst));
        line.erase(0, pos+delimiter.length());

        stringstream ss(line);

        while (getline(ss, lst, ' ')) {
            // cout << "lst: " << lst << endl;
            vect_l.push_back(stold(lst));
        }
        vect.push_back(vect_l);
    }

    // print_vect(vect);

    long double res=0;
    long double res_l;
    for (vector<long double> vect_l : vect) {
        // print_vectl(vect_l);
        res_l = vect_l[0];
        vect_l.erase(vect_l.begin());
        list<long double> list_res = all_res(vect_l);

        for (long double i:list_res) {
            // cout << i << ", ";
            if (i==res_l) {
                res+= res_l;
                break;
            }
        }
        // cout << endl;
    }

    
    cout << "result: " << res << endl;
    printf("%20.Lf\n",res);
    return 0;
}