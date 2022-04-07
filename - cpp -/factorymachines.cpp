
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1620

//bin search through possible times

bool isValid(vector<ll> nums, ll time, ll target);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, t;
    cin >> n >> t;
    vector<ll> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    ll low = 0;
    ll high = 1e18;
    ll mid = low + (high - low) / 2;
    ll ans = high;
    while(low <= high){
        if(isValid(nums, mid, t)){
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

bool isValid(vector<ll> nums, ll time, ll target) {
    ll sum = 0;
    for(int i = 0; i < nums.size(); i++){
        sum += time / nums[i];
        if(sum > target){
            return true;
        }
    }
    return sum >= target;
}
