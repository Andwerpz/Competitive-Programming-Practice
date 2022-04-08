
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1085

//we can bin search across all possible maximum subarray values. If we know that we can make a partition with
//maximum value x, then we know that we can make a partition with maximum value y, where y > x. 

//to test whether a maximum value partition x will work, just iterate along the array, keeping track of a sum
//value. If the sum ever goes above x, then reset it; that was one partition. If the number of partitions is 
//less or equal to k, then x is valid.

bool isValid(vector<ll> nums, ll val, int k){
    int cnt = 1;
    ll sum = 0;
    for(int i = 0; i < nums.size(); i++){
        if(nums[i] > val){
            return false;
        }
        if(sum + nums[i] > val){
            sum = 0;
            cnt ++;
        }
        sum += nums[i];
    }
    return cnt <= k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<ll> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    ll low = 0;
    ll high = 1e18;
    ll mid = low + (high - low) / 2;
    ll ans = high;
    while(low <= high){
        if(isValid(nums, mid, k)){
            ans = min(ans, mid);
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
        mid = low + (high - low) / 2;
    }
    cout << ans << endl;
    
    return 0;
}
