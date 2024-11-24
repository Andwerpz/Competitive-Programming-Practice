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

//AtCoder - ABC370

//nice dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, k;
    cin >> n >> k;
    vl a(n);
    for(ll &x : a) cin >> x;
    const ll mod = 998244353;
    ll psum = a[0];
    ll pcnt = 1;
    map<ll, ll> m;
    m[0] = 1;
    for(int i = 1; i < n; i++){
        //end subarray here
        ll npcnt = (pcnt + (pcnt - m[psum - k]) + mod) % mod;
        m[psum] += pcnt - m[psum - k] + mod;
        m[psum] %= mod;
        pcnt = npcnt;
        psum += a[i];
        // cout << "SUM : " << psum << " " << m[psum] << " " << pcnt << "\n";
    }
    cout << (pcnt - m[psum - k] + mod) % mod << "\n";
    
    return 0;
}