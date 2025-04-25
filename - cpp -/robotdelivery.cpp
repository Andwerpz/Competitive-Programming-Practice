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

//Spring 2025 Columbia University Local Contest - I

//first, root the tree. Then, for each subtree, compute the minimum amount of robots that must travel along the
//edge from yourself to your parent. The amount is exactly the difference between the number of robots in the 
//subtree and the number of delivery points. Then the answer is simply the sum over all the edges. 

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

int solve_slow(int n, int k, vvi& c, vi& a, vi& b) {
    int idptr = 0;
    vi nid(n);
    vi acnt(n, 0), bcnt(n, 0);
    for(int i = 0; i < n; i++) nid[i] = idptr ++;
    int ssource = idptr ++, ssink = idptr ++;
    MCMF mcmf(idptr);
    for(int i = 0; i < n; i++){
        for(int x : c[i]) mcmf.addEdge(nid[i], nid[x], 1e9, 1);
    }
    for(int i = 0; i < k; i++) {
        acnt[a[i]] ++;
    }
    for(int i = 0; i < k; i++) {
        bcnt[b[i]] ++;
    }
    for(int i = 0; i < n; i++){
        if(acnt[i] != 0) mcmf.addEdge(ssource, nid[i], acnt[i], 0);
        if(bcnt[i] != 0) mcmf.addEdge(nid[i], ssink, bcnt[i], 0);   
    }
    return mcmf.maxflow(ssource, ssink, k).second;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vvi c(n);
    vi a(n), b(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    for(int i = 0; i < k; i++) cin >> a[i];
    for(int i = 0; i < k; i++) cin >> b[i];
    vi acnt(n, 0), bcnt(n, 0);
    for(int i = 0; i < k; i++) {
        a[i] --, b[i] --;
        acnt[a[i]] ++, bcnt[b[i]] ++;
    }
    function<int(int, int, vi&)> calc_subt = [&](int cur, int p, vi& v) -> int {
        for(int x : c[cur]) if(x != p) v[cur] += calc_subt(x, cur, v);
        return v[cur];
    };
    calc_subt(0, -1, acnt), calc_subt(0, -1, bcnt);
    function<ll(int, int)> solve = [&](int cur, int p) -> ll {
        ll ans = 0;
        ans += abs(acnt[cur] - bcnt[cur]);
        for(int x : c[cur]) if(x != p) ans += solve(x, cur);
        return ans;  
    };
    cout << solve(0, -1) << "\n";
    
    return 0;
}