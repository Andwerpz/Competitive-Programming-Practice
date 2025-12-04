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

//UTPC Contest 10-15-25 Div.1 - C

//just greedy with alot of reading. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, k, x;
    cin >> n >> m >> k >> x;
    x --;
    k -= m;
    vl s(n), w(n);
    vvl a(m);
    for(int i = 0; i < n; i++) {
        cin >> s[i];
        s[i] --;
    }
    for(int i = 0; i < n; i++) cin >> w[i];
    for(int i = 0; i < n; i++) {
        a[s[i]].push_back(w[i]);
    }
    ll ans = 0;
    vector<pll> b;  //{weight, species}
    for(int i = 0; i < m; i++) {
        sort(a[i].begin(), a[i].end());
        reverse(a[i].begin(), a[i].end());
        assert(a[i].size() != 0);
        ans += a[i][0];
        // cout << "INIT : " << a[i][0] << "\n";
        for(int j = 1; j < a[i].size(); j++) b.push_back({a[i][j], i});
    }
    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());
    map<int, int> f;
    for(int i = 0; i < b.size(); i++) {
        if(k == 0) continue;
        int cs = b[i].second;
        int cw = b[i].first;
        if(f[cs] >= x) continue;
        f[cs] ++;
        ans += cw;
        k --;
        // cout << "COLLECT : " << cw << " " << cs << "\n";
    }
    cout << ans << "\n";
    
    return 0;
}