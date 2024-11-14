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

#include <bits/extc++.h>
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
typedef pair<int, int> pii;
typedef vector<ll> VL;
const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
    struct edge {
        int from, to, rev;
        ll cap, cost, flow;
    };
    int N
    vector<vector<edge>> ed;
    vector<int> seen;
    vector<ll> dist, pi;
    vector<edge*> par;

    MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

    void addEdge(int from, int to, ll cap, ll cost) {
        if(from == to) return;
        ed[from].push_back(edge{from, to, sz(ed[to]), cap, cost, 0});
        ed[to].push_back(edge{to, from, sz(ed[from]) - 1, 0, -cost, 0});
    }

    void path(int s){
        fill(all(seen), 0);
        fill(all(dist), INF);
        dist[s] = 0; ll di;

        __gnu_pbds::priority_queue<pair<ll, int>> q;
        vector<decltype(p)::point_iterator> its(N);
        q.push({0, s});

        while(!q.empty()) {
            s = q.top().second; q.pop();
            seen[s] = 1; di = dist[s] + pi[s];
            for(edge& e : ed[s]) if (!seen[e.to]) {
                ll val = di - pi[e.to] + e.cost;
                if(e.cap - e.flow > 0 && val < dist[e.to]) {
                    dist[e.to] = val;
                    par[e.to] = &e;
                    if(its[e.to] == q.end()) 
                        its[e.to] = q.push({-dist[e.to], e.to});
                    else 
                        q.modify(its[e.to], {-dist[e.to], e.to});
                }
            }
        }
        rep(i, 0, N) pi[i] = min(pi[i] + dist[i], INF);
    }

    pair<ll, ll> maxflow(int s, int t, ll max_flow = INF) {
        ll totflow = 0, totcost = 0;
        while(path(s), seen[t] && totflow < max_flow) {
            ll fl = max_flow - totflow;
            for(edge* x = par[t]; x; x = par[x->from]) 
                fl = min(fl, x->cap - x->flow);

            totflow += fl;
            for(edge* x = par[t]; x; x = par[x->from]) {
                x->flow += fl;
                ed[x->to][x->rev].flow -= fl;
            }
        }
        rep(i, 0, N) for(edge& e : ed[i]) totcost += e.cost * e.flow;
        return {totflow, totcost / 2};
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vi vin(n), vout(n);
    int ptr = 0;
    int ssource = ptr ++;
    int ssink = ptr ++;
    for(int i = 0; i < n; i++){
        vin[i] = ptr ++;
        vout[i] = ptr ++;
    }
    int bin = ptr ++;
    int bout = ptr ++;
    MCMF mf(ptr);
    mf.addEdge(ssource, bin, 1, 0);
    mf.addEdge(bout, ssink, 1, 0);
    //vertex weights
    for(int i = 0; i < n; i++){
        int v;
        cin >> v;
        mf.addEdge(bin, vin[i], 1, v);
        mf.addEdge(vout[i], bout, 1, v);
        mf.addEdge(vin[i], vout[i], 1, 0);
    }
    //edges
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        mf.addEdge(vout[u], vin[v], 1, w);
        mf.addEdge(vout[v], vin[u], 1, w);
    }
    
    return 0;
}