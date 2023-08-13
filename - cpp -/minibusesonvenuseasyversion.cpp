#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1808E1

//instead of counting lucky numbers, we can count the number of numbers that are not lucky, or 'unlucky' numbers,
//and then subtract that from the total amount of numbers, k^n, to get the amount of lucky numbers. 

//let's represent a number using an array of n digits, 'a'. a[i] denotes the ith digit. 
//in order for a to be lucky, it must be the case that there exists an i where
//a[i] = (a[0] + a[1] + ... + a[n] - a[i]) % k

//if we rearrange this, then it says
//(2 * a[i]) % k = (a[0] + a[1] + ... + a[n]) % k

//if we fix the target digit sum to some number 's', then we can count the number of unlucky numbers with digit sum s
//by seeing how many numbers sum to s, but don't include digits 'd' where (2 * d) % k = s. 
//this subproblem can be solved using a 2d dp approach. 

//now, we just have to solve the number of unlucky numbers for all s from 0 - k, and subtract them all from k^n.

//this algorithm runs in O(n * k^3) time. 
//in order to solve the medium version, we need to get rid of the n factor somehow. 

ll mod;
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

//how many numbers of length n have digit sums equal to s, and don't contain digits in blist
ll solve(ll n, ll base, int s, set<int>& blist) {
    //dp[i][j] = amount of numbers
    //i : length
    //j : digit sum mod base
    vector<vector<ll>> dp(n + 1, vector<ll>(base, 0));
    dp[0][0] = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < base; j++){
            for(int k = 0; k < base; k++){
                if(blist.find(k) != blist.end()){
                    continue;
                }
                int nsum = (j + k) % base;
                dp[i + 1][nsum] = add(dp[i + 1][nsum], dp[i][j]);
            }
        }
    }
    // cout << "SOLVE : " << n << " " << base << " " << s << "\n";
    // cout << "BLACKLIST : ";
    // for(auto i = blist.begin(); i != blist.end(); i++){
    //     cout << *i << " ";
    // }
    // cout << "\n";
    // cout << "ANS : " << dp[n][s] << "\n";
    return dp[n][s];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k;
    cin >> n >> k >> mod;
    ll ans = power(k, n);
    //cout << "K^N : " << ans << "\n";
    map<int, set<int>> m;
    for(int i = 0; i < k; i++){
        m.insert({i, set<int>()});
    }
    for(int i = 0; i < k; i++){
        int sum = (i * 2) % k;
        m.find(sum) -> second.insert(i);
    }
    for(int i = 0; i < k; i++){
        int sum = i;
        set<int> blist = m.find(i) -> second;
        ans = sub(ans, solve(n, k, sum, blist));
    }
    cout << ans << "\n";
    
    return 0;
}
