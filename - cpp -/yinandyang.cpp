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

//USACO 2013 US Open, Gold - Problem 2

//classic divide and conquer with centroid decomposition. 
//was rather tricky to implement

//idea is that for each centroid, we'll compute the number of good paths going through and ending on
//the centroid. When considering a centroid, we can root the tree at the centroid. 

//for each node, we'll consider it good if on the path from the node to the root, we can place a rest stop.
//We'll record all such 'good' nodes in d2. Otherwise, we'll record bad nodes in d1. 

//then, any good node can match to good or bad nodes in other subtrees (with matching distance of course), 
//but a bad node can only match to good nodes in other subtrees. 

//also need to specially consider paths from each node to the root. 

const int N = 100005;
int n;
vector<pii> c[N];
bool v[N];
int sz[N];
ll d1[2 * N], d2[2 * N], cd[2 * N];
int mn_depth, mx_depth;

int calc_centroid(int cur, int p, int desire) {
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i].first;
        if(next == p || v[next]) continue;
        if(sz[next] > desire) return calc_centroid(next, cur, desire);
    }
    return cur;
}

int calc_sz(int cur, int p) {
    sz[cur] = 1;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i].first;
        if(next == p || v[next]) continue;
        sz[cur] += calc_sz(next, cur);
    }
    return sz[cur];
}

//calc contribution from nodes with dist != 0
ll dfs(int cur, int p, int dist) {
    mn_depth = min(mn_depth, dist);
    mx_depth = max(mx_depth, dist);
    ll ans = 0;
    if(cd[N + dist] == 0) ans += d2[N - dist];
    else ans += d1[N - dist] + d2[N - dist];
    if(dist == 0 && cd[N + 0] > 1) ans ++;  //to centroid
    cd[N + dist] ++;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i].first;
        if(next == p || v[next]) continue;
        ans += dfs(next, cur, dist + c[cur][i].second);
    }
    cd[N + dist] --;
    return ans;
}

void dfs_pop(int cur, int p, int dist) {
    if(cd[N + dist] != 0) d2[N + dist] ++;
    else d1[N + dist] ++;
    cd[N + dist] ++;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i].first;
        if(next == p || v[next]) continue;
        dfs_pop(next, cur, dist + c[cur][i].second);
    }
    cd[N + dist] --;
}

ll solve(int cur) {
    cur = calc_centroid(cur, -1, calc_sz(cur, -1) / 2);
    v[cur] = true;
    ll ans = 0;
    cd[N + 0] = 1;
    mn_depth = 0;
    mx_depth = 0;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i].first;
        if(v[next]) continue;
        ans += dfs(next, cur, c[cur][i].second);
        dfs_pop(next, cur, c[cur][i].second);
    }
    for(int i = mn_depth; i <= mx_depth; i++){
        d1[N + i] = 0;
        d2[N + i] = 0;
        cd[N + i] = 0;
    }
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i].first;
        if(v[next]) continue;
        ans += solve(next);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    freopen("yinyang.in", "r", stdin);
    freopen("yinyang.out", "w", stdout);

    cin >> n;
    for(int i = 0; i < n - 1; i++){
        int u, v, t;
        cin >> u >> v >> t;
        u --;
        v --;
        if(t == 0) t = -1;
        c[u].push_back({v, t});
        c[v].push_back({u, t});
    }
    cout << solve(0) << "\n";
    
    return 0;
}