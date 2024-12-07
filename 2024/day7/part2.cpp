#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

void print_vectl(vector<string>& v) {
    for (string i : v) {
        cout << i << " ";
    }
    cout<<endl;
}

void print_vect(vector<vector<string>>& v) {
    for (vector<string> vl : v) {
        print_vectl(vl);
    }
}

// string ld_to_string(long double ld) {
//     stringstream ss;
//     ss << ld; 
//     return ss.str(); 
// }

list<string> rec_all_res(vector<string> vl, string tmp, list<string> res) {
    if (vl.size() <=1) {
        res.push_back(tmp);
        return res;
    }
    else if (vl.size()>=2) {
        long double p = stold(tmp) + stold(vl[1]);
        long double m = stold(tmp) * stold(vl[1]);

        string tmp_p = to_string(p);
        string tmp_m = to_string(m);
        string tmp_rm_0;
        tmp_rm_0 = tmp.substr(0, tmp.find('.'));
        string tmp_c = tmp_rm_0+vl[1];
        vl.erase(vl.begin());
        list<string> res1 = rec_all_res(vl, tmp_p, res);
        res1.merge(rec_all_res(vl, tmp_m, res));
        res1.merge(rec_all_res(vl, tmp_c, res));
        return res1;
    }
    else {
        long double p = stold(tmp) + stold(vl[1]);
        long double m = stold(tmp) * stold(vl[1]);
        string tmp_p = to_string(p);
        string tmp_m = to_string(m);
        vl.erase(vl.begin());
        list<string> res1 = rec_all_res(vl, tmp_p, res);
        res1.merge(rec_all_res(vl, tmp_m, res));
        return res1;
    }
}

list<string> all_res(vector<string> vl) {
    string tmp=vl[0];
    list<string> res;
    return rec_all_res(vl, tmp, res);
}

int main() { 
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }
    string line, fst, lst; 
    vector<vector<string>> vect;
    size_t pos;
    string delimiter=": ";

    while (getline(file, line)) {
        vector<string> vect_l;

        pos = line.find(delimiter);
        fst = line.substr(0, pos);
        // cout << "fst: " << fst << endl;
        vect_l.push_back(fst);
        line.erase(0, pos+delimiter.length());

        stringstream ss(line);

        while (getline(ss, lst, ' ')) {
            // cout << "lst: " << lst << endl;
            vect_l.push_back(lst);
        }
        vect.push_back(vect_l);
    }

    // print_vect(vect);

    long double res=0;
    long double res_l;
    for (vector<string> vect_l : vect) {
        // print_vectl(vect_l);
        res_l = stold(vect_l[0]);
        vect_l.erase(vect_l.begin());
        list<string> list_res = all_res(vect_l);

        for (string i:list_res) {
            long double ldi = stold(i);
            if (ldi==res_l) {
                res+=res_l;
                break;
            }
        }
    }

    cout << "result: " << res << endl;
    printf("%20.Lf\n",res);
    return 0;
}