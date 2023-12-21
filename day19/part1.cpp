#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// bool function which finds < in string

bool findLess(const string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '<') {
            return true;
        }
    }
    return false;
}

bool findGreater(const string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '>') {
            return true;
        }
    }
    return false;
}

bool findColon(const string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ':') {
            return true;
        }
    }
    return false;
}

long long t(unordered_map<string, long long>& values) {
    long long ans = 0;
    for (auto& x : values) {
        ans += x.second;
    }
    return ans;
}

void printValues(unordered_map<string, long long>& values) {
    for (auto& x : values) {
        cout << x.first << " " << x.second << endl;
    }
    cout << endl;
}


long long solve(unordered_map<string, string>& graph, unordered_map<string, long long>& values) {
    string key = "in";
    long long ans = 0;
    // printValues(values);
    while (1) {
        string value = graph[key];
        string token;
        stringstream ss(value);
        vector<string> tokens;
        // cout << key << endl;
        // cout << value << endl;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        for (const string& c : tokens) {
            int n = c.size();
            // cout << c << endl;
            if (findLess(c) && findColon(c)) {
                string first = c.substr(0, 1);
                size_t pos = c.find(':');
                string last = c.substr(pos + 1);
                long long middle = stoll(c.substr(2, n - 3));

                if (values[first] < middle && last.size() == 1 && last == "A") {
                    return t(values);
                }
                else if (values[first] < middle && last.size() == 1 && last == "R") {
                    return 0;
                }
                else if (values[first] < middle) {
                    key = last;
                    break;
                }
            }
            else if (findGreater(c) && findColon(c)) {
                string first = c.substr(0, 1);
                size_t pos = c.find(':');
                string last = c.substr(pos + 1);
                long long middle = stoll(c.substr(2, n - 3));
                if (values[first] > middle && last.size() == 1 && last == "A") {
                    return t(values);
                }
                else if (values[first] > middle && last.size() == 1 && last == "R") {
                    cout << first << endl;
                    return 0;
                }
                else if (values[first] > middle) {
                    key = last;
                    break;
                }
            }
            else {
                int n = c.size();
                if (n == 1) {
                    if (c == "A") {
                        return t(values);
                    }
                    else {
                        return 0;
                    }
                }
                else {
                    key = c;
                }
            }
        }
    }
    return ans;
}



int main() {
    string input;
    long long ans = 0;
    unordered_map<string, string> graph;
    while (getline(cin, input)) {
        if (input.empty()) {
            break;
        }
        stringstream ss(input);
        string from, to;
        ss >> from;
        ss >> to;
        graph[from] = to;
    }

    while (getline(cin, input)) {
        // split the string , and get the value of x,m,a,s

        string token;
        stringstream ss(input);
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        unordered_map<string, long long> values;
        for (const string& c : tokens) {
            size_t pos = c.find('=');
            string left = c.substr(0, pos);
            string right = c.substr(pos + 1);
            values[left] = stoll(right);
        }

        long long temp = solve(graph, values);
        ans += temp;
    }
    cout << ans << endl;
    return 0;
}
