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

//2025 NAQ - M

//lets try to solve the problem without doing balancing (A -> B != B -> A), however we still have the 
//restriction that everyone must spend and recieve 10,000 points.

//we can solve this using max flow, each node turns into two nodes (a_1, a_2), each edge (a, b) turns into
//two directed edges (a_1, b_2) and (b_1, a_2). We draw an edge from the source to each a_1 and
//from each a_2 to the sink with capacity 10,000. Finally, if the maximum flow is n * 10,000, then there
//is an answer that we can extract. 

//so how can we use this to solve the original problem. The main issue with the above is that there is no
//way to enforce that flows (a_1, b_2) and (b_1, a_2) are equal. However, there's a neat trick that we can
//do (thanks josh): we instead look for a max flow of n * 5,000. If we can find one, then we can construct
//a balanced solution with flow n * 10,000 by just adding (b_1, a_2) to (a_1, b_2) and adding
//(a_1, b_2) to (b_1, a_2).
//then, it's guaranteed that the flow are equal, and that each node spends and recieves exactly 10,000.

//the only issue left is to prove that there is a bijection from the original problem to our new
//5,000 flow problem. We've already shown that if a solution to the 5,000 flow problem exists, there also 
//exists a solution to the original problem. Now we need to show that if a solution to the original problem
//exists, there exists a solution to the 5,000 flow problem. 

//suppose we have a solution to the original problem. Observe that if we assign to all the edges an even 
//weight, then we can directly derive a solution to the 5000 flow problem. Otherwise, there exist some edges
//with odd weight, but notice that there can only be an even amount of odd weight edges incident on every node
//as the sum on every node is even. 

//we'll need this next fact to continue: if we have an undirected graph where all nodes have even degree, 
//then this graph is just a union of a bunch of simple cycles (no edges are reused). 
//then, if we just consider all edges where the weight is odd, we can partition them into a bunch of odd 
//cycles of purely odd edges. Then, we can walk each cycle and alternate between adding +1 and -1 to force
//the edge weights to be even. 

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> T edmondsKarp(vector<unordered_map<int, T>> &graph, int source, int sink) {
    assert(source != sink);
    T flow = 0;
    vi par(sz(graph)), q = par;

    for(;;) {
        fill(all(par), -1);
        par[source] = 0;
        int ptr = 1;
        q[0] = source;

        rep(i, 0, ptr) {
            int x = q[i];
            for (auto e : graph[x]) {
                if(par[e.first] == -1 && e.second > 0) {
                    par[e.first] = x;
                    q[ptr++] = e.first;
                    if (e.first == sink) goto out;
                }
            }
        }
        return flow;
    out:
        T inc = numeric_limits<T>::max();
        for (int y = sink; y != source; y = par[y]) {
            inc = min(inc, graph[par[y]][y]);
        }
        flow += inc;
        for(int y = sink; y != source; y = par[y]) {
            int p = par[y];
            if((graph[p][y] -= inc) <= 0) {
                graph[p].erase(y);
            }
            graph[y][p] += inc;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<unordered_map<int,int>> g(n * 2 + 2);
    int s = n * 2, t = n * 2 + 1;

    for(int i = 0; i < n; i++) {
        g[s][i] = 5000;
        g[n + i][t] = 5000;
    }

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        int tou = u + n;
        int tov = v + n;
        g[u][tov] = 5000;
        g[v][tou] = 5000;
    }

    // cout << "make it here 1" << endl;

    int flow = edmondsKarp(g, s, t);

    if(flow != n * 5000) {
        cout << "-1\n";
        return 0;
    }

    // cout << "make it here 1.1" << endl;

    vector<vector<int>> res(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        int from = i + n;
        for(auto [to, f] : g[from]) {
            // cout << "to : " << to << " f : " << f << endl;
            res[i][to] += f;
            res[to][i] += f;
        }
    }

    // cout << "make it here 2" << endl;

    if(flow == n * 5000) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << res[i][j] << " \n"[j == n - 1];
            }
        }
    } else {
        cout << "-1\n";
    }
    
    return 0;
}