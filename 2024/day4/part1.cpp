#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

void print_mat(vector<vector<char>> matrix) {
    for (int i=0; i<matrix.size();i++) {
        for (int j=0; j<matrix[i].size();j++) {
            cout << matrix[i][j] << " | " ;
        }
        cout << endl;
    }
}

void check_word(vector<vector<char>> matrix, int& res, int i1, int j1, int i2, int j2, int i3, int j3) {
    if (matrix[i1][j1] == 'M') {
        if (matrix[i2][j2] == 'A') {
            if (matrix[i3][j3] == 'S') {
                res += 1;
            }
        }
    }
}

void find(vector<vector<char>> matrix, int& res, int i, int j) {
    int n = matrix.size();
    int m = matrix[0].size();

    if (j-3>=0)
        check_word(matrix, res, i, j-1, i, j-2, i, j-3);
    if (i-3>=0 && j-3 >=0)
        check_word(matrix, res, i-1, j-1, i-2, j-2, i-3, j-3);
    if (i-3>=0)
        check_word(matrix, res, i-1, j, i-2, j, i-3, j);
    if (i-3>=0 && j+3<m)
        check_word(matrix, res, i-1, j+1, i-2, j+2, i-3, j+3);
    if (j+3<m)
        check_word(matrix, res, i, j+1, i, j+2, i, j+3);
    if (i+3<n && j+3<m)
        check_word(matrix, res, i+1, j+1, i+2, j+2, i+3, j+3);
    if (i+3<n)
        check_word(matrix, res, i+1, j, i+2, j, i+3, j);
    if (i+3<n && j-3>=0)
        check_word(matrix, res, i+1, j-1, i+2, j-2, i+3, j-3);
}

int main() { 
    ifstream file("input.txt");

    if (!file.is_open()) {
        cout << "Could not open file!\n";
        return 1;
    }

    string line, s; 
    vector<vector<char>> matrix;
    while (getline(file, line)) {
        vector<char> l;
        for (int j=0; j<line.length(); j++) {
            l.push_back(line[j]);
        }
        matrix.push_back(l);
    }
    
    print_mat(matrix);

    int r = 0;
    int& res = r;
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<m;j++) {
            if (matrix[i][j] == 'X') {
                find(matrix, res, i, j);
            }
        }
    }

    cout << "result: " << res << endl;
    
    return 0;
}
