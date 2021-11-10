
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1476A

//just binary search the answer.

//to check whether something is valid in O(1), you just need to determine the upper and lower bound of what you can make. 
//since you can make everything within those bounds, if a valid number occurs within those bounds, the input is valid.

using namespace std;

bool isValid(ll k, ll n, ll val){
    ll min = n - 1;
    ll max = (ll)(n - 1) * val;
    ll low = (max / (ll) k) * (ll) k;
    low -= val;
    ll high = low + k;
    if(low >= min && low <= max){
        return true;
    }
    if(high >= min && high <= max){
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
        ll n, k;
        cin >> n >> k;
        ll high = k;
        ll low = 1;
        ll mid = low + (high - low) / 2;
        ll ans = high;
        while(low <= high){
            if(isValid(k, n, mid)){
                ans = min(ans, mid);
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
            mid = low + (high - low) / 2;
        }
        cout << ans << endl;
    }

    return 0;
}



