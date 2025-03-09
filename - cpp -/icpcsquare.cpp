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
typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 2045B

//first, we can divide n and d by s, and fix s to start at 1. 

//for a given destination x, we're only really interested in the maximum jump required to arrive at that destination. 
//The maximum jump will always be the last jump, so to minimize the last jump, we should multiply by the minimum amount on
//the last jump. The minimum amount is always the lowest prime factor of x. 

//We can therefore test the highest even x that is a multiple of s that is valid, and if s is odd, test the next multiple of s
//after that. 

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

ll find_lpf(ll v) {
    ll lpf = v;
    for(ll p : pr) {
        while(v % p == 0) v /= p, lpf = min(lpf, p);
    }
    if(v != 1) lpf = min(lpf, v);
    return lpf;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, d, s;
    cin >> n >> d >> s;
    ll os = s;
    n /= s, d /= s, s = 1;
    ll ans = s;
    prime_sieve(1e6 + 100);
    {
        ll p = 2;
        ll low = 1, high = n, mult = -1;
        while(low <= high) {
            ll mid = low + (high - low) / 2;
            bool is_valid = true;
            lll tmp = (lll) s * (lll) mid;
            if(tmp * (p - 1) > d || tmp * p > n) is_valid = false;
            if(is_valid) {
                mult = mid;
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        if(mult != -1){
            ans = max(ans, s * mult * p);
        }
    }
    if(ans + s <= n) {
        ll lp = find_lpf(ans + s);
        ll inc = (ans + s) - (ans + s) / lp;
        if(inc <= d) ans += s;
    }
    cout << ans * os << "\n";
    
    return 0;
}