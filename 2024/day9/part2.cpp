#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void print_disk(vector<string>& disk) {
    for (string& s:disk) {
        cout << s << " ";
    }
    cout << endl;
}

void add_string(int nb, string& s, vector<string>& disk) {
    for (int i=0;i<nb;i++) {
        disk.push_back(s);
    }
}

int chr_to_int(char& c) {
    int i = c - '0';
    return i;
}

void move_block(int lb, int &rb, vector<string>& disk) {
    int size_block = rb-lb+1;
    int j;
    for (int i=0;i<lb-1;) {
        j=i+1;
        if (disk[i] == ".") {
            while (disk[j] ==".") {
                j++;
            }
            if (j-i >= size_block) {
                for (int k=0;k<size_block;k++) {
                    disk[i+k] = disk[lb+k];
                    disk[lb+k] = ".";
                }
                break;
            }
        }
        i=j;
    }
}

int main() { 
    ifstream file("example3");

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
    for (long unsigned int k=0; k<line.length();k++) {
        nb = chr_to_int(line[k]);
        if (free_space) {
            add_string(nb,point,disk);
            free_space = false;
        }
        else {
            s = to_string(id);
            add_string(nb,s,disk);
            free_space = true;
            id++;
        }
    }

    cout << "disk"<<endl;
    print_disk(disk);

    string id_str;
    string tmp;
    const int size = disk.size();
    int j;
    for (int i=size-1;i>0;) {
        id_str = disk[i];
        j=i-1;
        if (id_str!=".") {
            tmp = disk[j];
            while (tmp==id_str && j>0) {
                j--;
                tmp = disk[j];
            }
            move_block(j+1, i, disk);
        }
        i=j;
    }
    cout << "move disk:"<<endl;
    print_disk(disk);
    int n;
    long double res=0;
    for (int i=0;i<size;i++) {
        if (disk[i]!=".") {
            n = stoi(disk[i]);
            res += n*i;
        }
    }
    
    cout << "result: "<<res<<endl;
    printf("%20.Lf\n",res);
    return 0;
}