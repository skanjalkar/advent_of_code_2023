#include <bits/stdc++.h>
#include <iostream>
#include <utility>

using namespace std;

void printGrid(const vector<vector<int>>& grid) {
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

struct pair_hash {
    inline size_t operator()(const pair<int, int> & v) const {
        return v.first * 31 + v.second;
    }
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Node {
    int i;
    int j;
    int cnt;
    int cost;
    Direction dir;
    Node(int i, int j, int cnt, int cost, Direction dir) : i(i), j(j), cnt(cnt), cost(cost), dir(dir) {}

    bool operator<(const Node& other) const {
        return cost > other.cost;
    }

    bool operator==(const Node& other) const {
        return i == other.i && j == other.j && cnt == other.cnt && dir == other.dir;
    }

    bool operator!=(const Node& other) const {
        return !(*this == other);
    }

    bool operator>(const Node& other) const {
        return cost < other.cost;
    }

    void print() {
        cout << "i: " << i << " j: " << j << " cnt: " << cnt << " cost: " << cost << " dir: " << dir << endl;
    }
};

bool valid(int i, int j, const vector<vector<int>>& grid) {
    return i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size();
}

unordered_map<Direction, vector<pair<int, int>>> dirMap = {
    {Direction::UP, {{-1, 0}, {0, -1}, {0, 1}}},
    {Direction::DOWN, {{1, 0}, {0, -1}, {0, 1}}},
    {Direction::LEFT, {{0, -1}, {-1, 0}, {1, 0}}},
    {Direction::RIGHT, {{0, 1}, {1, 0}, {-1, 0}}}
};

unordered_map<pair<int, int>, Direction, pair_hash> dirMap2 = {
    {{-1, 0}, Direction::UP},
    {{1, 0}, Direction::DOWN},
    {{0, -1}, Direction::LEFT},
    {{0, 1}, Direction::RIGHT}
};

// vector hash
namespace std {
    template <>
    struct hash<vector<int>> {
        size_t operator()(const vector<int>& v) const {
            size_t seed = 0;
            for (auto& i : v) {
                seed ^= hash<int>()(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

struct Compare {
    bool operator()(const Node& n1, const Node& n2) {
        return n1.cost > n2.cost;
    }
};

void solve(vector<vector<int>>& grid, int si, int sj) {
    Node start = Node(si, sj, 0, 0, Direction::RIGHT);
    // convert pq to min heap
    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push(start);
    unordered_map<vector<int>, int> visited;

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        vector<int> v = {node.cnt, node.i, node.j, static_cast<int>(node.dir)};
        if (node.i == grid.size() - 1 && node.j == grid[0].size() - 1) {
            cout << node.cost << endl;
            return;
        }

        if (visited.find(v) != visited.end()) {
            continue;
        }
        // node.print();
        visited[v] = node.cost;

        for (auto d : dirMap[node.dir]) {
            int ni = node.i + d.first;
            int nj = node.j + d.second;
            if (valid(ni, nj, grid)) {
                if (dirMap2[d] == node.dir && node.cnt + 1 <= 3) {
                    Node temp = Node(ni, nj, node.cnt + 1, node.cost + grid[ni][nj], dirMap2[d]);
                    pq.push(temp);
                }
                else if (dirMap2[d] != node.dir){
                    Node temp = Node(ni, nj, 1, node.cost + grid[ni][nj], dirMap2[d]);
                    pq.push(temp);
                }
            }
        }
    }

    return;
}

int main() {
    string input;
    vector<vector<int>> grid;
    while(getline(cin, input)) {
        vector<int> row;
        for (int i = 0; i < input.size(); i++) {
            row.push_back(input[i] - '0');
        }
        grid.push_back(row);
    }

    // printGrid(grid);

    solve(grid, 0, 0);


    return 0;
}