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
    unordered_map<int, int> cards;
    while (getline(cin, line)) {
        size_t colon_pos = line.find(':');
        int id = stoi(line.substr(5, colon_pos-5));

        size_t bar_pos = line.find('|');
        string winning_numbers = line.substr(colon_pos+1, bar_pos - colon_pos-1);
        string our_numbers = line.substr(bar_pos + 1);
        // cout << our_numbers << endl;
        istringstream ss(winning_numbers);
        string token;
        unordered_set<int> winning_set;
        long long matches = 0;
        while (ss >> token) {
            winning_set.insert(stoi(token));
        }
        istringstream ss2(our_numbers);
        // cout << our_numbers << endl;
        while (ss2 >> token) {
            if (token == " ") continue;
            if (winning_set.find(stoi(token)) != winning_set.end()) {
                matches++;
            }
        }
        if (cards.count(id) == 0) {
            cards[id] = 1;
        }
        else {
            cards[id]++;
        }

        for (int i = id + 1; i <= id + matches; i++) {
            if (cards.count(i) == 0) {
                cards[i] = cards[id];
            }
            else {
                cards[i] += cards[id];
            }
        }
    }
    for (auto it = cards.begin(); it != cards.end(); it++) {
        sum += it->second;
    }
    cout << sum << endl;

    return 0;
}
