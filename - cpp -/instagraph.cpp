#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

//NCPC 2025 - I

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m; cin >> n >> m;
    vector<set<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[v].insert(u);
    }

    int res = -1, mx = -1;
    for(int i = 0; i < n; i++) {
        int cnt = 0;
        for(int x : adj[i]) {
            if(adj[x].count(i) == 0) cnt++;
        }
        if(cnt > mx) {
            res = i;
            mx = cnt;
        }
    }

    cout << res + 1 << " " << mx << '\n';

    return 0;
}