#include <chrono>
#include <climits>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

void print_patterns(vector<string>& patterns) {
    for (string& pat:patterns) {
        cout << pat<<", ";
    }
    cout << endl;
}

void print_designs(vector<string>& designs) {
    for (string& des:designs) {
        cout << des<<endl;
    }
    cout << endl;
}

bool is_design_possible(vector<string>& patterns, string design, int length_patterns) {
    // cout << "degign: "<<design<<endl;
    // myFile << "design: "<<design <<endl;
    if (find(patterns.begin(), patterns.end(), design)!=patterns.end()) {
        cout << "found"<<endl;
        return true;
    }

    int length = design.length();
    int i_init = std::min(length_patterns, length); 
    // cout << "length: "<<design.length()<<endl;
    // cout << "i_init: "<<i_init<<endl;
    for (int i=i_init;i>=1;i--) {
        string sub = design.substr(0,i);
        // myFile << "sub: "<<sub <<endl;
        // cout << "sub: "<<sub<<endl;
        if (find(patterns.begin(), patterns.end(), sub)!=patterns.end()) {
            // cout << "found sub in patterns"<<endl;
            // myFile << "found sub in patterns" <<endl;
            bool found= is_design_possible(patterns, design.substr(i), length_patterns);
            if (found) {
                return true;
            }
        }
        // else {
        //     myFile << "not found sub in patterns"<<endl;
        // }
    }
    // cout << "false"<<endl;
    return false;
}

// bool is_design_possible(vector<string>& patterns, string design, int length_patterns) {
//     cout << "degign: "<<design<<endl;
//     if (find(patterns.begin(), patterns.end(), design)!=patterns.end()) {
//         // cout << "found"<<endl;
//         return true;
//     }
//     bool found=false;
//     queue<string> q;
//     q.push(design);
//     string s;
//     while (!q.empty() && !found) {
//         s = q.front();
//         // cout << "s: "<<s<<endl;
//         q.pop();
//         if (find(patterns.begin(), patterns.end(), s)!=patterns.end()) {
//             found = true;
//         }
//         else {
//             int length = s.length();
//             int i_init = std::min(length_patterns, length); 
//             for (int i=i_init;i>=1;i--) {
//                 // cout << "i: "<<i<<endl;
//                 string sub = s.substr(0,i);
//                 // cout << "sub: "<<sub<<endl;
//                 if (find(patterns.begin(), patterns.end(), sub)!=patterns.end()) {
//                     // cout << "found sub in patterns"<<endl;
//                     // cout << "sub : "<<sub<<"+"<<s.substr(i)<<endl;
//                     q.push(s.substr(i));
//                 }
//             }
//         }
//     }
//     return found;
// }

int check_designs_possible(vector<string>& patterns, vector<string>& designs, int max_length_patterns) {
    int res=0;
    for (string& des: designs) {
        cout << "design: "<<des<<endl;
        // myFile << "check design: "<<des<<endl;
        bool cond = false;
        for (string& pat:patterns) {
            int l = pat.length();
            int ld = des.length();
            if (des.substr(ld-l)==pat) {
                for (string& pat2:patterns) {
                    int l2=pat2.length();
                    if (des.substr(ld-l-l2,l2)==pat2) {
                        cond =true;
                        break;
                    }
                }
            }
        }
        if (cond) {
            if (is_design_possible(patterns, des, max_length_patterns)) {
                res++;
            }
        }

    }
    return res;
}

int main() {
    ifstream file("input.txt");

    if (!file.is_open()) {
    cout << "Could not open file!\n";
    return 1;
    }
    string line, s;
    vector<string> patterns;
    vector<string> designs;
    
    getline(file,line);
    std::size_t found = line.find(", ");
    while (found != string::npos) {
        // cout << line.substr(0,found) <<endl;
        patterns.push_back(line.substr(0,found));
        line = line.erase(0,found+2);
        // cout << "line: "<<line<<endl;
        found = line.find(", ");
    }
    patterns.push_back(line);

    getline(file,line);
    while (getline(file, line)) {
        designs.push_back(line);
    }
    file.close();

    auto start = chrono::high_resolution_clock::now();

    // print_patterns(patterns);

    unsigned int max_length_patterns=0;
    unsigned int min_length_patterns=INT_MAX;
    for (string& s:patterns) {
        if (s.length()> max_length_patterns) {
            max_length_patterns=s.length();
        }
        else if (s.length()<min_length_patterns) {
            min_length_patterns=s.length();
        }
    }
    cout << "max length patterns: "<<max_length_patterns<<endl;
    cout << "min length patterns: "<<min_length_patterns<<endl;

    // print_designs(designs);

    // ofstream myFile("test");
    int res = check_designs_possible(patterns, designs, max_length_patterns);
    // myFile.close();
    // string s2="abc";
    // cout << s2.substr(0,1)<<endl;

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "result: "<<res<<endl;
    cout << "time: " << duration.count() << " microseconds" << endl;

    return 0;
}