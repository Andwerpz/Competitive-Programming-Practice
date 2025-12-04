#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

//NCPC 2025 - G

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<int>> comps;
    vector<int> vis(n);
    int small = INT_MAX;
    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            vector<int> a;
            queue<int> q;
            q.push(i);
            vis[i] = 1;
            while(q.size()) {
                int x = q.front();
                q.pop();
                a.push_back(x);
                for(int to : adj[x]) {
                    if(vis[to] == 0) {
                        vis[to] = 1;
                        q.push(to);
                    }
                }
            }
            comps.push_back(a);
            small = min(small, (int) a.size());
            // for(int x : a) cout << x << " ";
            // cout << '\n';
        }
    }

    if(small < k) {
        cout << "impossible\n";
    } else {
        vector<int> res(n);
        for(auto a : comps) {
            for(int i = 0; i < a.size(); i++) {
                res[a[i]] = i % k;
            }
        }
        for(int i = 0; i < n; i++) cout << res[i] + 1 << " \n"[i == n - 1];
    }

    return 0;
}