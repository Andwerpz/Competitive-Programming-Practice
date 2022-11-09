#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Kattis anti11

//simple dp problem. 

//for each i from 1 to n, how many bitstrings of length i can be made with 1 as the final digit with no '11' subarray?

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll mod = 1e9 + 7;
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> dp(n + 1);
        ll sum = 1;
        for(int i = 1; i <= n; i++){
            dp[i] = sum - dp[i - 1];
            if(dp[i] < 0){
                dp[i] += mod;
            }
            dp[i] %= mod;
            sum += dp[i];
            sum %= mod;
        }
        cout << sum << "\n";
    }
    
    return 0;
}
