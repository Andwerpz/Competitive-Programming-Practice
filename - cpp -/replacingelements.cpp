
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1473A

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n, d;
        cin >> n >> d;
        vector<int> nums(n);
        for(int i = 0; i < n; i++){
            cin >> nums[i];
        }
        sort(nums.begin(), nums.end());
        int max = nums[n - 1];
        int minCombo = nums[0] + nums[1];
        if(max <= d || minCombo <= d){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }

    return 0;
}



