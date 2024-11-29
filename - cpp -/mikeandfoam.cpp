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

//Codeforces - 547C

//just take mobius inversion, and answer will be obvious. 

vector<ll> mobius;
void calc_mobius(int n) {
    mobius = vector<ll>(n + 1, 0);
    mobius[1] = 1;
    vector<bool> c(n + 1, false);
    vector<ll> p(0);
    for(int i = 2; i <= n; i++){
        if(!c[i]) {
            p.push_back(i);
            mobius[i] = -1;
        }
        for(int j = 0; j < p.size() && i * p[j] <= n; j++){
            c[i * p[j]] = true;
            if(i % p[j] == 0){
                mobius[i * p[j]] = 0;
                break;
            }
            else {
                mobius[i * p[j]] = mobius[i] * mobius[p[j]];
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    calc_mobius(1e6);
    vvi d(1e6); //divisors
    for(int i = 1; i < d.size(); i++){
        for(int j = i; j < d.size(); j += i){
            d[j].push_back(i);
        }
    }
    int n, q;
    cin >> n >> q;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vb in(n, false);
    vl cnt(1e6, 0);
    ll cnt_a = 0, cnt_b = 0;
    for(int i = 0; i < q; i++){
        int x;
        cin >> x;
        x --;
        int val = a[x];
        cnt_a -= in[x] && val == 1;
        for(int j = 0; j < d[val].size(); j++){
            int div = d[val][j];
            cnt_b -= cnt[div] * cnt[div] * mobius[div];
            cnt[div] -= in[x];
        }
        in[x] = !in[x];
        cnt_a += in[x] && val == 1;
        for(int j = 0; j < d[val].size(); j++){
            int div = d[val][j];
            cnt[div] += in[x];
            cnt_b += cnt[div] * cnt[div] * mobius[div];
        }
        ll ans = (cnt_b - cnt_a) / 2;
        cout << ans << "\n";
    }
    
    return 0;
}