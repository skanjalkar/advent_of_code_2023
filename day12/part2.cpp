#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <unordered_map>

using namespace std;

struct vector_hash {
    size_t operator()(const vector<int> &v) const {
        hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

unordered_map<vector<int>, long long, vector_hash> memo;

// index = current index in spring_row
// group_index = current index in group_sizes
// current = current size of group
// memo[(index, group_index, current)] = number of arrangements from index to end of spring_row
// with group_sizes[group_index] == current

long long count_arrangements(const string &spring_row, vector<int> &group_sizes, int index, int group_index, int current) {
    vector<int> key = {index, group_index, current};
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }
    // base case
    if (index == spring_row.size()) {
        if (group_index == group_sizes.size() && current == 0) {
            return 1;
        }
        else if (group_index == group_sizes.size() - 1 && group_sizes[group_index] == current) {
            return 1;
        }
        else {
            return 0;
        }
    }
    long long temp = 0;
    for (char c : {'.', '#'}) {
        if (spring_row[index] == c || spring_row[index] == '?') {
            if (c == '.' && current == 0) {
                temp += count_arrangements(spring_row, group_sizes, index + 1, group_index, 0);
            }
            else if (c == '.' && current > 0 && group_index < group_sizes.size() && group_sizes[group_index] == current) {
                temp += count_arrangements(spring_row, group_sizes, index + 1, group_index + 1, 0);
            }
            else if (c == '#') {
                temp += count_arrangements(spring_row, group_sizes, index + 1, group_index, current + 1);
            }
        }
    }
    memo[key] = temp;
    return temp;

}

int main() {
    string line;
    long long ans = 0;

    while (getline(cin, line)) {
        vector<string> input = split(line, ' ');
        // multiply input[0] by 5 and split it by '?'
        // do the same for input[1]

        string newInput;
        for (int i = 0; i < 5; i++) {
            newInput += input[0];
            newInput += (i == 4) ? "" : "?";
        }

        vector<int> sizes;

        for (int i = 0; i < 5; ++i) {
            vector<string> size_strs = split(input[1], ',');
            for (const string &size_str : size_strs) {
                sizes.push_back(stoi(size_str));
            }
        }


        ans += count_arrangements(newInput, sizes, 0, 0, 0);
        memo.clear();
    }

    cout << ans << endl;
    return 0;
}
