#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSES - 1653

//dp[i][j] = minimum currently in the elevator where
//i = number of elevators sent previously
//j = bitset of people sent.

//at each state, you can either add any person that hasn't been sent to the current elevator, or
//just send the elevator. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    ll x;
    cin >> x;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    ll unv = 1e18;
    vector<vector<ll>> dp(2, vector<ll>((1 << n), unv));
    dp[0][0] = 0;
    int ans = -1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < (1 << n); j++){
            if(dp[0][j] == unv) {
                continue;
            }
            //take the elevator up
            dp[1][j] = min(dp[1][j], 0ll);
            //try to put people in the elevator
            for(int k = 0; k < n; k++){
                if(dp[0][j] + a[k] > x) {
                    break;
                }
                if(j & (1 << k)){
                    continue;
                }
                dp[0][j | (1 << k)] = min(dp[0][j | (1 << k)], dp[0][j] + a[k]);
            }
        }
        if(dp[0][(1 << n) - 1] != unv) {
            ans = i + 1;
            break;
        }
        fill(dp[0].begin(), dp[0].end(), unv);
        swap(dp[0], dp[1]);
    }
    cout << ans << "\n";
    
    return 0;
}
