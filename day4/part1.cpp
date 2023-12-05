#include<iostream>
#include<stdlib.h>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<sstream>

using namespace std;

int main() {
    string line;
    long long sum = 0;

    while (getline(cin, line)) {
        size_t colon_pos = line.find(':');
        size_t bar_pos = line.find('|');
        string winning_numbers = line.substr(colon_pos+1, bar_pos - colon_pos-1);
        string our_numbers = line.substr(bar_pos + 1);
        // cout << our_numbers << endl;
        istringstream ss(winning_numbers);
        string token;
        unordered_set<int> winning_set;
        long long found = 0;
        while (ss >> token) {
            winning_set.insert(stoi(token));
        }
        istringstream ss2(our_numbers);
        // cout << our_numbers << endl;
        while (ss2 >> token) {
            if (token == " ") continue;
            if (winning_set.find(stoi(token)) != winning_set.end()) {
                if (found == 0) {
                    found = 1;
                }
                else {
                    found *= 2;
                }
            }
        }
        sum += found;
    }

    cout << sum << endl;

    return 0;
}
