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
    vector<string> endWithANodes;
    string network;
    while (getline(cin, network)) {
        if (network.empty()) {
            continue;
        }
        string from = network.substr(0, 3);
        string left = network.substr(7, 3);
        string right = network.substr(12, 3);

        nodes[from] = make_pair(left, right);
        if (from.back() == 'A') {
            endWithANodes.push_back(from);
        }
    }


    const int n = instructions.size();

    vector<long long> ans;
    // solve for each string
    // take lcm
    // but not guarantee  to have best solution
    for (string start : endWithANodes) {
        long long i = 0;
        string temp = start;
        while (temp.back() != 'Z') {
            string left = nodes[temp].first;
            string right = nodes[temp].second;
            char instruction = instructions[i % n];
            if (instruction == 'L') {
                // cout << left << endl;
                temp = left;
            } else {
                // cout << right << endl;
                temp = right;
            }
            i++;
        }
        ans.push_back(i);
    }

    // LCM of ans
    long long lcm = 1;
    for (long long i : ans) {
        lcm = (lcm * i) / __gcd(lcm, i);
    }

    cout << lcm << endl;

    return 0;
}