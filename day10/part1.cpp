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

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int> & v) const {
        return std::hash<int>()(v.first) ^ std::hash<int>()(v.second);
    }
};

void solve(vector<vector<bool>>& visited, vector<vector<char>>& matrix, vector<vector<long long>>& steps, int x, int y, int n, int m, unordered_map<char, vector<Direction>>& dirMap, unordered_map<Direction, vector<char>>& dirToChar, vector<Direction>& directions) {
    if (visited[x][y]) {
        return;
    }
    visited[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int nx = x + dirs[i].first;
        int ny = y + dirs[i].second;
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && matrix[nx][ny] != '.') {
            Direction currentDir = directions[i];
            // check if matrix[nx][ny] is in dirTochar[currentDir]
            if (find(dirToChar[currentDir].begin(), dirToChar[currentDir].end(), matrix[nx][ny]) != dirToChar[currentDir].end()) {
                steps[nx][ny] = max(steps[nx][ny], steps[x][y] + 1);
                solve(visited, matrix, steps, nx, ny, n, m, dirMap, dirToChar, directions);
            }
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


    /*
    | is a vertical pipe connecting north and south.unordered_map<pair<int, int>, Direction, pair_hash> dirToPair = {
        {{-1, 0}, Direction::UP},
        {{1, 0}, Direction::DOWN},
        {{0, -1}, Direction::LEFT},
        {{0, 1}, Direction::RIGHT}
    };
    - is a horizontal pipe connecting east and west.
    L is a 90-degree bend connecting north and east.
    J is a 90-degree bend connecting north and west.
    7 is a 90-degree bend connecting south and west.
    F is a 90-degree bend connecting south and east.
    . is ground; there is no pipe in this tile.
    S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.
    */

    unordered_map<char, vector<Direction>> dirMap = {
        {'|', {Direction::UP, Direction::DOWN}},
        {'-', {Direction::LEFT, Direction::RIGHT}},
        {'L', {Direction::UP, Direction::RIGHT}},
        {'J', {Direction::UP, Direction::LEFT}},
        {'7', {Direction::DOWN, Direction::LEFT}},
        {'F', {Direction::DOWN, Direction::RIGHT}},
        {'S', {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT}}
    };

    unordered_map<Direction, vector<char>> dirToChar = {
        {Direction::UP, {'|', 'L', 'J', 'S'}},
        {Direction::DOWN, {'|', '7', 'F', 'S'}},
        {Direction::LEFT, {'-', 'L', '7', 'S'}},
        {Direction::RIGHT, {'-', 'J', 'F', 'S'}}
    };
    vector<Direction> directions = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    steps[x][y] = 0;

    solve(visited, matrix, steps, x, y, n, m, dirMap, dirToChar, directions);

    // max in steps
    long long maxSteps = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0 ; j < m; j++) {
            maxSteps = max(maxSteps, steps[i][j]);
        }
    }
    cout << maxSteps << endl;
    return 0;
}