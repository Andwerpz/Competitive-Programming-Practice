#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll mod = 998244353;
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i] >> b[i];
    }
    vector<pair<ll, ll>> dp(n, {0, 0});
    dp[0].first = 1;
    dp[0].second = 1;
    for(int i = 1; i < n; i++){
        //don't flip
        if(a[i] != a[i - 1]) {
            dp[i].first += dp[i - 1].first;
        }
        if(a[i] != b[i - 1]){
            dp[i].first += dp[i - 1].second;
        }
        //flip
        if(b[i] != a[i - 1]){
            dp[i].second += dp[i - 1].first;
        }
        if(b[i] != b[i - 1]){
            dp[i].second += dp[i - 1].second;
        }
        dp[i].first %= mod;
        dp[i].second %= mod;
    }
    cout << (dp[n - 1].first + dp[n - 1].second) % mod << "\n";
    
    return 0;
}
