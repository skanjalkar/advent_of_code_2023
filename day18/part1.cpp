#include <bits/stdc++.h>
#include <iostream>
using namespace std;

void printGrid(vector<vector<char>>& grid) {
    for (auto& row : grid) {
        for (auto& c : row) {
            cout << c;
        }
        cout << endl;
    }
    cout << endl;
}

void bfs(vector<vector<char>>& grid, int i, int j) {
    queue<pair<int, int>> q;
    q.push(make_pair(i, j));
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        int x = p.first;
        int y = p.second;
        // cout << x << " " << y << endl;
        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size()) {
            continue;
        }
        if (grid[x][y] == '#' || grid[x][y] == '$') {
            continue;
        }
        grid[x][y] = '$';
        q.push(make_pair(x + 1, y));
        q.push(make_pair(x - 1, y));
        q.push(make_pair(x, y + 1));
        q.push(make_pair(x, y - 1));
    }
}

void solve(vector<vector<char>>& grid, vector<pair<char, int>>& instructions) {
    int cx = 0;
    int cy = 0;

    for (auto& p : instructions) {
        char dir = p.first;
        int dist = p.second;
        if (dir == 'R') {
            for (int i = 0; i < dist; i++) {
                cy++;
                grid[cx][cy] = '#';
            }
        } else if (dir == 'L') {
            for (int i = 0; i < dist; i++) {
                cy--;
                grid[cx][cy] = '#';
            }
        } else if (dir == 'D') {
            for (int i = 0; i < dist; i++) {
                cx++;
                grid[cx][cy] = '#';
            }
        } else if (dir == 'U') {
            for (int i = 0; i < dist; i++) {
                cx--;
                grid[cx][cy] = '#';
            }
        } else {
            cout << "ERROR" << endl;
        }
    }
    int ans = 0;

    for (int i = 0; i < grid.size(); i++) {
        if (grid[i][0] == '.')
            bfs(grid, i, 0);
        if (grid[i][grid[0].size() - 1] == '.')
            bfs(grid, i, grid[0].size() - 1);
    }

    for (int i = 0; i < grid[0].size(); i++) {
        if (grid[0][i] == '.')
            bfs(grid, 0, i);
        if (grid[grid.size() - 1][i] == '.')
            bfs(grid, grid.size() - 1, i);
    }

    for (auto& row : grid) {
        for (auto& c : row) {
            if (c == '.' || c == '#') {
                ans++;
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    string input;
    int maxX = -1;
    int maxY = -1;
    int currx = 0;
    int curry = 0;
    vector<pair<char, int>> instructions;
    while (getline(cin, input)) {
        stringstream ss(input);
        char dir;
        int dist;
        ss >> dir >> dist;
        // cout << dir << " " << dist << endl;
        instructions.push_back(make_pair(dir, dist));
        if (dir == 'R') {
            currx += dist;
        } else if (dir == 'L') {
            currx -= dist;
        } else if (dir == 'D') {
            curry += dist;
        } else if (dir == 'U') {
            curry -= dist;
        } else {
            cout << "ERROR" << endl;
        }
        maxX = max(maxX, currx);
        maxY = max(maxY, curry);
    }
    // cout << "maxX " << maxX << " maxY " << maxY << "\n";
    vector<vector<char>> grid(maxY + 1, vector<char>(maxX + 1, '.'));
    solve(grid, instructions);
    return 0;
}