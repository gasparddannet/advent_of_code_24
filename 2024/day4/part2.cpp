#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

int minus_one(int i) {
    return i-1;
}

void print_mat(vector<vector<char>> matrix) {
    for (int i=0; i<matrix.size();i++) {
        for (int j=0; j<matrix[i].size();j++) {
            cout << matrix[i][j] << " | " ;
        }
        cout << endl;
    }
}

bool check_mas(vector<vector<char>> matrix, int i, int j, char ltr) {
    if (matrix[i][j] == ltr) {
        return true;
    }
    return false;
}

bool check_diag1(vector<vector<char>> m, int i, int j) {
    if (check_mas(m,i-1,j-1,'M') && check_mas(m,i+1,j+1,'S'))
        return true;
    else if (check_mas(m,i-1,j-1,'S') && check_mas(m,i+1,j+1,'M'))
        return true;
    return false;
}

bool check_diag2(vector<vector<char>> m, int i, int j) {
    if (check_mas(m,i-1,j+1,'M') && check_mas(m,i+1,j-1,'S')) 
        return true;
    else if (check_mas(m,i-1,j+1,'S') && check_mas(m,i+1,j-1,'M'))
        return true;
    return false;
}

bool check_diag(vector<vector<char>> m, int i, int j, int (*func1) (int), int (*func2) (int)) {
    if (check_mas(m,i-1,func1(j),'M') && check_mas(m,i+1,func2(j),'S'))
        return true;
    else if (check_mas(m,i-1,func1(j),'S') && check_mas(m,i+1,func2(j),'M'))
        return true;
    return false;
}

void find(vector<vector<char>> m, int& res, int i, int j) {
    int (*plus_one)(int) = [](int i) -> int {return i+1;};

    if (check_diag(m,i,j,&minus_one, [](int i) -> int {return i+1;}) 
        && check_diag(m,i,j,plus_one,&minus_one)) {
        res += 1;
    }
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
    for (int i=1; i<n-1; i++) {
        for (int j=1; j<m-1;j++) {
            if (matrix[i][j] == 'A') {
                find(matrix, res, i, j);
            }
        }
    }

    cout << "result: " << res << endl;
    
    return 0;
}
