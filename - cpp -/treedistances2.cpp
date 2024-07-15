#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//CSES - 1133

//lets say we have the answer to some node A, which is ans[A], and there exists an edge from A -> B. 
//now, we want to compute the answer to B, ans[B]. 

//when we traverse along the edge A -> B, we increase the distance to every node in the A subtree by 1,
//and decrease the distance to every node in the B subtree by 1. Thus, if we know the sizes of every 
//subtree, we can compute each answer in constant time. 

//If we root the tree arbitrarily, it's pretty easy to see how we can know the sizes of each subtree. 

void dfs1(int cur, int p, vector<vector<int>>& c, vector<int>& depth, vector<int>& subt) {
    subt[cur] = 1;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        depth[next] = depth[cur] + 1;
        dfs1(next, cur, c, depth, subt);
        subt[cur] += subt[next];
    }
}

void dfs2(int cur, int p, vector<vector<int>>& c, vector<int>& subt, ll cans, vector<ll>& ans) {
    int n = c.size();
    ans[cur] = cans;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        dfs2(next, cur, c, subt, cans + n - 2 * subt[next], ans);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vector<int> depth(n), subt(n);
    vector<ll> ans(n);
    dfs1(0, -1, c, depth, subt);
    ll cans = 0;
    for(int i = 0; i < n; i++) {
        cans += depth[i];
    }
    dfs2(0, -1, c, subt, cans, ans);
    for(int i = 0; i < n; i++){
        cout << ans[i] << " \n"[i == n - 1];
    }
    
    return 0;
}