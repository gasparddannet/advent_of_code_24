#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <cassert>

using namespace std;

int main() { 
    ifstream file("input");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }
    string line; 
    int res = 0;
    bool cond = true;

    while (getline(file, line)) {
        cout << line << endl;

        regex rx_mul("mul\\([0-9]*,[0-9]*\\)|don't|do");
        regex rx_nb("[0-9]+");
        
        smatch match_mul; 
        vector<int> vect_nb;

        if (regex_search(line, match_mul, rx_mul))
        {
            auto begin = sregex_iterator(line.begin(), line.end(), rx_mul);
            auto end = sregex_iterator();

            for (auto it = begin; it != end; ++it) {
                string match = it->str();
                cout << match << '\n';

                if (!match.compare("don't")) {
                    cout << "if don't" << endl;
                    cond = false;
                }
                else if (!match.compare("do")) {
                    cout << "if do" << endl;
                    cond = true;
                }
                else {
                    if (cond) {
                        cout << "entre bcl" << endl;
                        auto begin = sregex_iterator(match.begin(), match.end(), rx_nb);
                        auto end = sregex_iterator();
                        for (auto it2 = begin; it2 != end; ++it2) {
                            string nb = it2->str();
                            cout << nb << '\n';
                            vect_nb.push_back(stoi(nb));
                        }
                        assert(vect_nb.size()==2);
                        res += vect_nb[0] * vect_nb[1];
                        vect_nb.clear();
                    }
                }


            }
        }
        cout << "result: " << res << endl;
    }
    return 0;
}
