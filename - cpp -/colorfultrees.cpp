#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;
typedef vector<ll> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<ll>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __ll128 lll;
// typedef __float128 lld;

//2024 ICPC NAQ - D

//just need to get the counts of all color nodes for every subtree. Can update in O(n * log(n)) time
//amortized if we merge larger subtrees into smaller ones, like in DSU. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n; cin >> n;
    vector<ll> c(n);
    for(ll &x : c) cin >> x;
    vector<vector<array<ll,2>>> adj(n);

    for(ll i = 0; i < n - 1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back({b,i});
        adj[b].push_back({a,i});
    }

    vector<ll> parent_edges(n,-1);

    auto dfs = [&](auto self, ll i, ll p) -> void {

        for(auto [child, edge_id] : adj[i]) {
            if(child != p) {
                parent_edges[child] = edge_id;
                self(self, child, i);
            }
        }

    };

    dfs(dfs, 0, -1);

    // for(ll i = 0; i < n; i++) {
    //     cout << parent_edges[i] << " \n"[i == n - 1];
    // }

    vector<map<ll,ll>> dp(n);
    vector<ll> cnts(n);
    vector<ll> res(n);

    vector<ll> colorcnts(n + 1);
    for(ll i : c) {
        colorcnts[i]++;
    }

    auto add = [&](ll &currscore, map<ll,ll> &dpmap, ll addcolor) -> void {
        ll totalcolor = colorcnts[addcolor];
        ll currsize = dpmap[addcolor];
        currscore -= currsize * (totalcolor - currsize);
        currsize++;
        currscore += currsize * (totalcolor - currsize);
        dpmap[addcolor]++;
    };

    auto dfs2 = [&](auto self, ll i, ll p) -> void {
        ll largest_child = -1;
        for(auto [child, edge_id] : adj[i]) {
            if(child != p) {
                self(self, child, i);
                if(largest_child == -1 || dp[child].size() > dp[largest_child].size()) {
                    largest_child = child;
                }
            }
        }

        ll score = 0;
        if(largest_child != -1) {
            score = cnts[largest_child];
            swap(dp[i], dp[largest_child]);
        }

        for(auto [child, edge_id] : adj[i]) {
            if(child != p && child != largest_child) {
                for(auto [color, numcolor] : dp[child]) {
                    for(ll j = 0; j < numcolor; j++) {
                        add(score, dp[i], color);
                    }
                }
            }
        }
        // cout << "i : " << i << " add color : " << c[i] << " current cnt : " << dp[i][c[i]] << " curr score : " << score << " color cnt : " << colorcnts[c[i]] << '\n';
        add(score, dp[i], c[i]);
        // cout << "next cnt : " << score << '\n';
        cnts[i] = score;
        if(i) {
            res[parent_edges[i]] = score;
        }

    };

    dfs2(dfs2, 0, -1);

    for(ll i = 1; i < n; i++) {
        cout << res[i-1] << '\n';
    }

    
    return 0;
}