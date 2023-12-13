#include<iostream>
#include<stdlib.h>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<sstream>
#include<limits.h>

using namespace std;

template <typename T>
vector<vector<T>> transposeMatrix(const vector<vector<T>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return {};

    size_t numRows = matrix.size();
    size_t numCols = matrix[0].size();
    vector<vector<T>> transposed(numCols, vector<T>(numRows));

    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

long long calculate(vector<vector<char>>& grid, int i, int j) {
    long long v;
    int s = i;
    // cout << "i, j " << i << " " << j << endl;
    while (i >= 0 && j < grid.size()) {
        if (grid[i] != grid[j]) {
            return -1;
        }
        i--;
        j++;
    }
    // cout << "New i, j " << i << " " << j << endl;
    // cout << "s " << s << endl;
    return s+1;
}

long long solve(vector<vector<char>>& grid) {
    long long temp = 0;
    for (int i = 0; i < grid.size()-1; i++) {
        if (grid[i] == grid[i+1]) {
            long long temp2 = calculate(grid, i, i+1);
            temp += (temp2 == -1 ? 0 : (temp2)*100);
        }
    }

    vector<vector<char>> grid2 = transposeMatrix(grid);
    for (int i = 0; i < grid2.size()-1; i++) {
        if (grid2[i] == grid2[i+1]) {
            long long temp2 = calculate(grid2, i, i+1);
            temp += (temp2 == -1 ? 0 : temp2);
        }
    }
    return temp;
}


int main() {
    string input;
    long long ans = 0;
    vector<vector<char>>grid;
    while (getline(cin, input)) {
        if (input.empty()) {
            ans += solve(grid);
            grid.clear();
        }
        else {
            vector<char> row;
            for (int i = 0; i < input.size(); i++) {
                row.push_back(input[i]);
            }
            grid.push_back(row);
        }
    }
    ans += solve(grid);
    cout << ans << endl;

    return 0;
}