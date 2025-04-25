#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
typedef vector<ll> vl;

//2022 ICPC NAC - E

//huh, didn't think i'd be able to raise MAXV up to 10^4, but here we are. Time complexity of this is around
//O(N * MAXV * log(log(MAXV))). The key observation is that the answer to f[v][i] is only really dependent on the answers
//to f[x][p], where p is a prime factor of i. This allows us to turn the MAXV / log(MAXV) factor into log(log(MAXV))

vector<ll> lp; //lowest prime factor 
vector<ll> pr; //prime list
vector<bool> ispr;

void prime_sieve(ll n) {
    lp = vector<ll>(n + 1);
    pr = vector<ll>(0);
    ispr = vector<bool>(n + 1, false);
    for(ll i = 2; i <= n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
            ispr[i] = true;
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
// vector<ll> find_prime_factors(ll val) {
//     vector<ll> factors(0);
//     for(int i = 0; i < pr.size(); i++){
//         while(val % pr[i] == 0){
//             factors.push_back(pr[i]);
//             val /= pr[i];
//         }
//     }
//     if(val != 1){
//         factors.push_back(val);
//     }
//     return factors;
// }

vector<ll> find_prime_factors(ll val) {
    vector<ll> factors(0);
    while(val != 1) {
        factors.push_back(lp[val]);
        val /= lp[val];
    }
    return factors;
}

vector<int> find_upf(ll val){
    vl f = find_prime_factors(val);
    set<ll> s;
    for(ll x : f) s.insert(x);
    vector<int> ans;
    for(ll x : s) ans.push_back(x);
    return ans;
}

// //gets rid of duplicate prime factors
// ll reduce(ll val) {
//     vl f = find_prime_factors(val);
//     set<ll> s;
//     for(ll x : f) s.insert(x);
//     ll ans = 1;
//     for(ll x : s) ans *= x;
//     return ans;   
// }

const int MAXV = 10000, N = 5000;
int f[N][MAXV + 1], a[N];
vector<int> c[N], cv[MAXV + 1];
vector<int> upf[MAXV + 1];
void dfs(int v, int p, int val) {
    if(f[v][val] != -1) return;
    int ans = 0;
    if(val != a[v]) ans += val;
    for(int x : c[v]) {
        if(x == p) continue;
        int mn_nxt = 1e9;
        for(int nval : cv[val]) {
            if(f[x][nval] == -1) dfs(x, v, nval);
            mn_nxt = min(mn_nxt, f[x][nval]);
        }
        ans += mn_nxt;
        ans = min(ans, (int) 1e9);
    }
    f[v][val] = ans;
}

void dfs2(int v, int p) {
    for(int x : c[v]) if(x != p) dfs2(x, v);
    //try all values for this node. 
    //if gcd = g = p_1 * p_2 * ... * p_n, then the ans for g (without operation) 
    //is simply the min among ans for p_1, p_2, ..., p_n
    for(int i = 2; i <= MAXV; i++){
        f[v][i] = 0;
        for(int x : c[v]) {
            if(x == p) continue;
            int cur = 1e9;
            for(int fac : upf[i]) cur = min(cur, f[x][fac]);
            f[v][i] += cur;
        }
        if(i != a[v]) f[v][i] += i;
    }
    //do some preprocessing
    for(int i = 2; i <= MAXV; i++){
        if(!ispr[i]) continue;
        for(int j = i * 2; j <= MAXV; j += i) f[v][i] = min(f[v][i], f[v][j]);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    prime_sieve(1e5);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j <= MAXV; j++){
            f[i][j] = -1;
        }
    }
    for(int i = 2; i <= MAXV; i++) upf[i] = find_upf(i);
    int n; cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n - 1; ++i) {
        ll a, b; cin >> a >> b;
        a --, b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    // for (int i = 1; i <= MAXV; ++i) {
    //     for(int j = 1; j <= MAXV; j++) {
    //         if(gcd(i, j) != 1) cv[i].push_back(j);
    //     }
    // }
    // for(int i = 2; i <= MAXV; i++){
    //     dfs(0, -1, i);
    // }
    dfs2(0, -1);
    int ans = 1e9;
    for(int i = 2; i <= MAXV; i++) ans = min(ans, f[0][i]);
    cout << ans << "\n";
    
    return 0;
}