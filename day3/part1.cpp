#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

using namespace std;

bool isLegal(vector<vector<char>>& map, int i, int j) {
    return i >= 0 && i < map.size() && j >= 0 && j < map[0].size();
}

int getNum(vector<vector<char>>& map, int l, int r, int k, vector<vector<bool>>& seen) {
    string num = "";
    // cout << l << " " << r << " " << k << endl;
    while (isLegal(map, k, l)) {
        if (!isdigit(map[k][l])) {
            break;
        }
        num += map[k][l];
        seen[k][l] = 1;
        l--;
    }
    reverse(num.begin(), num.end());

    while (isLegal(map, k, r)) {
        if (!isdigit(map[k][r])) {
            break;
        }
        num += map[k][r];
        seen[k][r] = 1;
        r++;
    }
    // cout << num << endl;
    return stoi(num);
}

int main() {
    string line;
    vector<vector<char>> map;
    long long sum = 0;
    while (getline(cin, line)) {
        vector<char> row;
        for (int i = 0; i < line.length(); i++) {
            row.push_back(line[i]);
        }
        map.push_back(row);
    }

    vector<vector<bool>> seen(map.size(), vector<bool>(map[0].size(), 0));

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] != '.' && !isdigit(map[i][j])) {
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        if (k == 0 && l == 0) continue;
                        if (isLegal(map, i + k, j + l) && map[i + k][j + l] != '.' && isdigit(map[i + k][j + l]) && seen[i + k][j + l] == 0) {
                            int num = getNum(map, j+l, j + l + 1, i + k, seen);
                            sum += num;
                        }
                    }
                }
            }
        }
    }

    cout << sum << endl;

    return 0;
}