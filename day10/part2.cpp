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

// all possible dirs from a given direction, even diagonal
vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


enum Direction {UP, DOWN, LEFT, RIGHT};
vector<Direction> directions = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};

int main() {
    vector<vector<char>> matrix;
    string line;
    vector<vector<long long>> steps;
    int x, y;
    int cnt = 0;
    while (getline(cin, line)) {
        vector<char> row;
        for (int i = 0; i < line.size(); i++) {
            // cout << line[i] << " ";
            row.push_back(line[i]);
            if (row[i] == 'S') {
                x = cnt;
                y = i;
            }
        }
        cnt++;
        matrix.push_back(row);
    }
    // cout << x << " " << y << endl;
    int n = matrix.size();
    int m = matrix[0].size();
    steps.resize(n, vector<long long>(m, -1));

    unordered_map<char, vector<pair<Direction, Direction>> > charToDir = {
        {'|', {{Direction::UP, Direction::UP}, {Direction::DOWN, Direction::DOWN}}},
        {'-', {{Direction::RIGHT, Direction::RIGHT}, {Direction::LEFT, Direction::LEFT}}},
        {'L', {{Direction::DOWN, Direction::RIGHT}, {Direction::LEFT, Direction::UP}}},
        {'J', {{Direction::DOWN, Direction::LEFT}, {Direction::RIGHT, Direction::UP}}},
        {'7', {{Direction::UP, Direction::LEFT}, {Direction::RIGHT, Direction::DOWN}}},
        {'F', {{Direction::UP, Direction::RIGHT}, {Direction::LEFT, Direction::DOWN}}}
    };

    steps[x][y] = 0;
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    // queue of pair of x, y, direction
    queue<pair<pair<int, int>, Direction>> q;
    for (auto dir : directions) {
        q.push({{x, y}, dir});
    }
    visited[x][y] = true;

    while (!q.empty()) {
        pair<pair<int, int>, Direction> cur = q.front();
        q.pop();
        int curX = cur.first.first;
        int curY = cur.first.second;
        Direction curDir = cur.second;

        char currentChar = matrix[curX][curY];
        int newX = curX + dirs[curDir].first;
        int newY = curY + dirs[curDir].second;
        if (newX >= 0 && newX < n && newY >= 0 && newY < m && !visited[newX][newY]) {
            char newChar = matrix[newX][newY];
            if (newChar != '.') {
                vector<pair<Direction, Direction>> possibleDirs = charToDir[newChar];
                for (auto possibleDir : possibleDirs) {
                    if (possibleDir.first == curDir) {
                        steps[newX][newY] = steps[curX][curY] + 1;
                        q.push({{newX, newY}, possibleDir.second});
                        visited[newX][newY] = true;
                    }
                }
            }
        }
    }

    long long ans = 0;

    // shoot a ray from every point

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (visited[i][j]) continue;

            long long temp = 0;
            int x = i, y = j;

            while (x < n && y < m) {
                char curr = matrix[x][y];
                if (visited[x][y] && curr != 'L' && curr != '7') {
                    temp++;
                }
                x++;
                y++;
            }
            if (temp % 2 == 1) {
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}