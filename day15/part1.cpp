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

void solve(vector<string>& seqeunces) {
    int ans = 0;
    for (string & s : seqeunces) {
        int temp = 0;
        for (char c : s) {
            temp += int(c);
            temp = temp * 17;
            temp = temp % 256;
        }
        // cout << temp << endl;
        ans += temp;
    }
    cout << ans << endl;
}

int main() {
    string input;
    getline(cin, input);
    vector<string> sequences;
    // split string by all , and store in sequences
    stringstream ss(input);
    string token;
    while(getline(ss, token, ',')) {
        sequences.push_back(token);
    }

    solve(sequences);

    return 0;
}