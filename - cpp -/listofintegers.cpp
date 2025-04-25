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

//Codeforces - 920G

//the sequence L(x, p) consists of all the numbers that are coprime to p and greater than x. If we can figure
//out a way to count for some p, the number of elements in range [1, r) that are coprime to p, then we can
//binary search for the kth element of L(x, p). 

//to find the number of elements in range [1, r) that are coprime to p, we can use inclusion exclusion. A number
//can be bad if it shares any prime factor of p. To find the amount of elements that share some prime factors
//of p, just floor divide (r - 1) by the prime factors multiplied together. Since p <= 10^6, the maximum amount
//of unique prime factors is 7. 

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

vector<ll> find_prime_factors(ll val) {
    set<ll> factors;
    while(val != 1) {
        factors.insert(lp[val]);
        val /= lp[val];
    }
    vl ans(0);
    for(auto i = factors.begin(); i != factors.end(); i++) ans.push_back(*i);
    return ans;
}

//computes the number of elements coprime to p in range [1, r)
ll calc(ll r, ll p) {
    vl f = find_prime_factors(p);
    ll ans = 0;
    for(int i = 0; i < (1 << f.size()); i++){
        ll mult = 1, cnt = 0;
        for(int j = 0; j < f.size(); j++) if(i & (1 << j)) mult *= f[j], cnt ++;
        ans += ((r - 1) / mult) * (cnt % 2 == 1? -1 : 1);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(1e6 + 100);
    int t;
    cin >> t;
    while(t--){
        ll x, p, k;
        cin >> x >> p >> k;
        ll base = calc(x + 1, p);
        //find the smallest x such that calc(x, p) - base >= k
        ll low = x + 2, high = 1e15;
        ll ans = high;
        while(low <= high) {
            ll mid = low + (high - low) / 2;
            if(calc(mid, p) - base >= k) ans = mid, high = mid - 1;
            else low = mid + 1;
        }
        // for(int i = 1; i < 30; i++) {
        //     cout << calc(i, p) << " ";
        // }
        // cout << "\n";
        // cout << "VAL : " << calc(ans, p) - base << "\n";
        // cout << "BASE : " << base << endl;
        cout << ans - 1 << "\n";
    }
    
    return 0;
}