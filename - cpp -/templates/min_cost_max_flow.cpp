#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//slightly modified MCMF template from KACTL

//given a target flow, what is the minimum cost to acheive that flow?
//each edge has some cost, which is the cost per unit of flow. 

//backedges between nodes are allowed. I think this works because in max flow, it only really makes sense to 
//push flow one way through an edge, given that the capacity is symmetrical. 

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
	int N;
	vector<vector<edge>> ed;
	vector<int> seen;
	vector<ll> dist, pi;
	vector<edge*> par;

	MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		if (from == to) return;
		ed[from].push_back(edge{ from,to,sz(ed[to]),cap,cost,0 });
		ed[to].push_back(edge{ to,from,sz(ed[from])-1,0,-cost,0 });
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({ 0, s });

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to]) {
				ll val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					if (its[e.to] == q.end())
						its[e.to] = q.push({ -dist[e.to], e.to });
					else
						q.modify(its[e.to], { -dist[e.to], e.to });
				}
			}
		}
		rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
	}
    
	pair<ll, ll> maxflow(int s, int t, ll max_flow = INF) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t] && totflow < max_flow) {
			ll fl = max_flow - totflow;
			for (edge* x = par[t]; x; x = par[x->from])
				fl = min(fl, x->cap - x->flow);

			totflow += fl;
			for (edge* x = par[t]; x; x = par[x->from]) {
				x->flow += fl;
				ed[x->to][x->rev].flow -= fl;
			}
		}
		rep(i,0,N) for(edge& e : ed[i]) totcost += e.cost * e.flow;
		return {totflow, totcost/2};
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int source) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[source] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,0,N) if (pi[i] != INF)
			  for (edge& e : ed[i]) if (e.cap)
				  if ((v = pi[i] + e.cost) < pi[e.to])
					  pi[e.to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

//MCMF template copied from UCF team. 
//maybe faster than the KACTL one, idk
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