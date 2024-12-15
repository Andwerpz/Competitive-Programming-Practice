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

ll subt_cnt(int cur, int p, vvi& c){
    ll ans = 1;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p) continue;
        ans += subt_cnt(next, cur, c);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    //we want the 0 edge to belong to as many paths as possible
    //then, with the 1 edge, we should place it adjacent to the 0 edge, but which edge to choose?
    //so we're going to place a bunch of edges along a path. I'm guessing this path is the diameter?
    //not necessarily the diameter?
    //this is suboptimal

    int n;
    cin >> n;
    vvi c(n);
    vector<pii> e;
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
        e.push_back({u, v});
    }
    ll ans = 0;
    int l, r;
    //find best place to put 0, just try every edge
    for(int i = 0; i < n - 1; i++){
        int u = e[i].first, v = e[i].second;
        ll cans = subt_cnt(u, v, c) * subt_cnt(v, u, c);
        if(cans > ans){
            ans = cans;
            l = u;
            r = v;
        }
    }
    //put more and more edges in until you can't
    vb v(n, false);
    v[l] = true, v[r] = true;
    int pl = r, pr = l;
    while(c[l].size() != 1 || c[r].size() != 1){
        ll inc = 0;
        int nl, nr;
        ll lcnt = subt_cnt(l, pl, c), rcnt = subt_cnt(r, pr, c);
        for(int i = 0; i < c[l].size(); i++){
            int next = c[l][i];
            if(v[next]) continue;
            ll cinc = subt_cnt(next, l, c) * rcnt;
            if(cinc > inc){
                inc = cinc;
                nl = next;
                nr = r;
            }
        }
        for(int i = 0; i < c[r].size(); i++){
            int next = c[r][i];
            if(v[next]) continue;
            ll cinc = subt_cnt(next, r, c) * lcnt;
            if(cinc > inc){
                inc = cinc;
                nr = next;
                nl = l;
            }
        }
        ans += inc;
        v[nl] = true, v[nr] = true;
        if(l != nl) pl = l, l = nl;
        if(r != nr) pr = r, r = nr;
    }
    cout << ans << "\n";
    
    return 0;
}