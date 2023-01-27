#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problem Set #1 (Spring 2023) B

//since s is small, we can do a O(s^2) solution. 
//basically the coins problem, but with s coins. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    ll mod = 1e9 + 7;
    for(int i = 0; i < n; i++){
        for(int j = 3; j <= n; j++){
            int next = i + j;
            if(next > n) {
                continue;
            }
            dp[next] += dp[i];
            dp[next] %= mod;
        }
    }
    cout << dp[n] << "\n";
    
    return 0;
}
