
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codechef - CHRL3

//the solution involves reversing the array, then finding the longest increasing subsequence of the reversed array. 

//I'll need more time to think about this one.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    reverse(nums.begin(), nums.end());
    vector<int> dp;
    dp.push_back(nums[0]);
    for(int i = 1; i < nums.size(); i++){
        //cout << nums[i] << " ";
        int next = nums[i];
        if(next > dp.back()){
            dp.push_back(next);
        }
        else {
            int index = std::lower_bound(dp.begin(), dp.end(), next) - dp.begin();
            dp[index] = next;
        }
        // for(int j = 0; j < dp.size(); j++){
        //     cout << dp[j] << " ";
        // }
        // cout << endl;
    }
    cout << dp.size() << endl;

    return 0;
}



