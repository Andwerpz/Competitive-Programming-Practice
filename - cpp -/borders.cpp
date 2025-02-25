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

//ICPC NAC 2021 - C

//can reduce to minimum vertex covering on a bipartite graph, which via konig's theorem is equivalent to maximum matching
//on a bipartite graph. Can solve maximum bipartite matching with max flow. 

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
    
    int n, m;
    cin >> n >> m;
    //identify all components, assign ids
    int idptr = 0;
    vvi id(n, vi(m, -1));
    vvi g(n, vi(m));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++) g[i][j] = s[j] - '0';
    }
    // cout << "IDENTIFY COMPONENTS" << endl;
    vi dr = {-1, 1, 0, 0}, dc = {0, 0, -1, 1};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(id[i][j] != -1) continue;
            queue<pii> q;
            q.push({i, j});
            id[i][j] = idptr ++;
            while(q.size() != 0){
                int r = q.front().first, c = q.front().second;
                q.pop();
                for(int k = 0; k < 4; k++){
                    int nr = r + dr[k], nc = c + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc > m) continue;
                    if(id[nr][nc] != -1) continue;
                    if(g[nr][nc] != g[r][c]) continue;
                    id[nr][nc] = id[r][c];
                    q.push({nr, nc});
                }
            }
        }
    }
    //see which nodes are touching the edge
    // cout << "CHECK EDGE" << endl;
    vb t(idptr, false);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i == 0 || i == n - 1 || j == 0 || j == m - 1) t[id[i][j]] = true;
        }
    }
    vvb ve(idptr, vb(idptr, false));
    vvi c(idptr);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k < 4; k++){
                int nr = i + dr[k], nc = j + dc[k];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                if(id[nr][nc] != id[i][j] && !ve[id[nr][nc]][id[i][j]]) {
                    if(!t[id[nr][nc]] && !t[id[i][j]]) {
                        ve[id[nr][nc]][id[i][j]] = true;
                        ve[id[i][j]][id[nr][nc]] = true;
                        c[id[nr][nc]].push_back(id[i][j]);
                        c[id[i][j]].push_back(id[nr][nc]);
                    }
                }
            }
        }
    }
    // cout << "COLOR" << endl;
    vi col(idptr, -1);
    for(int i = 0; i < idptr; i++){
        if(col[i] != -1) continue;
        col[i] = 0;
        queue<int> q;
        q.push(i);
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int x : c[cur]) if(col[x] == -1) col[x] = col[cur] ^ 1, q.push(x);
        }
    }
    // cout << "MAXFLOW" << endl;
    int S = idptr, T = idptr + 1;
    // cout << "S T : " << S << " " << T << "\n";
    MCMF mcmf(idptr + 2);
    for(int i = 0; i < idptr; i++){
        if(!col[i]) {
            mcmf.addEdge(S, i, 1, 1);
            for(int x : c[i]) mcmf.addEdge(i, x, 1, 0);
        }
        else mcmf.addEdge(i, T, 1, 0);
    }
    int ans = mcmf.maxflow(S, T).first;
    // cout << "FLOW : " << ans << "\n";
    for(int i = 0; i < idptr; i++) ans += t[i];
    cout << ans << "\n";
    
    return 0;
}