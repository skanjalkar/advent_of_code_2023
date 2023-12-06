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

    vector<int> timeVec;
    vector<int> distanceVec;

    istringstream ss(time);

    int token;
    while (ss >> token) {
        timeVec.push_back(token);
    }

    istringstream ss2(distance);
    while (ss2 >> token) {
        distanceVec.push_back(token);
    }

    vector<int> numWays;

    for (int i = 0; i < timeVec.size(); i++) {
        int count = 0;
        for (int j = 1; j <= timeVec[i]; j++) {
            int currDistance = j * (timeVec[i]-j);
            if (currDistance > distanceVec[i]) {
                count++;
            }
        }
        numWays.push_back(count);
    }
    long long ans = 1;
    for (int & num : numWays) {
        ans *= num;
    }
    cout << ans << endl;
    return 0;
}