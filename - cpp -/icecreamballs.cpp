#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1862D

//if we have x different types of ice cream balls, then we can make at most x * (x - 1) types of 2 ball ice cream cones. 
//note that we can then start adding duplicates of the types of balls that we already have, each unique duplicate adds 1 to our maximum
//amount of cones that we can create. 

//we just need to binary search for the maximum x where x * (x - 1) <= n, and then the remainder will be the amount of duplicates that we 
//need to add. 

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

ll find_base(ll n) {
    ll ans = 2;
    ll low = 2;
    ll high = 2 * 1e9;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        if(mid * (mid - 1) / 2 <= n) {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        ll base = find_base(n);
        ll ans = base + (n - (base * (base - 1) / 2));
        cout << ans << "\n";
    }
    
    return 0;
}
