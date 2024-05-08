#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 10 G

//huh

//dp[i][j] = max number of determinable floors given
//i = nr eggs we have
//j = nr drops we're allowed

//dp[1][1] = 1
//dp[2][1] = 1
//dp[x][1] = 1, x >= 1
//dp[1][2] = 2
//dp[2][2] = 3

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<vector<ll>> dp(33, vector<ll>(33, 0));   //eggs, drops allowed
    for(int i = 1; i < 33; i++){
        for(int j = 1; j < 33; j++){
            dp[i][j] = 1 + dp[i - 1][j - 1] + dp[i][j - 1];
        }
    }
    int t;
    cin >> t;
    while(t-- > 0){
        ll n, k;
        cin >> n >> k;
        bool found = false;
        ll ans = 1e18;
        for(int i = 0; i < 33; i++){
            for(int j = 0; j < 33; j++){
                if(i > k) {
                    continue;
                }
                if(dp[i][j] < n){
                    continue;
                }
                found = true;
                ans = min(ans, (ll) j);
            }
        }
        if(found){
            cout << ans << "\n";
        }
        else {
            cout << "Impossible\n";
        }
    }
    
    return 0;
}
