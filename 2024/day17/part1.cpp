#include <chrono>
#include <climits>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <map>

using namespace std;

int get_register(ifstream& file) {
    string line;
    getline(file, line);
    line.erase(0,12);
    return stol(line);
}

vector<int> get_program(ifstream& file) {
    vector<int> program;
    string line, s;
    getline(file, line);
    getline(file, line);
    cout << line<<endl;
    line.erase(0,9);
    stringstream ss(line);
    while (getline(ss, s, ',')) {
        program.push_back(stoi(s));
    }
    return program;
}

int adv(int A, int co) {
    // cout << "A, pow(2, "<<co<<"): "<<A<<", "<<pow(2,co)<< "="<< A/int(pow(2,co))<<endl;
    return A/(int(pow(2,co)));
}

int bxl(int B, int lo) {
    return B^lo;
}

int bst(int co) {
    return co%8;
}

int bxc(int B, int C) {
    return B^C;
}

int out(int co) {
    return co%8;
}

vector<int> execute_program(vector<int> program, int A, int B, int C) {
    vector<int> output;
    // long out;
    map<int,int*> map;
    for (int j=0;j<=3;j++) {
        map[j]=&j;
    }
    map[4]=&A;
    map[5]=&B;
    map[6]=&C;

    for (unsigned int i=0;i<program.size();) {
        // cout << program[i]<<endl;
        if (program[i]==0) {
            int a= program[i+1];
            A = adv(A, *map[a]);
            i+=2;
        }
        else if (program[i]==1) {
            B = bxl(B,program[i+1]);
            i+=2;
        }        
        else if (program[i]==2) {
            B = bst(*map[program[i+1]]);
            i+=2;
        }        
        else if (program[i]==3) {
            if (A!=0) {
                i=program[i+1];
            }
            else {
                i+=2;
            }
        }        
        else if (program[i]==4) {
            B = bxc(B,C);
            i+=2;
        }        
        else if (program[i]==5) {
            int a = program[i+1];
            output.push_back(out(*map[a]));
            i+=2;
        }        
        else if (program[i]==6) {
            B = adv(A,*map[program[i+1]]);
            i+=2;
        }        
        else if (program[i]==7) {
            C = adv(A,*map[program[i+1]]);
            i+=2;
        }        
    }
    return output;
}

int main() {
    ifstream file("example2");

    if (!file.is_open()) {
    cout << "Could not open file!\n";
    return 1;
    }
    string line;

    int A, B, C;
    vector<int> program;

    A = get_register(file);
    B = get_register(file);
    C = get_register(file);
    program = get_program(file);

    file.close();

    // cout << A<< endl;
    // cout << B<< endl;
    // cout << C<< endl;
    // for (int i:program) {
    //     cout <<i<<",";
    // }
    // cout<<endl;

    auto start = chrono::high_resolution_clock::now();

    vector<int> output = execute_program(program, A, B, C);

    auto stop = chrono::high_resolution_clock::now();

    for (unsigned long i=0;i<output.size();i++) {
        if (i==output.size()-1) {
            cout << output[i] <<endl;
        }
        else {
            cout <<output[i] <<",";
        }
    }

    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time: " << duration.count() << "ms" << endl;

    return 0;
}