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

//Alberta Collegiate Programming Contest 2024, Open Division - K

//when we query s, we get back s^2 % p = r, so we can compute the largest multiple of p \leq s^2 as 
//x = s^2 - r. 

//since we know x is a multiple of p, and that p is prime, then p must be a prime factor of x. 
//if we take our first s to be 10^5, then regardless of the selection of p, x will have at most 7 unique prime
//factors. (can check this using brute force)

//we can use our remaining 3 queries to continually halve the number of prime factors remaining. 

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
set<ll> find_prime_factors(ll val) {
    set<ll> factors;
    for(int i = 0; i < pr.size(); i++){
        while(val % pr[i] == 0){
            factors.insert(pr[i]);
            val /= pr[i];
        }
    }
    if(val != 1){
        factors.insert(val);
    }
    return factors;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(1e6);
    cout << "q " << 100000 << endl;
    ll r;
    cin >> r;
    set<ll> f = find_prime_factors(100000ll * 100000ll - r);
    int qrem = 3;
    for(int i = 0; i < 3 && f.size() != 1; i++) {
        ll s = 1;
        int cnt = 0;
        set<ll> tf;
        for(auto j = f.begin(); j != f.end(); j++){
            if(cnt >= (f.size() + 1) / 2){
                break;
            }
            if(s * (*j) > 100000) {
                break;
            }
            cnt ++;
            tf.insert(*j);
            s *= *j;
        }
        cout << "q " << s << endl;
        cin >> r;
        if(r == 0){
            f = tf;
        }
        else {
            for(auto j = tf.begin(); j != tf.end(); j++){
                f.erase(*j);
            }
        }
    }
    cout << "a " << *f.begin() << endl;

    // for(int i = 0; i < pr.size(); i++){
    //     ll x = s * s - ((s * s) % pr[i]);
    //     set<ll> f = find_prime_factors(x);
    //     ret = max(ret, (ll) f.size());
    //     cout << "RET : " << pr[i] << " " << f.size() << endl;
    // }
    // cout << "MAX PF : " << ret << "\n";
    
    return 0;
}