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

//Codeforces - 1450E

//similar idea to https://atcoder.jp/contests/agc056/tasks/agc056_c, in that to build the construction
//we convert the problem into a shortest paths problem. However, there is the same issue with the other
//problem which is I have no idea how to prove that this construction is optimal, all I can prove is
//that it follows the rules laid out by the problem. 

//I'll say that an edge is directed if b = 1, and undirected if b = 0. For the construction, a few rules
//need to be followed:
// - all adjacent nodes must have shortest path difference = 1
// - if (u, v) is a directed edge, then d[u] + 1 = d[v]

//first of all, we can see that it's never possible when the graph is not bipartite. This actually makes
//the first rule very easy to enforce: just assign all edges with weight of either 1 or -1.

//as for the second rule, we'll decompose each directed edge into a forwards and backwards edge. The 
//forwards edge has weight 1 and backwards edge has weight -1. 

//for all undirected edges, the weights will be 1 in both directions. 

//to get the answer, just choose a node and compute the shortest path from the chosen node to all other nodes
//Try every node as the source and just take the best one. 

int calc_ans(int ind, vector<vector<pii>>& c, vi& aout) {
    int n = c.size();
    vi d(n, 1e9);
    d[ind] = 0;
    priority_queue<pii> q;
    q.push({0, ind});
    while(q.size() != 0){
        int cur = q.top().second;
        int cdist = -q.top().first;
        q.pop();
        if(d[cur] != cdist) continue;
        for(pii next : c[cur]) {
            int ndist = cdist + next.second;
            if(ndist < d[next.first]) {
                d[next.first] = ndist;
                q.push({-ndist, next.first});
            }
        }
    }
    int mn = 1e9, mx = -1e9;
    for(int x : d) mn = min(mn, x), mx = max(mx, x);
    for(int& x : d) x -= mn;
    aout = d;
    return mx - mn;
}

bool has_neg_cycle(vector<vector<pii>>& c){
    int n = c.size();
    vi d(n, 1e9);
    d[0] = 0;
    bool has;
    for(int i = 0; i <= n; i++){
        has = false;
        for(int j = 0; j < n; j++){
            for(int k = 0; k < c[j].size(); k++){
                int next = c[j][k].first, w = c[j][k].second;
                if(d[j] + w < d[next]) d[next] = d[j] + w, has = true;
            }
        }
    }
    return has;
}

bool is_bipartite(vector<vector<pii>>& c){
    int n = c.size();
    vi col(n, -1);
    col[0] = 0;
    queue<int> q;
    q.push(0);
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(pii next : c[cur]) {
            if(col[next.first] != -1) {
                if(col[next.first] != (col[cur] ^ 1)) return false;
            }
            else {
                col[next.first] = col[cur] ^ 1;
                q.push(next.first);
            }
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> c(n);
    for(int i = 0; i < m; i++){
        int u, v, b;
        cin >> u >> v >> b;
        u --, v --;
        c[u].push_back({v, 1});
        c[v].push_back({u, b? -1 : 1});
    }
    if(has_neg_cycle(c) || !is_bipartite(c)) {
        cout << "NO\n";
        return 0;
    }
    int ans = -1;
    vi a;
    for(int i = 0; i < n; i++){
        vi aout;
        int cans = calc_ans(i, c, aout);
        if(cans > ans) ans = cans, a = aout;
    }
    if(ans == -1) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    cout << ans << "\n";
    for(int x : a) cout << x << " ";
    cout << "\n";
    
    return 0;
}