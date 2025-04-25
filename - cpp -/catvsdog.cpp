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

//Kattis - catvsdog

//bruh, i just solved a problem like this, how did i not get this lol

//lets represent each voter as a node. If the opinions of two voters conflict (if there is an animal
//that one voter wants to keep in and the other one wants to remove), draw an edge between those voters. 
//Then, we are simply finding the size of the maximum independent set in the graph. 

//Observe that the graph is bipartite (cat lovers can only conflict with dog lovers and vice versa). 
//Then, the maximum independent set is the complement of the minimum vertex covering, which is the same
//as the maximum matching on the graph. We can then just use max flow to determine maximum matching. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int c, d, v;
        cin >> c >> d >> v;
        vector<pii> cv(0), dv(0);
        for(int i = 0; i < v; i++){
            string s1, s2;
            cin >> s1 >> s2;
            int i1 = stoi(s1.substr(1)), i2 = stoi(s2.substr(1));
            if(s1[0] == 'C') cv.push_back({i1, i2});
            else dv.push_back({i1, i2});
        }
        int idptr = 0;
        int ssource = idptr ++, ssink = idptr ++;
        vi cvid(cv.size()), dvid(dv.size());
        for(int i = 0; i < cv.size(); i++) cvid[i] = idptr ++;
        for(int i = 0; i < dv.size(); i++) dvid[i] = idptr ++;
        MCMF mcmf(idptr);
        for(int i = 0; i < cv.size(); i++){
            mcmf.addEdge(ssource, cvid[i], 1, 0);
            for(int j = 0; j < dv.size(); j++){
                if(cv[i].first == dv[j].second || cv[i].second == dv[j].first) {
                    mcmf.addEdge(cvid[i], dvid[j], 1, 0);
                }
            }
        }
        for(int i = 0; i < dv.size(); i++) {
            mcmf.addEdge(dvid[i], ssink, 1, 0);
        }
        cout << v - mcmf.maxflow(ssource, ssink).first << "\n";
    }
    
    return 0;
}