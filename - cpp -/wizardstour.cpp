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

//Codeforces - 858F

//we want to pair up the edges such that each pair of edges has one node in common, and we
//get the maximum amount of pairs. 

//consider the case when the graph is a tree. If there are n nodes, then I claim that i can always 
//make floor(n / 2) pairs no matter the structure of the tree. 

//finally, we can convert the general case into a tree using DFS tree technique. For backedges, we can consider
//making a 'clone' of the node that it connects. It doesn't matter which node we clone, just that we convert it into
//a tree. 

void dfs(int cur, int par, vvi& c, vi& p, vector<set<int>>& cset, vi& v) {
    p[cur] = par;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(v[next] == -1) {
            v[next] = v[cur] + 1;
            dfs(next, cur, c, p, cset, v);
        }
        else if(v[next] < v[cur]){
            cset[next].insert(cur);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi c(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    vi p(n), v(n, -1);
    vector<set<int>> cset(n, set<int>());
    for(int i = 0; i < n; i++){
        if(v[i] != -1){
            continue;
        }
        v[i] = 0;
        dfs(i, -1, c, p, cset, v);
    }
    vi indeg(n, 0);
    for(int i = 0; i < n; i++){
        if(cset[i].size() != 0 && p[i] != -1){
            indeg[p[i]] ++;
        }
    }
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(cset[i].size() != 0 && indeg[i] == 0){
            q.push(i);
        }
    }
    vvi ans(0);
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        auto ptr = cset[cur].begin();
        for(int i = 0; i < cset[cur].size() / 2; i++){
            int a = *ptr;
            ptr ++;
            int b = *ptr;
            ptr ++;
            ans.push_back({a, cur, b});
        }
        if(p[cur] != -1){
            indeg[p[cur]] --;
            if(indeg[p[cur]] == 0){
                q.push(p[cur]);
            }
            if(ptr != cset[cur].end()){
                int a = *ptr;
                ans.push_back({a, cur, p[cur]});
                cset[p[cur]].erase(cur);
            }
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i][0] + 1 << " " << ans[i][1] + 1 << " " << ans[i][2] + 1 << "\n";
    }
    
    return 0;
}