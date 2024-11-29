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

//CSES - 2081

//extension to fixed length paths 1 solution, also storing suffix sums of the d array. We do suffix sums because
//that way we can update only the first cmx_depth elements every time we dfs.  

const int N = 200005;
bool v[N];
ll d[N];
ll sfx[N];
int sz[N];
vector<int> c[N];
int mx_depth, cmx_depth, n, k1, k2;

ll dfs1(int cur, int par, int dist) {
    if(dist > k2) return 0;
    ll ans = sfx[max(0, k1 - dist)] - sfx[k2 - dist];
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == par || v[next]) continue;
        ans += dfs1(next, cur, dist + 1);
    }
    return ans;
}

void dadd(int cur, int par, int dist) {
    if(dist > k2) return;
    d[dist] ++;  
    mx_depth = max(mx_depth, dist);
    cmx_depth = max(cmx_depth, dist);
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
        cmx_depth = 0;
        ans += dfs1(next, cur, 1);
        dadd(next, cur, 1);
        for(int j = cmx_depth; j >= 0; j--){
            sfx[j] = sfx[j + 1] + d[j];
        }
    }
    fill(d + 1, d + mx_depth + 1, 0);
    fill(sfx + 1, sfx + mx_depth + 1, 0);
    sfx[0] = 1;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(!v[next]) ans += dfs2(next);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n >> k1 >> k2;
    k2 ++;
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    d[0] = 1;
    sfx[0] = 1;
    ll ans = dfs2(0);
    cout << ans << "\n";
    
    return 0;
}