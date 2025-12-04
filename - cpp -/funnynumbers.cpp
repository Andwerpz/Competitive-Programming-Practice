#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//UTPC 11-12-2025 Div1 - F

//this is just bitmask dp. 

vector<ll> lp; //lowest prime factor 
vector<ll> pr; //prime list

void prime_sieve(ll n) {
    lp = vector<ll>(n + 1);
    pr = vector<ll>(0);
    for(ll i = 2; i <= n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

// - slow version, use when big number 
vector<ll> find_prime_factors(ll val) {
    vector<ll> factors(0);
    for(int i = 0; i < pr.size(); i++){
        while(val % pr[i] == 0){
            factors.push_back(pr[i]);
            val /= pr[i];
        }
    }
    if(val != 1){
        factors.push_back(val);
    }
    return factors;
}

void find_divisors_helper(vector<ll>& p, vector<ll>& c, ll ind, ll val, vector<ll>& ans) {
    if(ind == p.size()) {
        ans.push_back(val);
        return;
    }
    find_divisors_helper(p, c, ind + 1, val, ans);
    for(ll i = 0; i < c[ind]; i++){
        val *= p[ind];
        find_divisors_helper(p, c, ind + 1, val, ans);
    }
}

//includes 1 as a divisor
vector<ll> find_divisors(ll val) {
    vector<ll> factors = find_prime_factors(val);
    map<ll, ll> m;
    vector<ll> p(0);
    vector<ll> c(0);
    for(ll i = 0; i < factors.size(); i++){
        ll next = factors[i];
        if(m.find(next) == m.end()) {
            p.push_back(next);
            c.push_back(0);
            m.insert({next, m.size()});
        }
        ll ind = m[next];
        c[ind] ++;
    }
    vector<ll> div(0);
    find_divisors_helper(p, c, 0, 1, div);
    return div;
}

set<ll> find_divisors_set(ll val) {
    vl v = find_divisors(val);
    set<ll> s;
    for(ll d : v) s.insert(d);
    return s;
}

set<ll> un(set<ll>& a, set<ll>& b) {
    set<ll> ret;
    for(ll x : a) if(b.count(x)) ret.insert(x);
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(1e6);
    int n;
    cin >> n;
    vl x(n), y(n);
    for(int i = 0; i < n; i++) cin >> x[i];
    for(int i = 0; i < n; i++) cin >> y[i];
    vector<set<ll>> div(n);
    for(int i = 0; i < n; i++) div[i] = find_divisors_set(y[i]);
    vvi mat(n, vi(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            mat[i][j] = un(div[i], div[j]).size();
            // cout << "MAT : " << mat[i][j] << " " << y[i] << " " << y[j] << "\n";
        }
    }
    vvi dp((1 << n), vi(n, -1e9));
    for(int i = 0; i < n; i++) {
        dp[(1 << i)][i] = 0;
    }
    for(int i = 1; i < (1 << n); i++) {
        for(int j = 0; j < n; j++) {
            if(!(i & (1 << j))) continue;
            if(dp[i][j] < 0) continue;
            for(int k = 0; k < n; k++) {
                if(i & (1 << k)) continue;
                dp[i ^ (1 << k)][k] = max(dp[i ^ (1 << k)][k], dp[i][j] + mat[j][k]);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++) ans = max(ans, dp[(1 << n) - 1][i]);
    cout << ans << "\n";
    
    return 0;
}

