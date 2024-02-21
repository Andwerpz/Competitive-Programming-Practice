#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;
typedef vector<int> vi;

//ICPC NAQ 2023 - K

//tried to use HLD to solve, but it TLE D:
//the idea is correct, just too slow. 

//apparently, can use binary lifting to get it to n * log(n)

struct DSU {
    int N;
    vector<int> dsu;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    void dsu_init() {
        for(int i = 0; i < N; i++){
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        dsu[rb] = ra;
        
        return true;
    }
};

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = -inf, madd = 0, val = inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vector<int>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = min(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
        // cout << "SEGT QUERY : " << L << " " << R << endl;
		if (R <= lo || hi <= L) return inf;
		if (L <= lo && hi <= R) return val;
		push();
		return min(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != -inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = -inf;
	}
};

struct HLD {
    bool VALS_EDGES = true;
	int N, tim = 0;
	vector<vector<int>> adj;
	vi par, siz, depth, rt, pos;
	Node *tree;
	HLD(vector<vi> adj_): 
    N(adj_.size()), adj(adj_), par(N, -1), siz(N, 1), depth(N), rt(N),
    pos(N),tree(new Node(0, N)){ dfsSz(0); dfsHld(0); }
	
    void dfsSz(int v) {
		if (par[v] != -1) adj[v].erase(find(adj[v].begin(), adj[v].end(), par[v]));
		for (int& u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(int u, int v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v]) swap(u, v);
        // cout << "PROCESS : " << pos[u] << " " << pos[v] << "\n";
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void modifyPath(int u, int v, int val) {
		process(u, v, [&](int l, int r) { tree->set(l, r, val); });
	}
	int queryPath(int u, int v) { // Modify depending on problem
		int res = 1e9;
		process(u, v, [&](int l, int r) {
				res = min(res, tree->query(l, r));
		});
		return res;
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<pair<ll, pair<int, int>>> edges(0);
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        a --;
        b --;
        edges.push_back({w, {a, b}});
    }
    //construct mst
    ll mst_cost = 0;
    DSU dsu(n);
    sort(edges.begin(), edges.end());
    vector<pair<ll, pair<int, int>>> mst_edges(0);
    for(int i = 0; i < m; i++){
        ll cost = edges[i].first;
        int a = edges[i].second.first;
        int b = edges[i].second.second;
        if(dsu.unify(a, b)) {
            mst_cost += cost;
            mst_edges.push_back({cost, {a, b}});
        }
    }
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < mst_edges.size(); i++){
        int a = mst_edges[i].second.first;
        int b = mst_edges[i].second.second;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    //construct hld
    HLD hld(c);
    for(int i = 0; i < mst_edges.size(); i++){
        int cost = mst_edges[i].first;
        int a = mst_edges[i].second.first;
        int b = mst_edges[i].second.second;
        hld.modifyPath(a, b, cost);
    }
    //calc answer
    dsu = DSU(n);
    ll ans = mst_cost;
    for(int i = 0; i < edges.size(); i++){
        ll cost = edges[i].first;
        int a = edges[i].second.first;
        int b = edges[i].second.second;
        if(!dsu.unify(a, b)){
            ll min_remove = hld.queryPath(a, b);
            hld.modifyPath(a, b, 1e9);
            ans = max(ans, mst_cost - min_remove + cost);
        }
    }
    cout << ans << "\n";
    
    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef __int128 lll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, m; cin >> n >> m;
//     vector<pair<ll, pair<int,int>>> edges;
//     vector<vector<pair<int, ll>>> adj(n+1);
//     for (int i = 0; i < m; ++i) {
//         int a, b; cin >> a >> b;
//         int c; cin >> c;
//         adj[a].push_back({b, c});
//         adj[b].push_back({a, c});
//         edges.push_back({c, {a, b}});
//     }

//     // DSU dsu(n+1);

//     priority_queue<pair<ll, pair<int, int>>> pq;
//     vector<bool> vis(n+1);
//     for (auto e : adj[1]) {
//         ll c = e.second;
//         int b = e.first;
//         pq.push({-c, {1, b}});
//     }
//     vis[1] = true;
//     cerr << "si : " << pq.size() << endl;
//     ll ans = 0;
//     ll maxdiff = 0;
//     while (pq.size()) {
//         auto e = pq.top();
//         pq.pop();
//         ll c = -e.first;
//         int a = e.second.first, b = e.second.second;
//         if (vis[a] && vis[b]) continue;
//         cerr << "a : " << a << " b : " << b << endl;
//         ans += c;
//         if (vis[b]) swap(a, b);
//         for (auto e : adj[b]) {
//             ll c2 = e.second;
//             int b2 = e.first;
//             pq.push({-c2, {b, b2}});
//         }
//     // cerr << "si : " << pq.size() << endl;
        
//         // what if we don't add this edge?
//         while (pq.size()) {
//             auto e = pq.top();
//         // pq.pop();
//             ll c = -e.first;
//             int a = e.second.first, b = e.second.second;
//             cerr << "A2 : " << a << " Ab : " << b << endl;
//             // if (b > a) swap(a, b);
//             if (vis[a] && vis[b]) {
//                 pq.pop();
//             } else break;
//         }
//         vis[a] = vis[b] = true;

//         if (pq.size()) {
//             auto e2 = pq.top();
//         // pq.pop();
//             ll c2 = -e2.first;
//             cerr << "HELLO. c2 ; " << c2 << " c : " << c << endl;
//             maxdiff = max(maxdiff, c2 - c);
//         }
//     }
//     cerr << "ans : " << ans << " maxdiff : " << maxdiff << endl;
//     cout << ans + maxdiff << endl;
//     return 0;
// }
