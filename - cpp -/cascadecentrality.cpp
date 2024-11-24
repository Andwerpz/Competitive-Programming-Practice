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

//2024 NA Mid Central Regional - D

//bruh, if n >= 10^5, then it would be a nice rerooting problem, but nooo, n = 100. 

const int N = 1000;
int sz[N];

int calc_sz(int cur, int p, vvi& c) {
    sz[cur] = 1;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p) continue;
        sz[cur] += calc_sz(next, cur, c);
    }
    return sz[cur];
}

ld dfs(int cur, int p, vvi& c, ld seq) {
    seq /= c[cur].size();
    ld ans = seq;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p) continue;
        ans += dfs(next, cur, c, seq);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi c(n);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    ld sum = 0;
    for(int i = 0; i < n; i++){
        calc_sz(i, -1, c);
        for(int j = 0; j < c[i].size(); j++){
            sum += dfs(c[i][j], i, c, 1);
        }
        sum += 1;
    }
    cout << fixed << setprecision(10) << sum / n << "\n";
    
    return 0;
}