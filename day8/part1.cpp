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

int main() {
    string instructions;
    getline(cin, instructions);

    unordered_map<string, pair<string, string>> nodes;

    string network;
    while (getline(cin, network)) {
        if (network.empty()) {
            continue;
        }
        string from = network.substr(0, 3);
        string left = network.substr(7, 3);
        string right = network.substr(12, 3);

        nodes[from] = make_pair(left, right);
    }

    string goal = "ZZZ";
    string start = "AAA";
    int i = 0;
    const int n = instructions.size();
    while (start != goal) {
        string left = nodes[start].first;
        string right = nodes[start].second;
        char instruction = instructions[i % n];
        if (instruction == 'L') {
            // cout << left << endl;
            start = left;
        } else {
            // cout << right << endl;
            start = right;
        }
        i++;
    }

    cout << i << endl;

    return 0;
}