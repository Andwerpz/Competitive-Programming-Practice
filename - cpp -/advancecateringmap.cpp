#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2015 - C

//this is apparently a classic min cost max flow problem. 

struct Edge {
    int from, to, capacity, cost;
    Edge(int from, int to, int capacity, int cost) {
        this->from = from;
        this->to = to;
        this->capacity = capacity;
        this->cost = cost;
    }
};

vector<vector<int>> adj, cost, capacity;

const int INF = 1e9;

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
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
//K = target flow
int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;
    int cost = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        int f = K - flow;
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

    if (flow < K)
        return -1;
    else
        return cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    int ptr = 0;
    int ssource = ptr ++;
    int ssink = ptr ++;
    vector<int> fid(n + 1, 0);
    vector<int> tid(n + 1, 0);
    for(int i = 0; i < n + 1; i++){
        fid[i] = ptr ++;
        if(i != 0){
            tid[i] = ptr ++;
        }
    }
    vector<Edge> edges;
    //from source to prececessors
    edges.push_back(Edge(ssource, fid[0], k, 0));
    for(int i = 1; i < fid.size(); i++){
        edges.push_back(Edge(ssource, fid[i], 1, 0));
    }
    //from prececessors to requests
    for(int i = 0; i < n; i++){
        int m = n - i;
        for(int j = 1; j <= m; j++){
            int cost;
            cin >> cost;
            edges.push_back(Edge(fid[i], tid[i + j], 1, cost));
        }
    }
    //from requests to sink
    for(int i = 1; i < tid.size(); i++){
        edges.push_back(Edge(tid[i], ssink, 1, 0));
    }
    cout << min_cost_flow(ptr, edges, n, ssource, ssink) << "\n";
    
    return 0;
}
