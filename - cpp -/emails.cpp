#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
#define rep(i, a ,b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define z(s) (int) (x).size()

//SWERC 2020 - I

//if the graph is not one connected component, then it's always impossible

//otherwise, it's always possible. The amount of days is equal to ceil(log_2(len))
//where 'len' is the maximum distance between any two nodes in the graph.

//to find the maximum distance between any two nodes in an undirected graph, you can
//just do something like tree diameter with 2 BFSs. 

vi bfs(vvi& c, int s) {
    int n = c.size();
    vi d(n, 1e9);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    while(q.size() != 0) {
        int cur = q.front();
        q.pop();
        for(int x : c[cur]) {
            if(d[x] != 1e9) continue;
            d[x] = d[cur] + 1;
            q.push(x);
        }
    }
    return d;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vi> c(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vi d1 = bfs(c, 0);
    int mxpos = 0;
    for(int i = 1; i < n; i++) {
        if(d1[i] > d1[mxpos]) {
            mxpos = i;
        }
    }
    if(d1[mxpos] == 1e9) {
        cout << "-1\n";
        return 0;
    }
    vi d2 = bfs(c, mxpos);
    int mx = 0;
    for(int i = 0; i < n; i++) {
        mx = max(mx, d2[i]);
    }
    int ans = 0;
    int p2 = 1;
    while(p2 < mx) {
        ans ++;
        p2 *= 2;
    }
    cout << ans << "\n";

    return 0;
}
