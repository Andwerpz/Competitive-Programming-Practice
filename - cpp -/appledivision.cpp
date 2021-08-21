
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long ll;

using namespace std;

int main() {

    int n;
    cin >> n;
    vector<ll> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    ll sum, pointer, target;
    sum = 0;
    for(int i = 0; i < n; i++){
        sum += nums[i];
        //cout << sum << " ";
    }
    target = sum / 2;
    //cout << sum << endl;
    for(int i = n - 1; i >= 0; i--){
        if(nums[i] + pointer <= target){
            pointer += nums[i];
        }
    }
    cout << abs((pointer) - (sum - pointer)) << "\n";
    return 0;
}



