#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
using pi = pair<int, int>;

//ICPC Finals 2014

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<vector<int>> adj(n), rev_adj(n);

    for (int i = 0; i < n; ++i) {
        int m; cin >> m;
        adj[i].assign(m, 0);
        for (int j = 0; j < m; ++j) {
            string s; cin >> s;
            for (auto c : s) {
                int b = c - 'a';
                // cerr << "b : " << b << endl;
                adj[i][j] ^= (1 << b);
            }
        }
    }

    // for (auto v : adj) {
    //     for (auto x : v) {
    //         cerr << x << " ";
    //     }
    //     cerr << endl;
    // }

    vector<vector<int>> dp(n, vector<int>(n, -1));

    // dp[i][j] = min cost to force j from i
    for (int i = 0; i < n; ++i) {
        vector<vector<int>> adj_c = adj;
        // trying to force i
        dp[i][i] = 0;
        vector<bool> used(n);
        queue<pi> q;
        q.push({i, 0});
        while (q.size()) {
            auto p = q.front();
            int v = p.first, d = p.second;
            q.pop();
            if (used[v]) continue;
            used[v] = true;
            dp[v][i] = d;
            for (int j = 0; j < n; ++j) {
                if (used[j]) continue;
                // cerr << "v : " << v << " j : " << j << endl;
                for (auto& x : adj_c[j]) {
                    if (x & (1 << v)) {
                        x ^= (1 << v);
                    }
                    // cerr << x << " ";
                    if (!x) {
                        q.push({j, d+1});
                    }
                }
                // cerr << endl;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
