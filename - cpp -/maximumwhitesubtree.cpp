#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1324F

//first, we can arbitrarily root the tree. Then, solve the simpler question; what is the maximum difference of white
//to black nodes in every *rooted* subtree? This can be easily solved using one pass of dfs. Denote subt[i] as the 
//maximum difference of white to black nodes in the subtree rooted at node i in the rooted tree. 

//of course, this doesn't solve the original problem, but note that if the tree is rooted at node r, then subt[r]
//is actually the answer for node r for the original problem. For the remaining nodes, we need to supplement subt[i]
//with information from their parent. 

//specifically, we need to know what's the maximum number of white nodes we can gain from expanding to the parent. 
//if you think about this, this can also be done in one pass of dfs. 

vector<int> a;

void dfs1(int cur, int p, vector<vector<int>>& c, vector<int>& subt_max) {
    subt_max[cur] = a[cur];
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        dfs1(next, cur, c, subt_max);
        subt_max[cur] += max(subt_max[next], 0);
    }
}

void dfs2(int cur, int p, vector<vector<int>>& c, vector<int>& subt_max, int p_max, vector<int>& ans) {
    ans[cur] = subt_max[cur] + max(p_max, 0);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        int np_max = max(p_max, 0) + subt_max[cur] - max(subt_max[next], 0);
        dfs2(next, cur, c, subt_max, np_max, ans);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    a = vector<int>(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] == 0) {
            a[i] = -1;
        }
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
    //root the tree at node 1, and compute the maximum score taking subtree for each node
    vector<int> subt_max(n, -1);
    dfs1(0, -1, c, subt_max);
    //now, compute the actual answer for each node
    vector<int> ans(n, -1);
    dfs2(0, -1, c, subt_max, 0, ans);
    for(int i = 0; i < n; i++){
        cout << ans[i] << " \n"[i == n - 1];
    }
    
    return 0;
}