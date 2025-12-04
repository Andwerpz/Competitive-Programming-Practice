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

//CodeSprint LA 2025 Open - C

//at first, it seems like it's only possible if m is even, but then you realize that if n = 6 and
//m = 3, then it's also possible. 

//then, you theorize that if n % m = 0, it's also possible, but get WA. Thinking, you realize that n = 12 and
//m = 5 is also possible (1 group of 3, 1 group of 2). 

//then, you theorize that if m is odd, you just need to find the lowest odd prime factor of n, subtract that
//out of m, and see if there are enough remaining seats. This gets AC

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, m;
    cin >> n >> m;
    bool ans = false;
    if(m % 2 == 0) ans = true;
    if(m != 1 && n % m == 0) ans = true;
    if(m % 2 == 1) {
        //find lowest odd prime factor of n
        prime_sieve(1e5);
        vl p = find_prime_factors(n);
        ll pf = (ll) (2e9) + 100;
        for(int i = 0; i < p.size(); i++) if(p[i] % 2 == 1) pf = min(pf, p[i]);
        // cout << "PF : " << pf << "\n";
        if(pf != (ll) (2e9) + 100 && m >= pf) {
            ll rem_n = n - pf * 2;
            ll rem_m = m - pf;
            if(rem_n >= rem_m) ans = true;
        }
    }
    cout << (ans ? "Yes" : "No") << "\n";
    
    return 0;
}