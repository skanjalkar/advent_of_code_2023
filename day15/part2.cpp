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

struct Labels {
    string sq;
    int focal;
    Labels(string s = "", int f = 0) : sq(s), focal(f) {}
};

struct Boxes {
    vector<Labels> labels;
    void add(string s, int f) {
        if (!update(s, f))
            labels.push_back(Labels(s, f));
    }

    void remove(string s) {
        for (int i = 0; i < labels.size(); i++) {
            if (labels[i].sq == s) {
                labels.erase(labels.begin() + i);
                return;
            }
        }
    }

    bool update(string s, int f) {
        for (int i = 0; i < labels.size(); i++) {
            if (labels[i].sq == s) {
                labels[i].focal = f;
                return true;
            }
        }
        return false;
    }

    int focusingPower(int boxNum) {
        int ans = 0;
        for (int i = 0; i < labels.size(); ++i) {
            ans += boxNum * (i+1) * labels[i].focal;
        }
        return ans;
    }
};

void printBox(vector<Boxes> & box) {
    for (int i = 0; i < 256; ++i) {
        cout << i+1 << ": ";
        for (int j = 0; j < box[i].labels.size(); ++j) {
            cout << box[i].labels[j].sq << " " << box[i].labels[j].focal << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve(vector<string>& seqeunces) {
    vector<Boxes> box(256);
    for (string & s : seqeunces) {
        // printBox(box);
        const int n = s.size();
        if (s[n-1] == '-') {
            string sq = s.substr(0, n-1);
            int boxNum = 0;
            for (char c: sq) {
                boxNum += int(c);
                boxNum = boxNum * 17;
                boxNum = boxNum % 256;
            }
            box[boxNum].remove(sq);
        }
        else {
            int boxNum = 0;
            // find position of '=' in string
            int pos = 0;
            for (int i = 0; i < n; ++i) {
                if (s[i] == '=') {
                    pos = i;
                    break;
                }
            }
            string sq = s.substr(0, pos);
            // find focal, which is string after '=' to the end
            int focal = stoi(s.substr(pos+1, n-pos-1));
            for (char c: sq) {
                boxNum += int(c);
                boxNum = boxNum * 17;
                boxNum = boxNum % 256;
            }
            // cout << sq << " " << focal << " " << boxNum << endl;
            box[boxNum].add(sq, focal);
        }
    }
    // printBox(box);
    int ans = 0;
    for (int i = 0; i < 256; ++i) {
        ans += box[i].focusingPower(i+1);
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