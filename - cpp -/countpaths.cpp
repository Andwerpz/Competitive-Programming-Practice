#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

void dfs(int cur, int p, vector<vector<int>>& c, vector<ll>& nr_child, vector<int>& lsc, vector<int>& color) {
    if(lsc[color[cur]] != -1) {
        nr_child[lsc[color[cur]]] ++;
    }
    int p_lsc = lsc[color[cur]];
    lsc[color[cur]] = cur;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        dfs(next, cur, c, nr_child, lsc, color);
    }
    lsc[color[cur]] = p_lsc;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> color(n);
        for(int i = 0; i < n; i++){
            cin >> color[i];
            color[i] --;
        }
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        vector<ll> nr_child(n, 0);
        vector<int> lsc(n, -1);
        dfs(0, -1, c, nr_child, lsc, color);
        ll ans = 0;
        for(int i = 0; i < n; i++){
            cout << nr_child[i] << "\n";
            ans += nr_child[i] * (nr_child[i] + 1) / 2;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
