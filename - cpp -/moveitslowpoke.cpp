#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<bool> vb;

//ICPC ECNA 2025 - H

int g[100][100];
int c[100][100][100];
int vis[100][100][101];
int dis[100][100][101];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, k, d, s, t; cin >> n >> m >> k >> d >> s >> t;
    s--; t--;

    for(int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        g[a][b] = c;
        g[b][a] = c;
    }

    for(int i = 0; i < k; i++) {
        int a, b, d; cin >> a >> b >> d;
        a--; b--; d--;
        c[a][b][d] = 1;
    }

    for(int i = 0; i < 100; i++) for(int j = 0; j < 100; j++) for(int k = 0; k < 101; k++) dis[i][j][k] = 1e9;

    priority_queue<array<ll,4>, vector<array<ll,4>>, greater<array<ll,4>>> pq;

    auto add_q = [&](int node, int parent, int cd, int time) -> void {
        if(cd > d) return;
        if(vis[node][parent][cd]) return;
        if(time < dis[node][parent][cd]) {
            dis[node][parent][cd] = time;
            pq.push({time, node, parent, cd});
        }
    };

    for(int i = 0; i < n; i++) {
        if(g[s][i]) {
            add_q(i, s, min(d, g[s][i]), g[s][i]);
        }
    }

    while(pq.size()) {
        auto [time, node, parent, cd] = pq.top();
        pq.pop();

        if(vis[node][parent][cd]) continue;
        vis[node][parent][cd] = 1;

        for(int i = 0; i < n; i++) {
            if(g[node][i] && i != parent) {
                int ncd;
                if(c[parent][node][i]) {
                    ncd = cd + g[node][i];
                } else {
                    ncd = min(d, g[node][i]);
                }
                add_q(i, node, ncd, time + g[node][i]);
            }
        }
    }

    int res = 1e9;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= d; j++) {
            res = min(res, dis[t][i][j]);
        }
    }

    if(res == 1e9) {
        cout << "impossible\n";
    } else {
        cout << res << '\n';
    }


    return 0;
}

/*

7 8 3 29 1 7
1 2 20
2 3 10
2 4 4
4 3 8
2 5 6
5 6 8
6 3 4
3 7 10
1 2 3
1 2 4
2 5 6


*/