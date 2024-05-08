#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1934B

//i made a guess. I assume that the majority of the coins are going to be 15 value, so i brute forced the answer
//for all n <= 10^6, then if n is greater than 10^6, i just 15 value coins until it's below. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> dp(1e6, 1e9);
    dp[0] = 0;
    vector<int> m = {1, 3, 6, 10, 15};
    for(int i = 1; i < dp.size(); i++){
        for(int j = 0; j < m.size(); j++){
            if(i - m[j] >= 0){
                dp[i] = min(dp[i], dp[i - m[j]] + 1);
            }
        }
    }
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int ans = 0;
        //just use 15s
        if(n >= dp.size()) {
            int diff = n - (int) dp.size() + 15;
            int mult = diff / 15;
            ans += mult;
            n -= mult * 15;
        }
        ans += dp[n];
        cout << ans << "\n";
    }
    
    return 0;
}
