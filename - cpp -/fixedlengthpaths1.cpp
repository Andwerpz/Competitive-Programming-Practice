#pragma GCC optimize("O2")
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

//CSES - 2080

//whew, had to go to constant factor school for this one. 
//big idea is to compute for each node, the number of k-paths going through it. Naively, this would 
//take n^2, as we can compute this value for one node in O(n). 

//the idea to speed it up is to apply centroid decomposition in a divide and conquer fashion. To solve some 
//tree, we first compute the number of k-paths going through the centroid, then we remove the centroid and then solve
//for the remaining components. 

//apparently there's a linear time solution??

const int N = 200001;
bool v[N];
ll d[N];
int sz[N];
vector<int> c[N];
int mx_depth, n, k;

ll dfs1(int cur, int par, int dist) {
    if(dist > k) return 0;
    ll ans = dist <= k? d[k - dist] : 0;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == par || v[next]) continue;
        ans += dfs1(next, cur, dist + 1);
    }
    return ans;
}

void dadd(int cur, int par, int dist) {
    if(dist > k) return;
    d[dist] ++;  
    mx_depth = max(mx_depth, dist);
    for(int i = 0; i < c[cur].size(); i++) {
        int next = c[cur][i];
        if(next == par || v[next]) continue;
        dadd(next, cur, dist + 1);
    }
}

int calc_sz(int cur, int par) {
    int ans = 1;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(par == next || v[next]) continue;
        ans += calc_sz(next, cur);
    }
    sz[cur] = ans;
    return ans;
}

int find_centroid(int cur, int par, int desired) {
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(!v[next] && next != par && sz[next] >= desired) {
            return find_centroid(next, cur, desired);
        }
    }
    return cur;
}

ll dfs2(int cur) {
    //find centroid of current component
    calc_sz(cur, -1);
    int centroid = find_centroid(cur, -1, sz[cur] >> 1);
    //compute how many paths of length k are going through this node
    cur = centroid;
    v[cur] = true;
    ll ans = 0;
    mx_depth = 0;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(v[next]) continue;
        ans += dfs1(next, cur, 1);
        dadd(next, cur, 1);
    }
    fill(d + 1, d + mx_depth + 1, 0);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(!v[next]) ans += dfs2(next);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n >> k;
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    d[0] = 1;
    ll ans = dfs2(0);
    cout << ans << "\n";
    
    return 0;
}