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

void bfs(vector<vector<char>>& grid, long long i, long long j) {
    queue<pair<long long, long long>> q;
    q.push(make_pair(i, j));
    while (!q.empty()) {
        pair<long long, long long> p = q.front();
        q.pop();
        long long x = p.first;
        long long y = p.second;
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

void solve(vector<vector<char>>& grid, vector<pair<char, long long>>& instructions, long long minX, long long minY) {
    long long cx = 0;
    long long cy = 0;

    for (auto& p : instructions) {
        char dir = p.first;
        long long dist = p.second;
        // cout << dir << " " << dist << endl;
        if (dir == 'R') {
            for (long long i = 0; i < dist; i++) {
                cy++;
                grid[minY + cx][minX + cy] = '#';
            }
        } else if (dir == 'L') {
            for (long long i = 0; i < dist; i++) {
                cy--;
                grid[minY + cx][minX + cy] = '#';
            }
        } else if (dir == 'D') {
            for (long long i = 0; i < dist; i++) {
                cx++;
                grid[minY + cx][minX + cy] = '#';
            }
        } else if (dir == 'U') {
            for (long long i = 0; i < dist; i++) {
                cx--;
                grid[minY + cx][minX + cy] = '#';
            }
        } else {
            cout << "ERROR" << endl;
        }
    }
    long long ans = 0;

    for (long long i = 0; i < grid.size(); i++) {
        if (grid[i][0] == '.')
            bfs(grid, i, 0);
        if (grid[i][grid[0].size() - 1] == '.')
            bfs(grid, i, grid[0].size() - 1);
    }

    for (long long i = 0; i < grid[0].size(); i++) {
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
    long long maxX = -1;
    long long maxY = -1;
    long long minX = LONG_LONG_MAX;
    long long minY = LONG_LONG_MAX;
    long long currx = 0;
    long long curry = 0;
    vector<pair<char, long long>> instructions;
    while (getline(cin, input)) {
        stringstream ss(input);
        char dir;
        long long dist;
        ss >> dir >> dist;
        string s;
        ss >> s;
        s = s.substr(1, s.size() - 2);
        cout << s << " " <<  s.back() <<endl;
        // cout << dir << " " << dist << endl;
        if (s.back() == '0') {
            long long num = stoll(s.substr(0, s.size() - 1));
            currx += stoll(s.substr(0, s.size() - 1));
            instructions.push_back(make_pair('R', stoi(s.substr(0, s.size() - 1))));
        } else if (s.back() == '2') {
            instructions.push_back(make_pair('L', stoi(s.substr(0, s.size() - 1))));
            currx -= stoll(s.substr(0, s.size() - 1));
        } else if (s.back() == '1') {
            instructions.push_back(make_pair('D', stoi(s.substr(0, s.size() - 1))));
            curry += stoll(s.substr(0, s.size() - 1));
        } else if (s.back() == '3') {
            instructions.push_back(make_pair('U', stoi(s.substr(0, s.size() - 1))));
            curry -= stoll(s.substr(0, s.size() - 1));
        } else {
            cout << "ERROR" << endl;
        }
        minX = min(minX, currx);
        minY = min(minY, curry);
        maxX = max(maxX, currx);
        maxY = max(maxY, curry);
    }
    // cout << "maxX " << maxX << " maxY " << maxY << " minY " << minY << " minX " << minX  << "\n";
    vector<vector<char>> grid(abs(minY) + maxY + 1, vector<char>(abs(minX) + maxX + 1, '.'));
    solve(grid, instructions, abs(minX), abs(minY));
    return 0;
}