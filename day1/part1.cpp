#include<iostream>
#include<stdlib.h>

using namespace std;

int main() {
    // parse input line by line
    string line;
    long long sum = 0;
    while (getline(cin, line)) {
        // convert string to int
        int left, right;
        const int n = line.size();
        for (int i = 0; i < n; i++) {
            if (line[i]-'0' <= 9 && line[i]-'0' >= 0) {
                // convert character to int
                left = line[i]-'0';
                break;
            }
        }
        for (int j = n - 1; j >= 0; j--) {
            if (line[j]-'0' <= 9 && line[j]-'0' >= 0) {
                // convert character to int
                right = line[j]-'0';
                break;
            }
        }
        sum += left*10 + right;
        // cout << sum << "\n";
    }
    cout << sum << endl;
    return 0;
}
