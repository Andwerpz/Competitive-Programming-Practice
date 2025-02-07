#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//2022-2023 Winter Petrozavodsk Camp Day 4 - M

//came up with right strat, template diffed

//we can model this as a mcmf problem. Have a node representing every room and every spot that we can place windows. 
//to enforce that room (i, j) has exactly w[i][j] windows, draw from the source to node (i, j) with capacity w[i][j]

//from every room, draw an edge to every placeable window from this room an edge with capacity 1. This enforces that
//each window can only be placed once from every room. 

//from every window, draw two edges to the sink, one with capacity 1, cost 0 and another with capacity 1, cost (whatever the
//product of the two cells this window connects). 

//finally, the answer is simply the minimum cost of the maximum flow in this graph. 

struct UCF_MCMF {
    const ll INF = LLONG_MAX >> 2;

    struct Edge {
        int v;
        ll cap, flow, cost;
    };

    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<pair<int, int>> par;
    vector<int> in_q;
    vector<ll> dist, pi;

    UCF_MCMF(int n) : n(n), adj(n), dist(n), pi(n), par(n), in_q(n) {}

    void addEdge(int u, int v, ll cap, ll cost) {
        int idx = edges.size();
        edges.push_back({v, cap, 0, cost});
        edges.push_back({u, cap, cap, -cost});
        adj[u].push_back(idx);
        adj[v].push_back(idx ^ 1);
    }

    bool find_path(int s, int t) {
        fill(dist.begin(), dist.end(), INF);
        fill(in_q.begin(), in_q.end(), 0);
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        in_q[s] = 1;

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            in_q[cur] = 0;

            for (int idx : adj[cur]) {
                Edge& e = edges[idx];
                int nxt = e.v;
                ll cap = e.cap, fl = e.flow, wt = e.cost;
                ll nxtD = dist[cur] + wt;

                if (fl >= cap || nxtD >= dist[nxt]) continue;

                dist[nxt] = nxtD;
                par[nxt] = {cur, idx};

                if (!in_q[nxt]) {
                    q.push(nxt);
                    in_q[nxt] = 1;
                }
            }
        }
        return dist[t] < INF;
    }

    pair<ll, ll> calc(int s, int t) {
        ll flow = 0, cost = 0;

        while (find_path(s, t)) {
            for (int i = 0; i < n; i++) {
                pi[i] = min(pi[i] + dist[i], INF);
            }

            ll f = INF;
            for (int v = t, u, i; v != s; v = u) {
                tie(u, i) = par[v];
                f = min(f, edges[i].cap - edges[i].flow);
            }

            flow += f;
            for (int v = t, u, i; v != s; v = u) {
                tie(u, i) = par[v];
                edges[i].flow += f;
                edges[i ^ 1].flow -= f;
            }
        }

        for (size_t i = 0; i < edges.size() / 2; i++) {
            cost += edges[i * 2].cost * edges[i * 2].flow;
        }

        return {flow, cost};
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi p(n, vi(m)), vid(n, vi(m + 1)), hid(n + 1, vi(m)), nid(n, vi(m)), w(n, vi(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> p[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> w[i][j];
        }
    }
    int idptr = 0;
    int s = idptr ++, t = idptr ++, aux = idptr ++;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            nid[i][j] = idptr ++;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= m; j++){
            vid[i][j] = idptr ++;
        }
    }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j < m; j++){
            hid[i][j] = idptr ++;
        }
    }
    UCF_MCMF mcmf(idptr);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            mcmf.addEdge(s, nid[i][j], w[i][j], 0);
            mcmf.addEdge(nid[i][j], vid[i][j], 1, 0);
            mcmf.addEdge(nid[i][j], vid[i][j + 1], 1, 0);
            mcmf.addEdge(nid[i][j], hid[i][j], 1, 0);
            mcmf.addEdge(nid[i][j], hid[i + 1][j], 1, 0);
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= m; j++){
            mcmf.addEdge(vid[i][j], t, 1, 0);
            if(j != 0 && j != m) mcmf.addEdge(vid[i][j], aux, 1, p[i][j - 1] * p[i][j]);
        }
    }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j < m; j++){
            mcmf.addEdge(hid[i][j], t, 1, 0);
            if(i != 0 && i != n) mcmf.addEdge(hid[i][j], aux, 1, p[i - 1][j] * p[i][j]);
        }
    }
    mcmf.addEdge(aux, t, 50 * 50 * 2, 0);
    cout << mcmf.calc(s, t).second << "\n";
    
    return 0;
}