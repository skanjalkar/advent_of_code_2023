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

void dfs(int x, int y, vector<vector<char>>& matrix, vector<vector<bool>>& visited, vector<vector<vector<bool>>>& newVisited, int n, int m) {
    if (x < 0 || x >= n || y < 0 || y >= m || newVisited[x][y][0] || newVisited[x][y][1] || newVisited[x][y][2] || newVisited[x][y][3]) {
        return;
    }
    for (int i = 0; i < 4; ++i) {
        if (!newVisited[x][y][i]) {
            newVisited[x][y][i] = true;
            dfs(x + dirs[i].first, y + dirs[i].second, matrix, visited, newVisited, n, m);
            visited[x][y] = true;
        }
    }
}


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

    // find pairs of chars that can be squeezed
    // all that map to up or down and if they are side by side can be squeezed
    // all that map to left right and if they are up and down can be squeezed
    // also have to check the direction in which they are being visited

    unordered_set<char> verticalSqueeze = {'|', 'L', 'J', '7', 'F'};
    unordered_set<char> horizontalSqueeze = {'-', 'L', 'J', '7', 'F'};
    unordered_map<char, vector<char>> digaonalVSqueeze = {{'|', {'F', 'L'}}, {'J', {'|', 'F', 'L'}}, {'7', {'|', 'F', 'L'}}};
    unordered_map<char, vector<char>> diagonalHSqueeze = {{'-', {'L', 'J'}}, {'F', {'-', 'L', 'J'}}, {'7', {'-', 'L', 'J'}}};
    vector<vector<vector<bool>>> newVisited(n, vector<vector<bool>>(m, vector<bool>(4, false)));
    for (int i = 1; i < n-1; ++i) {
        for (int j = 0; j < m-1; ++j) {
            if (matrix[i][j] != '.' && matrix[i][j+1] != '.' && verticalSqueeze.count(matrix[i][j]) && verticalSqueeze.count(matrix[i][j+1])) {
                newVisited[i][j][2] = true;
                newVisited[i][j][3] = true;
                newVisited[i][j+1][2] = true;
                newVisited[i][j+1][3] = true;
            }
            if (matrix[i][j] != '.' && matrix[i-1][j+1] != '.' && digaonalVSqueeze.count(matrix[i][j]) && digaonalVSqueeze.count(matrix[i-1][j+1])) {
                newVisited[i][j][2] = true;
                newVisited[i][j][3] = true;
                newVisited[i-1][j+1][2] = true;
                newVisited[i-1][j+1][3] = true;
            }
            if (matrix[i][j] != '.' && matrix[i+1][j+1] != '.' && digaonalVSqueeze.count(matrix[i][j]) && digaonalVSqueeze.count(matrix[i+1][j+1])) {
                newVisited[i][j][2] = true;
                newVisited[i][j][3] = true;
                newVisited[i+1][j+1][2] = true;
                newVisited[i+1][j+1][3] = true;
            }
        }
    }

    for (int i = 0; i < n-1; ++i) {
        for (int j = 1; j < m-1; ++j) {
            if (matrix[i][j] != '.' && matrix[i+1][j] != '.' && horizontalSqueeze.count(matrix[i][j]) && horizontalSqueeze.count(matrix[i+1][j])) {
                newVisited[i][j][0] = true;
                newVisited[i][j][1] = true;
                newVisited[i+1][j][0] = true;
                newVisited[i+1][j][1] = true;
            }
            if (matrix[i][j] != '.' && matrix[i+1][j-1] != '.' && diagonalHSqueeze.count(matrix[i][j]) && diagonalHSqueeze.count(matrix[i+1][j-1])) {
                newVisited[i][j][0] = true;
                newVisited[i][j][1] = true;
                newVisited[i+1][j-1][0] = true;
                newVisited[i+1][j-1][1] = true;
            }
            if (matrix[i][j] != '.' && matrix[i+1][j+1] != '.' && diagonalHSqueeze.count(matrix[i][j]) && diagonalHSqueeze.count(matrix[i+1][j+1])) {
                newVisited[i][j][0] = true;
                newVisited[i][j][1] = true;
                newVisited[i+1][j+1][0] = true;
                newVisited[i+1][j+1][1] = true;
            }
        }
    }

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         cout << visited[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;

    // print new visited
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << "(" << i << ", " << j << "): ";
            for (int k = 0; k < 4; ++k) {
                cout << newVisited[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }


    for (int i = 0; i < n; ++i) {
        if (matrix[i][0] == '.' && !visited[i][0]) {
            dfs(i, 0, matrix, visited, newVisited, n, m);
        }
    }
    for (int j = 0; j < m; ++j) {
        if (matrix[0][j] == '.' && !visited[0][j]) {
            dfs(0, j, matrix, visited, newVisited, n, m);
        }
    }

    for (int i = n-1; i >= 0; --i) {
        if (matrix[i][m-1] == '.' && !visited[i][m-1]) {
            dfs(i, m-1, matrix, visited, newVisited, n, m);
        }
    }

    for (int j = m-1; j >= 0; --j) {
        if (matrix[n-1][j] == '.' && !visited[n-1][j]) {
            dfs(n-1, j, matrix, visited, newVisited, n, m);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << visited[i][j] << " ";
        }
        cout << endl;
    }

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!visited[i][j]) {
                ans++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}