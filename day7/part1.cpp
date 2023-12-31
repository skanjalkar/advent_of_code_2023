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

enum hand {
    FIVE,
    FOUR,
    FULL,
    THREE,
    TWO,
    ONE,
    HIGH
};



unordered_map<char, int> values = {
    {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5},
    {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
    {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13},
    {'A', 14}
};

struct Bids {
    string name;
    int price;
    hand h;
    unordered_map<char, int> unique_c;

    // constructor
    Bids(string n, int p) : name(n), price(p) {
        setHand();
    }

    // check which hand it is and assign the hand
    void setHand() {
        for (char& c : name) {
            unique_c[c]++;
        }
        if (unique_c.size() == 1) {
            h = FIVE;
        } else if (unique_c.size() == 2) {
            for (auto& x : unique_c) {
                if (x.second == 4) {
                    h = FOUR;
                    return;
                }
            }
            h = FULL;
        } else if (unique_c.size() == 3) {
            for (auto& x : unique_c) {
                if (x.second == 3) {
                    h = THREE;
                    return;
                }
            }
            h = TWO;
        } else if (unique_c.size() == 4) {
            h = ONE;
        } else {
            h = HIGH;
        }
    }

    bool operator<(const Bids& b) const {
        if (h != b.h) {
            return h < b.h;
        }
        int i = 0;
        while (i < name.size()) {
            if (values[name[i]] != values[b.name[i]]) {
                // cout << name[i] << " " << b.name[i] << endl;
                return values[name[i]] > values[b.name[i]];
            }
            i++;
        }
        return false;
    }

};


int main() {
    string line;

    vector<Bids> bids;
    while (getline(cin, line)) {
        string cards = line.substr(0, line.find(" "));
        int price = stoi(line.substr(line.find(" ") + 1));
        bids.push_back(Bids(cards, price));
    }
    // cout << "\n";
    // print bids
    // for (auto& x : bids) {
    //     cout << x.name << " " << x.price << endl;
    // }
    sort(bids.begin(), bids.end());
    // print bids
    // cout << "\n";
    // for (auto& x : bids) {
    //     cout << x.name << " " << x.price << endl;
    // }
    long long ans = 0;
    const int n = bids.size();
    for (int i = 0; i < n; i++) {
        ans += bids[i].price*(n-i);
    }

    cout << ans << endl;

    return 0;
}