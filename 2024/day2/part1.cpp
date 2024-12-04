#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


int print_vect(vector<int> v) {
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

int main() { 
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }
    string str, s; 
    int res = 0;
    while (getline(file, str)) {
        vector<int> vect;

        // cout << "str:" << str << endl;
        stringstream ss(str);

        while (getline(ss, s, ' ')) {
            // cout << "s:" << s << endl;
            vect.push_back(stoi(s));
        }
        print_vect(vect);
        int safe = 1;

        if (vect[0] < vect[1]) {
            for(vector<int>::iterator it = vect.begin(); it != vect.end() - 1; it++)
                {
                    if (*it > *(it+1)) {
                        cout << *it << " and " << *(it+1) << " is decreasing but " << *vect.begin() 
                        << " and " << *(vect.begin() + 1) << " is increasing" << endl;
                        safe = 0;
                        break;
                    }
                    else if (*(it+1) - *it < 1) {
                        cout << *it << " and " << *(it+1) << " is neither an increase or a decrease" << endl;
                        safe = 0;
                        break;
                    }
                    else if (*(it+1) - *it > 3) {
                        cout << *it << " and " << *(it+1) << " is an increase of " << *(it+1) - *it << endl;
                        safe = 0;
                        break;
                    }
                }
        }
        else if (vect[0] > vect[1]) {
            for(vector<int>::iterator it = vect.begin(); it != vect.end()-1; it++)
                {
                    if (*it < *(it+1)) {
                        cout << *it << " and " << *(it+1) << " is increasing but " << *vect.begin() 
                        << " and " << *(vect.begin() + 1) << " is decreasing" << endl;
                        safe = 0;
                        break;
                    }
                    else if (*it - *(it+1) < 1) {
                        cout << *it << " and " << *(it+1) << " is neither an increase or a decrease" << endl;
                        safe = 0;
                        break;
                    }
                    else if (*it - *(it+1) > 3) {
                        cout << *it << " and " << *(it+1) << " is a decrease of " << *it - *(it+1) << endl;
                        safe = 0;
                        break;
                    }
                }
        }
        else {
            cout << vect[0] << " and " << vect[1] << " is neither an increase or a decrease !" << endl;
            safe = 0;
        }
        if (safe == 1) {
            res += 1;
        }
    }
    
    cout << "result: " << res << endl;
    return 0;
}