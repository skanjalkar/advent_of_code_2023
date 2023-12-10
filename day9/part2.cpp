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

long long predictNext(vector<long long> nums) {
    long long tempSum = 0;
    vector<long long> ans;
    while (1) {
        bool found = false;
        ans.push_back(nums[0]);
        vector<long long> temp;
        for (int i = 0; i < nums.size() - 1; i++) {
            temp.push_back(nums[i+1] - nums[i]);
        }
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] != 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            reverse(ans.begin(), ans.end());
            for (int i = 0; i < ans.size(); i++) {
                tempSum = (ans[i]-tempSum);
            }
            return tempSum;
        }
        nums = temp;
    }
}

// a - b
// c - (a - b)
// d - (c - (a - b))

int main() {
    string sequence;
    long long sum = 0;
    while (getline(cin, sequence)) {
        vector<long long> nums;
        istringstream iss(sequence);
        long long num;
        while (iss >> num) {
            nums.push_back(num);
        }

        sum += predictNext(nums);
    }
    cout << sum << "\n";
    return 0;
}