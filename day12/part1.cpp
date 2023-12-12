#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool is_valid(const string &replacement, const vector<int> &sizes) {
    vector<int> group_lengths;
    int count = 0;

    for (char ch : replacement) {
        if (ch == '#') {
            count++;
        } else if (count > 0) {
            group_lengths.push_back(count);
            count = 0;
        }
    }
    if (count > 0) group_lengths.push_back(count);

    return group_lengths == sizes;
}

void generate_combinations(const string &conditions, vector<int> &sizes, string &current, int index, int &count) {
    if (index == conditions.size()) {
        if (is_valid(current, sizes)) {
            count++;
        }
        return;
    }

    if (conditions[index] == '?') {
        current[index] = '.';
        generate_combinations(conditions, sizes, current, index + 1, count);

        current[index] = '#';
        generate_combinations(conditions, sizes, current, index + 1, count);
    } else {
        current[index] = conditions[index];
        generate_combinations(conditions, sizes, current, index + 1, count);
    }
}

int count_arrangements(const string &spring_row, vector<int> &group_sizes) {
    vector<string> parts = split(spring_row, ' ');
    string conditions = parts[0];
    string current = conditions;

    int count = 0;
    generate_combinations(conditions, group_sizes, current, 0, count);
    return count;
}

int main() {
    string line;
    int total_count = 0;

    while (getline(cin, line)) {
        vector<string> input = split(line, ' ');
        vector<int> sizes;

        vector<string> size_strs = split(input[1], ',');
        for (const string &size_str : size_strs) {
            sizes.push_back(stoi(size_str));
        }

        total_count += count_arrangements(input[0], sizes);
    }

    cout << total_count << endl;
    return 0;
}
