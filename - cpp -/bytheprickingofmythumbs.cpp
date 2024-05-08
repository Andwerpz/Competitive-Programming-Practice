#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC Contest 03-22-24 Div. 1 - D

//just do a dfs through the tree, rooted at node 0. For each node, determine if this node knows anyone we need to
//remove, or if it knows anyone who knows something (that we need to know). Count all such nodes. 

int solve(int cur, int p, vector<vector<int>>& c, vector<int>& r){
    int ans = 0;
    bool knows = false;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        if(r[next] >= r[0]) {
            knows = true;
        }
        ans += solve(next, cur, c, r);
    }
    if(ans != 0){
        knows = true;
    }
    if(knows && cur != 0){
        ans ++;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> r(n);
    for(int i = 0; i < n; i++){
        cin >> r[i];
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
    cout << solve(0, -1, c, r) << "\n";
    
    return 0;
}
