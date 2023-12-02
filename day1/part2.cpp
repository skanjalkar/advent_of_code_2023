#include<iostream>
#include<stdlib.h>
#include<unordered_set>

using namespace std;

unordered_set<string> DIGITS_IN_WORDS = unordered_set<string> {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main() {
    string line;
    long long sum = 0;

    while (getline(cin, line)) {
        int left, right;
        const int n = line.size();
        for (int i = 0; i < n; i++) {
            if (line[i]-'0' <= 9 && line[i]-'0' >= 0) {
                // convert character to int
                left = line[i]-'0';
                break;
            }
            // check first character and do substring match
            if (line[i] == 'z' && line.substr(i, 4) == "zero") {
                left = 0;
                break;
            }
            if (line[i] == 't' && line.substr(i, 3) == "two") {
                left = 2;
                break;
            }
            if (line[i] == 'f' && line.substr(i, 4) == "four") {
                left = 4;
                break;
            }
            if (line[i] == 's' && line.substr(i, 3) == "six") {
                left = 6;
                break;
            }
            if (line[i] == 'e' && line.substr(i, 5) == "eight") {
                left = 8;
                break;
            }
            if (line[i] == 'o' && line.substr(i, 3) == "one") {
                left = 1;
                break;
            }
            if (line[i] == 't' && line.substr(i, 5) == "three") {
                left = 3;
                break;
            }
            if (line[i] == 'f' && line.substr(i, 4) == "five") {
                left = 5;
                break;
            }
            if (line[i] == 's' && line.substr(i, 5) == "seven") {
                left = 7;
                break;
            }
            if (line[i] == 'n' && line.substr(i, 4) == "nine") {
                left = 9;
                break;
            }
        }

        for (int j = n - 1; j >= 0; j--) {
            if (line[j]-'0' <= 9 && line[j]-'0' >= 0) {
                // convert character to int
                right = line[j]-'0';
                break;
            }
            // check last character and do substring match
            if (line[j] == 'z' && line.substr(j, 4) == "zero") {
                right = 0;
                break;
            }
            if (line[j] == 't' && line.substr(j, 3) == "two") {
                right = 2;
                break;
            }
            if (line[j] == 'f' && line.substr(j, 4) == "four") {
                right = 4;
                break;
            }
            if (line[j] == 's' && line.substr(j, 3) == "six") {
                right = 6;
                break;
            }
            if (line[j] == 'e' && line.substr(j, 5) == "eight") {
                right = 8;
                break;
            }
            if (line[j] == 'o' && line.substr(j, 3) == "one") {
                right = 1;
                break;
            }
            if (line[j] == 't' && line.substr(j, 5) == "three") {
                right = 3;
                break;
            }
            if (line[j] == 'f' && line.substr(j, 4) == "five") {
                right = 5;
                break;
            }
            if (line[j] == 's' && line.substr(j, 5) == "seven") {
                right = 7;
                break;
            }
            if (line[j] == 'n' && line.substr(j, 4) == "nine") {
                right = 9;
                break;
            }
        }

        sum += left*10 + right;
    }
    cout << sum << "\n";
    return 0;
}