#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//2023-2024 ICPC Asia Jakarta Regional H

ll mod = 998244353;
vector<ll> fac;
map<pair<ll, ll>, ll> nckdp;

ll add(ll a, ll b) {
    ll ret = a + b;
    while(ret >= mod) {
        ret -= mod;
    }
    return ret;
}

ll sub(ll a, ll b) {
    ll ans = a - b;
    while(ans < 0){
        ans += mod;
    }
    return ans;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

ll power(ll a, ll b) {
    ll ans = 1;
    ll p = a;
    while(b != 0){
        if(b % 2 == 1){
            ans = mul(ans, p);
        }
        p = mul(p, p);
        b /= 2;
    }
    return ans;
}

ll divide(ll a, ll b){
    return mul(a, power(b, mod - 2));
}

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

void fac_init() {
    fac = vector<ll>(2e6, 1);
    for(int i = 2; i < fac.size(); i++){
        fac[i] = mul(fac[i - 1], i);
    }
}

ll nck(ll n, ll k) {
    if(nckdp.find({n, k}) != nckdp.end()) {
        return nckdp.find({n, k}) -> second;
    }
    ll ans = divide(fac[n], mul(fac[k], fac[sub(n, k)]));
    nckdp.insert({{n, k}, ans});
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    fac_init();
    int n, m;
    cin >> n >> m;
    string a, b;
    cin >> a >> b;
    vector<ll> acnt(26, 0), bcnt(26, 0);
    for(int i = 0; i < n; i++){
        acnt[a[i] - 'A'] ++;
    }
    for(int i = 0; i < m; i++){
        bcnt[b[i] - 'A'] ++;
    }
    vector<vector<ll>> dp(26, vector<ll>(n + m, 0));
    if(bcnt['Z' - 'A'] < acnt['Z' - 'A']){
        cout << "0\n";
        return 0;
    }
    dp['Z' - 'A'][bcnt['Z' - 'A'] - acnt['Z' - 'A']] = 1;
    for(int i = 'Y' - 'A'; i >= 0; i--){
        //take suf sum of previous layer
        for(int j = dp[i + 1].size() - 2; j >= 0; j--){
            dp[i + 1][j] = add(dp[i + 1][j], dp[i + 1][j + 1]);
        }
        //compute current layer
        for(int j = 0; j <= min(acnt[i], bcnt[i]); j++){
            //we're using j of letter i
            if(j > acnt[i]) {
                //we're using too many
                break;
            }
            ll req_prev = acnt[i] - j;
            req_prev = max(0ll, req_prev);
            ll ways = dp[i + 1][req_prev];
            ll cur = divide(fac[acnt[i]], mul(fac[req_prev], fac[j]));
            ways = mul(ways, cur);
            ll remaining = bcnt[i] - j;
            dp[i][remaining] = ways;
        }
    }
    ll ans = 0;
    for(int i = 0; i < dp[0].size(); i++){
        ans = add(ans, dp[0][i]);
    }
    ll factor = fac[n];
    for(int i = 0; i < 26; i++){
        factor = divide(factor, fac[acnt[i]]);
    }
    ans = mul(ans, factor);
    cout << ans << "\n";
    
    return 0;
}
