
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 2413

//notice that since the width of the tower is always 2, for each row of the tower, there is two options: 
//1 wide piece
//2 short pieces

//for the wide piece, you can choose to extend it to the next layer, or not extend.
//if you don't extend, then you have two options: put another wide piece, put two short pieces. 

//for the short pieces, you can extend both, left, or right. If you don't extend, then you can put
//a wide piece, or two short pieces. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    ll mod = 1e9 + 7;
    cin >> t;
    //precompute answers
    vector<pair<ll, ll>> dp(1e6 + 1);   //first: LONG, second: SHORT
    dp[1].first = 1;
    dp[1].second = 1;
    for(int i = 2; i < dp.size(); i++){
        dp[i].first = dp[i - 1].first * 2ll + dp[i - 1].second;
        dp[i].second = dp[i - 1].first + dp[i - 1].second * 4ll;
        while(dp[i].first >= mod){
            dp[i].first -= mod;
        }
        while(dp[i].second >= mod){
            dp[i].second -= mod;
        }
    }
    while(t-- > 0){
        int n;
        cin >> n;
        ll ans = dp[n].first + dp[n].second;
        if(ans >= mod){
            ans -= mod;
        }
        cout << ans << endl;
    }
    
    return 0;
}
