
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, n;
    cin >> k >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    int ans = 0;
    while(true){
        sort(nums.begin(), nums.end());
        for(int i = n - 1; i >= n - k; i--){
            if(nums[i] == 0){
                goto outer;
            }
            nums[i] --;
        }
        ans ++;
    }
    outer: ;
    cout << ans << endl;
    
    return 0;
}
