#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1913E

//we can turn this into a min cost flow problem. 

//let's imagine building another matrix 'b', where we want to maximize the amount of cases where if
//a[i][j] = 1, then b[i][j] = 1. Since the number of 1s in 'b' is fixed, this is identical to minimizing
//the cases where b[i][j] = 1 and a[i][j] = 0. Note that maximizing the cases where a[i][j] = 1 then
//b[i][j] = 1 will also maximize the cases where a[i][j] = 0 then b[i][j] = 0, because the number of 1s
//and 0s in b are fixed. 

//so we have 3 constraints for b:
//1 - the number of 1s on row i must be A[i]
//2 - the number of 1s on column i must be B[i]
//3 - the number of cases where b[i][j] = 1 and a[i][j] = 0 is minimal

//we can make a source and sink; S, T, and we have one node for each row and column of b, denoted by 
//R[i] and C[j]. To enforce constraint 1, we can draw edges from the source, S, to each row, with the edge
//(S, R[i]) having capacity A[i] and cost 0. Similarly for constraint 2, we draw edges from each column 
//to the sink with edge (C[j], T) having capacity B[j]. 

//to enforce constraint 3, for each pair of i, j, we draw an edge from row i to column j. Each edge will
//have a capacity of 1, as each grid cell can have at most 1 '1' placed in it, and if a[i][j] = 0, then
//the cost will be 1, to make sure we minimize these cases. 

struct Edge {
    ll from, to, capacity, cost;
    Edge(ll from, ll to, ll capacity, ll cost) {
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m, 0));
    int nr_one = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> g[i][j];
            nr_one += g[i][j];
        }
    }
    vector<int> a(n), b(m);
    int a_sum = 0;
    int b_sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a_sum += a[i];
    }
    for(int i = 0; i < m; i++){
        cin >> b[i];
        b_sum += b[i];
    }
    if(a_sum != b_sum || a_sum > n * m) {
        cout << "-1\n";
        return 0;
    }
    int ptr = 0;
    int source = ptr ++;
    int sink = ptr ++;
    vector<int> r(n), c(m);
    for(int i = 0; i < n; i++){
        r[i] = ptr ++;
    }
    for(int i = 0; i < m; i++){
        c[i] = ptr ++;
    }
    vector<Edge> e(0);
    //source to row
    for(int i = 0; i < n; i++){
        e.push_back({source, r[i], a[i], 0});
    }
    //row to col
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            e.push_back({r[i], c[j], 1, g[i][j] == 0? 1 : 0});
        }
    }
    //col to sink
    for(int i = 0; i < m; i++){
        e.push_back({c[i], sink, b[i], 0});
    }
    int o_cost = min_cost_flow(ptr, e, source, sink, a_sum); //nr zeroes we replace
    if(o_cost == -1){
        cout << "-1\n";
        return 0;
    }
    int z_cost = nr_one - (a_sum - o_cost); //nr ones we don't use
    cout << o_cost + z_cost << "\n";

    return 0;
}
