#include <iostream>
#include <fstream>
#include <string>
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

    while (getline(file, line)) {
        cout << line << endl;

        regex rx_mul("mul\\([0-9]*,[0-9]*\\)");
        regex rx_nb("[0-9]+");
        
        smatch match_mul; 
        vector<int> vect_nb;

        if (std::regex_search(line, match_mul, rx_mul))
        {
            auto begin = std::sregex_iterator(line.begin(), line.end(), rx_mul);
            auto end = std::sregex_iterator();

            for (auto it = begin; it != end; ++it) {
                std::string mul = it->str();
                std::cout << mul << '\n';

                auto begin = std::sregex_iterator(mul.begin(), mul.end(), rx_nb);
                auto end = std::sregex_iterator();
                for (auto it2 = begin; it2 != end; ++it2) {
                    std::string nb = it2->str();
                    std::cout << nb << '\n';
                    vect_nb.push_back(stoi(nb));
                }
                assert(vect_nb.size()==2);
                res += vect_nb[0] * vect_nb[1];
                vect_nb.clear();
            }
        }
        cout << "result: " << res << endl;
    }
    return 0;
}
