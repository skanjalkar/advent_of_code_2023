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
    string time;
    string distance;

    getline(cin, time);
    getline(cin, distance);

    time = time.substr(5);
    distance = distance.substr(9);

    time.erase(remove_if(time.begin(), time.end(), ::isspace), time.end());
    distance.erase(remove_if(distance.begin(), distance.end(), ::isspace), distance.end());

    long long iTime = stoll(time);
    long long iDistance = stoll(distance);

    long long low = 1;
    long long high = iTime;
    long long temp;
    while (low <= high) {
        long long mid = (low + high) / 2;
        long long currDistance = mid * (iTime - mid);

        if (currDistance > iDistance) {
            temp = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    long long low2 = 1;
    long long high2 = iTime;
    long long temp2;
    while (low2 <= high2) {
        long long mid = (low2 + high2) / 2;
        long long currDistance = mid * (iTime - mid);

        if (currDistance > iDistance) {
            temp2 = mid;
            low2 = mid + 1;
        }
        else {
            high2 = mid - 1;
        }
    }
    // idist - (idist - temp2) - temp1
    //
    cout << temp2 - temp + 1 << endl;

    return 0;
}