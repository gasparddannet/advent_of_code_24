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

int cond(vector<int> vect, vector<int>::iterator it, int &tol, int &safe) {
        cout << ". Tolerate by removing " << *it << endl;
        it = vect.erase(it);
        tol -= 1;

        // it (it+1)


    return 0;
    }

int rec(vector<int> vect, int &safe, int &tol) {
    if (vect[0] < vect[1]) {
        for(vector<int>::iterator it = vect.begin()+1; it != vect.end();) {
            if (*(it-1) > *it) {
                cout << *(it-1) << " and " << *it << " is decreasing but " << *vect.begin() 
                << " and " << *(vect.begin() + 1) << " is increasing";
                if (tol == 1) {
                    if (*(it+1) - *(it-1) < 1 || *(it+1) - *(it-1) > 3){ // check it-1 et it+1
                        cout << ". 2Tolerate by removing " << *(it-1) << endl; 
                        it = vect.erase(it-1);
                        tol -= 1;
                    }
                    else {
                        cout << ". 1Tolerate by removing " << *it << endl; 
                        it = vect.erase(it);
                        tol -= 1;
                    }
                }
                else {
                    cout << ". Not tolerate" << endl;
                    safe -= 1;
                    it++;
                    break;
                }
            }
            else if (*it - *(it-1) < 1) {
                cout << *(it-1) << " and " << *it << " is neither an increase or a decrease";
                safe -= 1;
                if (tol == 1) {
                    cout << ". Tolerate by removing " << *it << endl;
                    it = vect.erase(it);
                    tol -= 1;
                }
                else {
                    cout << ". Not tolerate" << endl;
                    safe -= 1;
                    it++;
                    break;
                }
            }
            else if (*it - *(it-1) > 3) {
                cout << *(it-1) << " and " << *it << " is an increase of " << *it - *(it-1); // cas ou c'est au debut
                safe -= 1;
                if (tol == 1) {
                    if (*(it+1) - *(it-1) <1 ||*(it+1) - *(it-1) >3) {
                        cout << ". Tolerate by removing " << *(it-1) << endl;  // if it-1 et it+1
                        it = vect.erase(it-1);
                        tol -= 1;
                    }
                    else {
                        cout << ". 1Tolerate by removing " << *it << endl; 
                        it = vect.erase(it);
                        tol -= 1;
                    }
                }
                else {
                    cout << ". Not tolerate" << endl;
                    safe -= 1;
                    it++;
                    break;
                }
            }
            else {
                it++;
            }
        }
    }
  
    else if (vect[0] > vect[1]) {
        for(vector<int>::iterator it = vect.begin()+1; it != vect.end();) {
            // cout << "it:" << *it << endl;
            if (*(it-1) < *it) {
                cout << *(it-1) << " and " << *it << " is increasing but " << *vect.begin() 
                << " and " << *(vect.begin() + 1) << " is decreasing";
                if (tol == 1) {
                    if (*(it-1) - *(it+1) < 1 || *(it-1) - *(it+1) > 3){ // check it-1 et it+1
                        cout << ". 2Tolerate by removing " << *(it-1) << endl<<std::flush; 
                        // cout << *it << endl<<std::flush; 
                        it = vect.erase(it-1);
                        // cout << *it << endl<<std::flush; 
                        tol -= 1;
                    }
                    else {
                        cout << ". 1Tolerate by removing " << *it << endl; 
                        it = vect.erase(it);
                        tol -= 1;
                    }
                }
                else {
                    cout << ". Not tolerate" << endl;
                    safe -= 1;
                    break;
                }
            }
            else if (*(it-1) - *it < 1) {
                cout << *(it-1) << " and " << *it << " is neither an increase or a decrease";
                if (tol == 1) {
                    cout << ". Tolerate by removing " << *it << endl;
                    it = vect.erase(it);
                    tol -= 1;
                }
                else {
                    cout << ". Not tolerate" << endl;
                    safe -= 1;
                    break;
                }
            }
            else if (*(it-1) - *it > 3) {
                cout << *(it-1) << " and " << *it << " is a decrease of " << *(it-1) - *it;
                if (tol == 1) {
                    if (*(it-1) - *(it+1) < 1 || *(it-1) - *(it+1) > 3){ // check it-1 et it+1
                        cout << ". 2Tolerate by removing " << *(it-1) << endl; 
                        it = vect.erase(it-1);
                        tol -= 1;
                    }
                    else {
                        cout << ". 1Tolerate by removing " << *it << endl; 
                        it = vect.erase(it);
                        tol -= 1;
                    }
                }
                else {
                    cout << ". Not tolerate" << endl;
                    // cout << 11 <<endl;
                    safe -= 1;
                    it++;
                    break;
                }
            }
            else {
                it++;
            }
        }
    }
    else if (vect[0] == vect[1]) {
        if (tol ==1) {
            cout << *vect.begin() << " and " << *(vect.begin()+1) << " is neither an increase or a decrease. Tolerate by removing " << *vect.begin() << endl;
            vect.erase(vect.begin());
            tol -= 1;
            rec(vect, safe, tol);
        }
        else {
            safe -= 1;
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

        int safe = 1;
        int tol = 1;
        int &rsafe = safe;
        int &rtol = tol;
        safe = rec(vect, rsafe, rtol);
        if (rsafe >= 1) {
            res += 1;
        }
    }
    
    cout << "result: " << res << endl;
    return 0;
}