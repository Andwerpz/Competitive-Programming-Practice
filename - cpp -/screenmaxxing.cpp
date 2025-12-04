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

//UTPC 11-12-2025 Div1 - E

//we can test locking each door in O(1) time. 

void dfs1(vvi& c, int cur, int p, vl& ssum, vl& a) {
    ssum[cur] = a[cur];
    for(int x : c[cur]) {
        if(x == p) continue;
        dfs1(c, x, cur, ssum, a);
        ssum[cur] += ssum[x];
    }
}

ll dfs2(vvi& c, int cur, int p, ll tot, vl& ssum) {
    ll ans = 0;
    for(int x : c[cur]) {
        if(x == p) continue;
        ans = max(ans, dfs2(c, x, cur, tot, ssum));
        ans = max(ans, ssum[x] * (tot - ssum[x]));
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vl ssum(n);
    vvi c(n);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    dfs1(c, 0, -1, ssum, a);
    ll tot = ssum[0];
    ll rm = dfs2(c, 0, -1, tot, ssum);
    ll ans = 0;
    // cout << "RM : " << rm << " " << tot << "\n";
    for(int i = 0; i < n; i++) ans += a[i] * (tot - a[i]);
    ans /= 2;
    ans -= rm;
    cout << ans << "\n";

    return 0;
}