#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//2018 South Central USA Regional - J

//notice that the maximum amount of people that can get from left to right bank is equal to the min cut, assuming that
//the capacity of each edge is 1. This should be enough to clue you in that this problem is max flow. 

//given that we can get everyone across, we want to find the minimum cost. This is just min cost flow. 

#include <ext/pb_ds/detail/standard_policies.hpp>
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
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,0,N) if (pi[i] != INF)
			  for (edge& e : ed[i]) if (e.cap)
				  if ((v = pi[i] + e.cost) < pi[e.to])
					  pi[e.to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int p, r, l;
    cin >> p >> r >> l;
    int source = r ++;
    int sink = r ++;
    MCMF mcmf(r);
    for(int i = 0; i < l; i++){
        int u, v;
        cin >> u >> v;
        u = u == -2? source : (u == -1? sink : u);
        v = v == -2? source : (v == -1? sink : v);
        mcmf.addEdge(u, v, 1, 1);
        mcmf.addEdge(v, u, 1, 1);
    }
    pair<ll, ll> ans = mcmf.maxflow(source, sink, p);
    ll flow = ans.first;
    ll cost = ans.second;
    if(flow != p){
        cout << (p - flow) << " people left behind\n";
    }
    else {
        cout << cost << "\n";
    }
    
    return 0;
}
