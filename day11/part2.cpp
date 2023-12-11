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


struct Node
{
    char x;
    long long gx;
    long long gy;

    Node(char x, long long gx, long long gy) : x(x), gx(gx), gy(gy) {}
};

long long euclDiff(vector<vector<Node>>& newGrid, pair<int, int> s, pair<int, int> e) {
    long long sum = 0;
    sum = abs(s.first - e.first) + abs(s.second - e.second) + abs(newGrid[e.first][e.second].gx - newGrid[s.first][s.second].gx)*(1000000-1) + abs(newGrid[e.first][e.second].gy - newGrid[s.first][s.second].gy)*(1000000-1);
    return sum;
}

vector<vector<Node>> update(vector<vector<char>>& grid) {
    vector<vector<Node>> newGrid;
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
    int cntx = 0;
    for (int i = 0; i < grid.size(); i++) {
        vector<Node> newRow;
        int cnt = 0;
        for (int j = 0; j < grid[i].size(); j++) {
            if (col.find(j) != col.end()) {
                newRow.push_back(Node(grid[i][j], 0, ++cnt));
            }
            else {
                newRow.push_back(Node(grid[i][j], 0, cnt));
            }
        }
        if (row.find(i) != row.end()) {
            cntx++;
        }
        for (Node & n : newRow) {
            n.gx = cntx;
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

    vector<vector<Node>>newGrid = update(grid);
    vector<pair<int, int>> pos;
    for (int i = 0; i < newGrid.size(); ++i) {
        for (int j = 0; j < newGrid[i].size(); ++j) {
            if (newGrid[i][j].x == '#') {
                pos.push_back(make_pair(i, j));
            }
        }
    }

    long long ans = 0;

    for (int i = 0; i < pos.size(); ++i) {
        // cout << newGrid[pos[i].first][pos[i].second].gx << " " << newGrid[pos[i].first][pos[i].second].gy << endl;
        for (int j = i + 1; j < pos.size(); ++j) {
            long long sum = euclDiff(newGrid, pos[i], pos[j]);
            ans += sum;
        }
    }
    cout << ans << endl;
    return 0;
}
