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

//CTU Open 2021 - H

//if we compress all nodes with only 1 child, each bread will go log(n) junctions on average. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q; cin >> n >> q;

    vector<vector<int>> adj(n);

    for (int i = 1; i < n; ++i) {
        int x; cin >> x;
        adj[x].push_back(i);
    }

    vector<int> ans(q);

    auto dfs = [&](auto dfs, int v, vector<int>& a) {
        if (a.size() == 0)
            return;

        if (adj[v].size() == 0) {
            for (auto x : a) {
                ans[x] = v;
            }
            return;
        } else if (adj[v].size() == 1) {
            dfs(dfs, adj[v][0], a);
        } else {
            // actual work
            vector<vector<int>> split(adj[v].size());
            for (int i = 0; i < a.size(); ++i) {
                split[i % (adj[v].size())].push_back(a[i]);
            }

            for (int i = 0; i < adj[v].size(); ++i) {
                dfs(dfs, adj[v][i], split[i]);
            }
        }
        
    };

    vector<int> b;
    for (int i = 0; i < q; ++i) {
        b.push_back(i);
    }

    dfs(dfs, 0, b);

    for (auto x : ans)
        cout << x << "\n";
    // cerr << endl;
    
    return 0;
}