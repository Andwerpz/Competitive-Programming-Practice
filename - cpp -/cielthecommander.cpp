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

//Codeforces - 321C

//if we take the centroid decomposition of the tree, the maximum height will be around log(n), so we can just assign the ranks
//to the layers of the tree. 

const int N = 200001;
int sz[N];
bool v[N];
int ans[N];
vector<int> c[N];

int find_centroid(int cur, int p, int desire) {
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(p != next && !v[next] && sz[next] >= desire) return find_centroid(next, cur, desire);
    }
    return cur;
}

int calc_sz(int cur, int p) {
    sz[cur] = 1;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(p != next && !v[next]) sz[cur] += calc_sz(next, cur);
    }
    return sz[cur];
}

void centroid_decomp(int cur, int layer) {
    calc_sz(cur, -1);
    cur = find_centroid(cur, -1, sz[cur] / 2);
    ans[cur] = layer;
    v[cur] = true;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(!v[next]) centroid_decomp(next, layer + 1);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    centroid_decomp(0, 0);
    for(int i = 0; i < n; i++){
        cout << (char) ('A' + ans[i]) << " ";
    }
    cout << "\n";
    
    return 0;
}