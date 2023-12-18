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

#define vertical (grid[beams[i].y][beams[i].x] == '.' || grid[beams[i].y][beams[i].x] == '|')
#define horizontal (grid[beams[i].y][beams[i].x] == '-' || grid[beams[i].y][beams[i].x] == '.')
#define valid (beams[i].x >= 0 && beams[i].x < grid[0].size() && beams[i].y >= 0 && beams[i].y < grid.size())
#define invalid (beams[i].x < 0 || beams[i].x >= grid[0].size() || beams[i].y < 0 || beams[i].y >= grid.size())

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Beam {
    int x;
    int y;
    Direction dir;
    Beam(int x, int y, Direction dir) : x(x), y(y), dir(dir) {}

    bool operator==(const Beam& other) const {
        return x == other.x && y == other.y && dir == other.dir;
    }
};

void printEnergy(vector<vector<bool>>& energized) {
    for (int i = 0; i < energized.size(); i++) {
        for (int j = 0; j < energized[i].size(); j++) {
            if (energized[i][j]) {
                cout << "# ";
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

struct PairHash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        // Use a combination of the default hash for the first and second elements
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);

        // Combine the two hashes. Here, we use a simple shifting method,
        // but more sophisticated methods can be used.
        return hash1 ^ (hash2 << 1);
    }
};

void printBeams(vector<Beam>& b) {
    for (int i = 0; i < b.size(); i++) {
        cout << b[i].x << " " << b[i].y << " ";
        if (b[i].dir == Direction::UP) {
            cout << "UP" << endl;
        }
        else if (b[i].dir == Direction::DOWN) {
            cout << "DOWN" << endl;
        }
        else if (b[i].dir == Direction::LEFT) {
            cout << "LEFT" << endl;
        }
        else {
            cout << "RIGHT" << endl;
        }
    }
    cout << endl;

}

void printBeam(Beam& b) {
    cout << b.x << " " << b.y << " ";
    if (b.dir == Direction::UP) {
        cout << "UP" << endl;
    }
    else if (b.dir == Direction::DOWN) {
        cout << "DOWN" << endl;
    }
    else if (b.dir == Direction::LEFT) {
        cout << "LEFT" << endl;
    }
    else {
        cout << "RIGHT" << endl;
    }
}

int solve(vector<vector<char>>& grid, int sx, int sy, Direction dir1) {
    vector<vector<bool>> energized(grid.size(), vector<bool>(grid[0].size(), false));
    unordered_map<Direction, Direction> dirMap = {
        {Direction::UP, Direction::DOWN},
        {Direction::DOWN, Direction::UP},
        {Direction::LEFT, Direction::RIGHT},
        {Direction::RIGHT, Direction::LEFT}
    };

    unordered_map<pair<char, Direction>, Direction, PairHash> turnMap = {
        {{'/', Direction::UP}, Direction::RIGHT},
        {{'/', Direction::DOWN}, Direction::LEFT},
        {{'/', Direction::LEFT}, Direction::DOWN},
        {{'/', Direction::RIGHT}, Direction::UP},
        {{'\\', Direction::UP}, Direction::LEFT},
        {{'\\', Direction::DOWN}, Direction::RIGHT},
        {{'\\', Direction::LEFT}, Direction::UP},
        {{'\\', Direction::RIGHT}, Direction::DOWN}
    };

    vector<Beam> beams;
    Beam b = {sx, sy, dir1};
    beams.push_back(b);
    int cnt = 0;
    int j = 0;
    while (!beams.empty()) {
        j++;
        int n = beams.size();
        vector<vector<bool>> prev = energized;

        for (int i = 0; i < n; i++) {
            if (beams[i].dir == Direction::RIGHT && valid && horizontal) {
                energized[beams[i].y][beams[i].x] = true;
                beams[i].x++;
            }
            else if (beams[i].dir == Direction::LEFT && valid && horizontal) {
                energized[beams[i].y][beams[i].x] = true;
                beams[i].x--;
            }
            else if (beams[i].dir == Direction::UP && valid && vertical) {
                energized[beams[i].y][beams[i].x] = true;
                beams[i].y--;
            }
            else if (beams[i].dir == Direction::DOWN && valid && vertical) {
                energized[beams[i].y][beams[i].x] = true;
                beams[i].y++;
            }
            else {
                if (valid) {
                    energized[beams[i].y][beams[i].x] = true;
                }
                if (invalid) {
                    beams[i].x = -1;
                    beams[i].y = -1;
                    continue;
                }

                char c = grid[beams[i].y][beams[i].x];
                if (c == '/' || c == '\\') {
                    beams[i].dir = turnMap[{c, beams[i].dir}];
                    // also need to move direction
                    if (beams[i].dir == Direction::RIGHT) {
                        beams[i].x++;
                    }
                    else if (beams[i].dir == Direction::LEFT) {
                        beams[i].x--;
                    }
                    else if (beams[i].dir == Direction::UP) {
                        beams[i].y--;
                    }
                    else {
                        beams[i].y++;
                    }
                }
                else {
                    if (beams[i].dir == Direction::RIGHT) {
                        beams[i].dir = Direction::UP;
                        beams[i].y--;
                    }
                    else if (beams[i].dir == Direction::UP) {
                        beams[i].dir = Direction::LEFT;
                        beams[i].x--;
                    }
                    else if (beams[i].dir == Direction::LEFT) {
                        beams[i].dir = Direction::DOWN;
                        beams[i].y++;
                    }
                    else if (beams[i].dir == Direction::DOWN) {
                        beams[i].dir = Direction::RIGHT;
                        beams[i].x++;
                    }
                    int newX = beams[i].x;
                    int newY = beams[i].y;
                    if (beams[i].dir == Direction::RIGHT) {
                        newX -= 2;
                    }
                    else if (beams[i].dir == Direction::LEFT) {
                        newX += 2;
                    }
                    else if (beams[i].dir == Direction::UP) {
                        newY += 2;
                    }
                    else if (beams[i].dir == Direction::DOWN) {
                        newY -= 2;
                    }
                    Beam newBeam = {newX, newY, dirMap[beams[i].dir]};
                    beams.push_back(newBeam);
                }
            }

        }
        if (energized == prev)
            cnt++;
        if (cnt == 3) {
            break;
        }
        for (int i = 0; i < beams.size(); i++) {
            if (beams[i].x == -1 && beams[i].y == -1) {
                beams.erase(beams.begin() + i);
                i--;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < energized.size(); i++) {
        for (int j = 0; j < energized[i].size(); j++) {
            if (energized[i][j]) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    string input;
    vector<vector<char>> grid;
    while (getline(cin, input)) {
        vector<char> row;
        for (int i = 0; i < input.size(); i++) {
            row.push_back(input[i]);
        }
        grid.push_back(row);
    }

    int ans = -1;
    for (int i = 0; i < grid.size(); i++) {
        ans = max(ans, solve(grid, 0, i, Direction::RIGHT));
        ans = max(ans, solve(grid, grid.size()-1, i, Direction::LEFT));
    }

    for (int i = 0; i < grid[0].size(); i++) {
        ans = max(ans, solve(grid, i, 0, Direction::DOWN));
        ans = max(ans, solve(grid, i, grid[0].size() - 1, Direction::UP));
    }

    cout << ans << endl;

    return 0;
}