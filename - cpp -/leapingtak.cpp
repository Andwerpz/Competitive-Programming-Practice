#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    ll mod = 998244353;
    vector<ll> dp(n + 1, 0);
    vector<pair<int, int>> s(k, pair<int, int>(0, 0));
    for(int i = 0; i < k; i++){
        cin >> s[i].first >> s[i].second;
    }
    dp[0] = 1;
    dp[1] = -1;
    ll sum = 0;
    for(int i = 0; i < n; i++){
        sum += dp[i];
        sum %= mod;
        //cout << sum << " " << dp[i] << endl;
        for(int j = 0; j < k; j++){
            int l = i + s[j].first;
            int r = i + s[j].second + 1;
            if(l <= n) {
                dp[l] += sum;
                dp[l] %= mod;
            }
            if(r <= n){
                dp[r] -= sum;
                if(dp[r] < 0){
                    dp[r] += mod;
                }
            }
        }
    }
    cout << sum << "\n";
    
    return 0;
}
