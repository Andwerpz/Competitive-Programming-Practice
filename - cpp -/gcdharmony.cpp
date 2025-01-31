#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//2022 ICPC NAC - E

const int MAXV = 1000, N = 5000;
int f[N][MAXV + 1], a[N];
vector<int> c[N], cv[MAXV + 1];
void dfs(int v, int p, int val) {
    if(f[v][val] != -1) return;
    int ans = 0;
    if(val != a[v]) ans += val;
    for(int x : c[v]) {
        if(x == p) continue;
        int mn_nxt = 1e9;
        for(int nval : cv[val]) {
            if(f[x][nval] == -1) dfs(x, v, nval);
            mn_nxt = min(mn_nxt, f[x][nval]);
        }
        ans += mn_nxt;
        ans = min(ans, (int) 1e9);
    }
    f[v][val] = ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < N; i++) {
        for(int j = 0; j <= MAXV; j++){
            f[i][j] = -1;
        }
    }
    int n; cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n - 1; ++i) {
        ll a, b; cin >> a >> b;
        a --, b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    for (int i = 1; i <= MAXV; ++i) {
        for(int j = 1; j <= MAXV; j++) {
            if(gcd(i, j) != 1) cv[i].push_back(j);
        }
    }
    for(int i = 1; i <= MAXV; i++){
        dfs(0, -1, i);
    }
    int ans = 1e9;
    for(int i = 1; i <= MAXV; i++) ans = min(ans, f[0][i]);
    cout << ans << "\n";
    
    return 0;
}