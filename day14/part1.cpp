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


void printMatrix(const vector<vector<char>>& grid) {
    const int n = grid.size();
    const int m = grid[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

long long getLoad(vector<vector<char>>& grid) {
    const int n = grid.size();
    const int m = grid[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'O') {
                // cout << "test" << endl;
                int k = j;
                while (k >= 0 && grid[i][k-1] == '.') {
                    k--;
                }
                // cout << i << " " << j << " " << k << endl;
                grid[i][j] = '.';
                grid[i][k] = 'O';
            }
        }
    }

    vector<vector<char>> transposed = transposeMatrix(grid);
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        long long cnt = 0;
        for (int j = 0; j < m; ++j) {
            if (transposed[i][j] == 'O') {
                cnt++;
            }
        }
        cout << "i, cnt" << i << " " << cnt << endl;
        ans += (cnt * (n-i));
    }

    printMatrix(transposed);

    return ans;
}

int main() {
    string input;
    vector<vector<char>> inputs;
    while (getline(cin, input)) {
        vector<char> row;
        for (char c : input) {
            row.push_back(c);
        }
        inputs.push_back(row);
    }

    vector<vector<char>> grid = transposeMatrix(inputs);
    long long ans = getLoad(grid);
    cout << ans << endl;
    return 0;
}