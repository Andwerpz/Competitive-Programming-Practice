
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//CSES - Increasing Array

int main()
{
    
    int n;
    cin >> n;
    vector<long long> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    long long ans = 0;
    long long max = 0;
    for(int i = 0; i < n; i++){
        max = std::max(max, nums[i]);
        ans += std::abs(max - nums[i]);
    }
    cout << ans;

    return 0;
}



