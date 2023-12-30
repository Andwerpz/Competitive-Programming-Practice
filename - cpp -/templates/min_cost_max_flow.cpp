#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//given a target flow, what is the minimum cost to acheive that flow?
//each edge has some cost, which is the cost per unit of flow. 

//when using this, keep in mind that you can't have any backedges, 
//between two nodes, there must be exactly 1 edge. 

struct Edge {
    ll from, to, capacity, cost;
    Edge(int from, int to, ll capacity, ll cost) {
        this->from = from;
        this->to = to;
        this->capacity = capacity;
        this->cost = cost;
    }
    Edge() {}
};

vector<vector<ll>> adj, cost, capacity;

const int INF = 1e9;

void shortest_paths(int n, int v0, vector<ll>& d, vector<ll>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

//N = node amt
//s = source
//t = sink
//K = target flow; if set to infinity, then will find min cost of max flow. 
ll min_cost_flow(int N, vector<Edge> edges, int s, int t, ll K = 1e18) {
    adj.assign(N, vector<ll>());
    cost.assign(N, vector<ll>(N, 0));
    capacity.assign(N, vector<ll>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    ll flow = 0;
    ll cost = 0;
    vector<ll> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        ll f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    if(flow == K || K == 1e18) {
        return cost;
    }
    return -1;
}