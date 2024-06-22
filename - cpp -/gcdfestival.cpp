#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1575G

//intended solution uses euler totient function, but we came up with a jank sqrt decomposition solution. 

//denote g[x] = sum(gcd(a[i], a[j])) where gcd(i, j) is a multiple of x. For now, we don't care about how we find it. 
//then, _g[x] = sum(gcd(a[i], a[j])) where gcd(i, j) *equals* x. I claim that 
//_g[x] = g[x] - sum(_g[y]), where y is a multiple of x, y != x. 
//then, the answer to our problem is simply sum(_g[x] * x). 

//now, how to find g[x]? In order for gcd(i, j) to be a multiple of x, i and j must be multiples of x. 
//Now comes the jank part. For values of x greater than sqrt(n), we just use brute force to compute the values, more
//specifically, we just try all pairs i, j that are a multiple of x. For values x that are less than sqrt(x), we use
//an n * log(n) approach, that has a constant overhead of 10^5 (which is the range of the values). This leads to
//an overall complexity of (i think) n * log(n) * sqrt(n). 

//for constant factor optimization, note that you don't have to mod any of the intermediate results, as the answer is
//bounded by 10^16. 

ll mod = 1e9 + 7;
vector<ll> f(1e5 + 1, 0), g(1e5 + 1, 0);

ll gcd_sum_fast(vector<ll>& a, ll inc) {
    ll ans = 0;
    for(int i = inc; i <= a.size(); i += inc){
        f[a[i - 1]] ++;
    }
    for(int i = g.size() - 1; i > 0; i--){
        g[i] = 0;
        for(int j = i; j < f.size(); j += i) {
            g[i] += f[j];
        }
        g[i] *= g[i];
        for(int j = i * 2; j < f.size(); j += i){
            g[i] -= g[j];
        }
        ans += g[i] * i;
    }
    for(int i = inc; i <= a.size(); i += inc){
        f[a[i - 1]] --;
    }
    return ans;
}

ll gcd_sum_slow(vector<ll> &a, ll i) {
    int n = a.size();
    ll res = 0;
    for(ll j = i; j <= n; j += i) {
        for(ll k = i; k <= n; k += i) {
            res += gcd(a[j - 1], a[k - 1]);
        }
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<ll> d(1e5 + 1, 0);
    ll ans = 0;
    for(int i = d.size() - 1; i > 0; i--){
        if(i > n) {
            continue;
        }
        if(i > sqrt(n)) {
            d[i] = gcd_sum_slow(a, i);
        }
        else {
            d[i] = gcd_sum_fast(a, i);
        }
        for(int j = i * 2; j < d.size(); j += i){
            d[i] -= d[j];
        }
        ans += d[i] * i;
    }
    ans %= mod;
    cout << ans << "\n";
    
    return 0;
}