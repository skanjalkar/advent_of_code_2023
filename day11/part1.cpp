#include<iostream>
#include<stdlib.h>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<sstream>
#include<limits.h>
#include<queue>
using namespace std;

long long euclDiff(vector<vector<char>>& newGrid, pair<int, int> s, pair<int, int> e) {
    long long sum = 0;
    sum = abs(s.first - e.first) + abs(s.second - e.second);
    return sum;
}

vector<vector<char>> update(vector<vector<char>>& grid) {
    vector<vector<char>> newGrid;
    unordered_set<int> row;
    unordered_set<int> col;

    for (int i = 0; i < grid.size(); i++) {
        int cnt = 0;
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '#') {
                cnt++;
            }
        }
        if (cnt == 0) {
            row.insert(i);
        }
    }

    for (int j = 0; j < grid[0].size(); j++) {
        int cnt = 0;
        for (int i = 0; i < grid.size(); i++) {
            if (grid[i][j] == '#') {
                cnt++;
            }
        }
        if (cnt == 0) {
            col.insert(j);
        }
    }

    for (int i = 0; i < grid.size(); i++) {
        vector<char> newRow;
        for (int j = 0; j < grid[i].size(); j++) {
            if (col.find(j) != col.end()) {
                newRow.push_back(grid[i][j]);
            }
            newRow.push_back(grid[i][j]);
        }
        if (row.find(i) != row.end()) {
            newGrid.push_back(newRow);
        }
        newGrid.push_back(newRow);
    }
    return newGrid;

}

int main() {
    vector<vector<char>> grid;
    string input;
    while (getline(cin, input)) {
        vector<char> row;
        for (int i = 0; i < input.size(); i++) {
            row.push_back(input[i]);
        }
        grid.push_back(row);
    }

    vector<vector<char>>newGrid = update(grid);
    vector<pair<int, int>> pos;
    for (int i = 0; i < newGrid.size(); ++i) {
        for (int j = 0; j < newGrid[i].size(); ++j) {
            if (newGrid[i][j] == '#') {
                pos.push_back(make_pair(i, j));
            }
        }
    }
    long long sum = 0;
    int cnt = 0;
    for (int i = 0; i < pos.size(); ++i) {
        for (int j = i + 1; j < pos.size(); ++j) {
            sum += euclDiff(newGrid, pos[i], pos[j]);
            cnt++;
        }
    }
    cout << sum << endl;

    return 0;
}
