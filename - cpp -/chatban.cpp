
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1612C

//binary search through the amount of messages sent.

//given an set amount of messages, it is possible to calculate the amount of emotes in O(1) time. With that, it is also 
//possible to calculate whether or not you'll be banned for a given amount of messages. 

bool isValid(ll val, ll x, ll k){
    ll sum = 0;
    if(val <= k){
        sum = (val * (val + 1)) / 2;
        sum -= val;
    }
    else{
        sum = (k * (k + 1)) / 2;
        val -= k;
        sum += (k * val) - (val * (val + 1)) / 2;
        sum -= k - val;
    }
    if(sum <= x){
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll k, x;
        cin >> k >> x;
        x --;
        ll high = k * 2 - 1;
        ll low = 0;
        ll mid = low + (high - low) / 2;
        ll ans = 0;
        while(low <= high){
            if(isValid(mid, x, k)){
                ans = max(ans, mid);
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
            mid = low + (high - low) / 2;
        }
        cout << ans << endl;
    }
    
    return 0;
}
