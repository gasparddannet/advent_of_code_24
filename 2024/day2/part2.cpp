#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void print_vect(vector<int>& v) {
    for (int i : v) {
        cout << i << " ";
    }
}

int is_safe(vector<int>& vect) {
    bool safe = true;
    bool icr = vect[0] < vect[1];
    for(vector<int>::iterator it = vect.begin()+1; it != vect.end();it++) {
        if ((*(it-1) > *it) && icr) {
            safe = false;
            break;
        }
        else if ((*(it) > *(it-1)) && !icr) {
            safe = false;
            break;
        }
        else if ((abs(*it - *(it-1))<1) || (abs(*it - *(it-1))>3)) {
            safe = false;
            break;
        }
    }
    return safe;
}

int main() { 
    ifstream file("example.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }
    string str, s; 
    int res = 0;
    while (getline(file, str)) {
        vector<int> vect;

        stringstream ss(str);

        while (getline(ss, s, ' ')) {
            vect.push_back(stoi(s));
        }
        print_vect(vect);

        bool safe = is_safe(vect);
        if (safe) {
            printf("\tsafe\n");
            res += 1;
        }
        else {
            bool b;
            for (long unsigned int i=0; i<vect.size();i++) {
                vector<int> vect_copy(vect);
                vect_copy.erase(vect_copy.begin()+i);
                b = is_safe(vect_copy);
                if (b) {
                    printf("\tsafe: ");
                    print_vect(vect_copy);
                    cout<<endl;
                    res += 1;
                    break;
                }
            }
            if (!b) printf("\tnot safe\n");
        }
    }
    
    cout << "result: " << res << endl;
    return 0;
}