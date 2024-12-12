#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <charconv>

using namespace std;

void print_disk(vector<string>& disk) {
    for (string& s:disk) {
        cout << s << " ";
    }
    cout << endl;
}

void add_string(int nb, string& s, vector<string>& disk) {
    for (int i=0;i<nb;i++) {
        // disk_map+=c;
        disk.push_back(s);
    }
}

int chr_to_int(char& c) {
    int i = c - '0';
    return i;
}

char* int_to_chr(int &i) {
    int length = to_string(i).length();
    char* nchar = new char[length];
    to_chars(nchar, nchar+length, i);
    return nchar;
}

void move_block(int &i, vector<string>& disk) {
    string tmp = disk[i];
    if (tmp != ".") {
        for (int j=0;j<i;j++) {
            if (disk[j]==".") {
                disk[i] = ".";
                disk[j] = tmp;
                break;
            }
        }
    }
}

int main() { 
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }
    string line; 
    int id=0;
    int nb;
    bool free_space = false;
    string s;
    string point=".";
    vector<string> disk;

    getline(file, line);
    // cout << "line:\t"<<line<<endl;
    for (long unsigned int k=0; k<line.length();k++) {
        nb = chr_to_int(line[k]);
        // cout << "nb: "<<nb<<": ";
        if (free_space) {
            // cout << "."<<endl;
            add_string(nb,point,disk);
            free_space = false;
        }
        else {
            s = to_string(id);
            // cout <<s<<endl;
            add_string(nb,s,disk);
            free_space = true;
            id++;
        }
    }

    // cout << "disk"<<endl;
    // print_disk(disk);

    const int size = disk.size();
    for (int i=size-1;i>=0;i--) {
        move_block(i, disk);
    }
    // cout << "move disk:";
    // print_disk(disk);

    long double res=0;
    string it = disk[0];
    int i=0;
    int n;
    while (it != ".") {
        n = stoi(it);
        res += n*i;
        i++;
        it = disk[i];
    }
    
    cout << "result: "<<res<<endl;
    printf("%20.Lf\n",res);
    return 0;
}