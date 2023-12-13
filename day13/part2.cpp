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

bool smudgeCheck(vector<char> top, vector<char> bot) {
    for (int i = 0; i < top.size(); ++i) {
        vector<char> temp = top;
        if (temp[i] = '#')
            temp[i] = '.';
        else
            temp[i] = '#';
        if (temp == bot)
            return true;
    }
    return false;
}

bool smudge(vector<vector<char>>& grid) {
    bool ok = false;
    for (int i = 0; i < grid.size()/2; ++i) {
        if (grid[i] != grid[grid.size()-i-1]) {
            if (!ok) {
                bool check = smudgeCheck(grid[i], grid[grid.size()-i-1]);
                if (check)
                    ok = true;
                else
                    return false;
            }
            else {
                return false;
            }
        }
    }
    return ok;
}

long long solve(vector<vector<char>>& grid) {
    int check;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < grid.size(); ++j) {
            if ((j+1)*2 < grid.size()) {
                vector<vector<char>> temp(grid.begin(), grid.begin()+(j+1)*2);
                check = smudge(temp);
            }
            else {
                vector<vector<char>> temp(grid.end()-((grid.size()-1)-j)*2, grid.end());
                check = smudge(temp);
            }
            if (check) {
                if (i == 1) {
                    return (long long) (j+1);
                }
                else {
                    return (long long) ((j+1)*100);
                }
            }
        }
        grid = transposeMatrix(grid);
    }
    return 0;
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