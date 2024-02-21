#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//UTPC Contest 02-09-24 Div. 2 - F

//we can use 2D dp to solve this problem:
//dp[i][j] = nr ways to make given
//i = number of pizzas we've stacked so far
//j = how many proper pairs we're guaranteed to get so far. 

//to explain the notion of guaranteed pairs, i'll use an example: Let's say that you have 4 pizzas. Since
//the radii of all 4 pizzas are unique, let's just say they have radii of {1, 2, 3, 4}. Then, if we place
//the pizza with radii 3 on the bottom, we'll have guaranteed 2 proper pairs, because no matter what, the 
//pizzas with radii 1 and 2 must go on top. 

//to generalize, if we have A pizzas left to place, then we can gurantee from 0 to A - 1 more proper pairs.

//so for transitions, if we have i pizzas stacked, then we have n - i pizzas left to place, thus we can
//transition from dp[i][j] to dp[i + 1][j + k] where k is in the range [0, n - i - 1]. 

//the issue now is that our solution runs in O(n^3) time, so to fix this, we can instead try to compute
//dp[i][j] directly. Notice that dp[i][j] only depends on some contiguous segment of the array dp[i - 1], 
//so we can use sliding window to compute dp[i][j] in O(1) time, which allows our solution to be O(n^2). 

ll mod = 1e9 + 7;
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

//true if odd, false if even. 
bool nck_parity(ll n, ll k) {   
    return (n & (n - k)) == 0;
}

ll catalan(ll n){
    return sub(nck(2 * n, n), nck(2 * n, n + 1));
}

//cantor pairing function, uniquely maps a pair of integers back to the set of integers. 
ll cantor(ll a, ll b, ll m) {
    return ((a + b) * (a + b + 1) / 2 + b) % m;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    //i : nr pizzas we've stacked so far
    //j : how many proper pairs we have so far
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++){
        ll p_sum = 0;
        for(int j = 0; j <= k; j++){
            p_sum = add(p_sum, dp[i - 1][j]);
            if(j - (n - i) - 1 >= 0){
                p_sum = sub(p_sum, dp[i - 1][j - (n - i) - 1]);
            }
            dp[i][j] = p_sum;
        }
    }
    cout << dp[n][k] << "\n";
    
    return 0;
}
