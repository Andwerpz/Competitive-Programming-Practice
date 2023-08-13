#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1811G1 / G2

//to solve the easy version, we can use 2d dp. 
//dp[i][j] = maximum number of ways to construct a path given that
//we only use the ith prefix of elements, and
//there are exactly j groups of k elements. 

//for each state, we need to transition n times, basically selecting another k elements from each state. 
//since there are n^2 states in total, this will run in O(n^3) time, which is enough for the easy version. 

//to solve the hard version, we can discard the j parameter of the dp, and only use the i parameter. 
//we can do this because we are only interested in the maximum amount of constructible groups for any prefix. 
//the transitions are the exact same, but since we have less states, it will run in O(n^2), which is enough 
//for the hard version.

ll mod = 1e9 + 7;
vector<ll> fac;
map<pair<ll, ll>, ll> nckdp;

ll add(ll a, ll b) {
    return (a + b) % mod;
}

ll sub(ll a, ll b) {
    ll ans = a - b;
    if(ans < 0){
        ans += mod;
    }
    return ans;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

ll power(ll a, ll b) {
    if(b == 0){
        return 1;
    }
    ll ans = power(a, b / 2);
    ans = mul(ans, ans);
    if(b % 2 == 1) {
        ans = mul(ans, a);
    }
    return ans;
}

ll divide(ll a, ll b){
    return mul(a, power(b, mod - 2));
}

void fac_init() {
    fac = vector<ll>(1e6, 1);
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    fac_init();
    int t;
    cin >> t;
    while(t--){
        ll n, k;
        cin >> n >> k;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> maxl(n + 1, 0);
        vector<ll> dp(n + 1, 1);
        for(int i = 0; i < n; i++){
            //make segment ending on element j - 1. 
            int nmxl = maxl[i] + 1;
            ll cnt = 0;
            for(int j = i + 1; j <= n; j++){
                if(a[j - 1] == a[i]) {
                    cnt ++;
                }
                if(cnt < k){
                    continue;
                }
                if(maxl[j] > nmxl) {
                    break;
                }
                ll mult = nck(cnt - 1, k - 1);
                if(maxl[j] == nmxl) {
                    dp[j] = add(dp[j], mul(dp[i], mult));
                }
                else {
                    dp[j] = mul(dp[i], mult);
                }
                maxl[j] = nmxl;
            }
        }
        cout << dp[n] << "\n";
    }
    
    return 0;
}
