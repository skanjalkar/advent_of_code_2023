#include<iostream>
#include<stdlib.h>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<sstream>
#include<limits.h>
#include<map>
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

// hash function for vector<vector<char>> so that it can be used in map
struct hash_func {
    size_t operator()(const vector<vector<char>>& vv) const {
        hash<char> hasher;
        size_t seed = vv.size();
        for (const auto& v : vv) {
            for (char i : v) {
                seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }
        return seed;
    }
};

struct Cycle {
    long long index;
    long long load;
    vector<vector<char>> grid;
    Cycle(long long i, long long l, vector<vector<char>> g) : index(i), load(l), grid(g) {}
};

void printMatrix(const vector<vector<char>>& grid) {
    const int n = grid.size();
    const int m = grid[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

long long getLoad(vector<vector<char>>& grid, bool flip = false) {
    const int n = grid.size();
    const int m = grid[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'O') {
                int k = j;
                while (k >= 0 && grid[i][k-1] == '.') {
                    k--;
                }
                grid[i][j] = '.';
                grid[i][k] = 'O';
            }
        }
    }
    if (flip) {
        grid = transposeMatrix(grid);
    }

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        long long cnt = 0;
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'O') {
                cnt++;
            }
        }
        ans += (long long)((long long) cnt *  ((long long)n- (long long)i));
    }
    return ans;
}

long long getLoadf(vector<vector<char>>& grid, bool flip = false) {
    const int n = grid.size();
    const int m = grid[0].size();
    for (int i = n-1; i >= 0; --i) {
        for (int j = m-1; j >= 0; --j) {
            if (grid[i][j] == 'O') {
                int k = j;
                while (k < m && grid[i][k+1] == '.') {
                    k++;
                }
                grid[i][j] = '.';
                grid[i][k] = 'O';
            }
        }
    }
    if (flip) {
        grid = transposeMatrix(grid);
    }

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'O') {
                cnt++;
            }
        }
        ans += (long long)((long long) cnt *  ((long long)n- (long long)i));
    }
    return ans;
}

long long MOD = 1000000000;

void solve(vector<vector<char>>& grid) {
    long long cnt = 0;
    vector<Cycle> cycles;
    while (1) {
        long long temp = 0;
        for (int i = 0; i < 4; i++) {
            bool flip = false;
            if (i % 4 == 0 || i % 4 == 2) {
                grid = transposeMatrix(grid);
                flip = true;
            }

            if (i % 4 == 3 || i % 4 == 2) {
                temp = getLoadf(grid, flip);
            }
            else {
                temp = getLoad(grid, flip);
            }
        }
        for (const auto& cycle : cycles) {
            if (cycle.grid == grid) {
                long long index = cycle.index;
                cout << index << " " << (cnt - index) << endl;
                long long diff = ((MOD - cnt - 1) % (cnt - index + 1)) - 1;
                cout << cycles[diff].load << endl;
                return;
            }
        }
        vector<vector<char>> tempGrid = grid;
        cnt++;
        cycles.push_back(Cycle(cnt, temp, tempGrid));
    }
    return;
    // cout << temp << endl;
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
    solve(inputs);

    return 0;
}