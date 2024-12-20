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

//AtCoder - AGC27C

//In order to be able to make any AB string, we'll need to always be able to transition from the current node, to
//at least one node of both A and B labels. Let's call a node 'good' if you're connected to at least one good
//node of both A and B labels. Note that you're able to create any AB word you want iff there exists good nodes
//in the graph. 

//How do we determine if good nodes exist? We can start by assuming that all nodes are good, then slowly pruning
//away nodes that are actually not good. At the end when we can't prune anymore, the remaining nodes that we assume
//are good are going to be truly good, since we can't prune anymore. 

//To prune, we can just do a topological sort like algorithm. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vvi c(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vb g(n, true);
    vi acnt(n, 0), bcnt(n, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            int next = c[i][j];
            acnt[i] += s[next] == 'A';
            bcnt[i] += s[next] == 'B';
        }
    }
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(min(acnt[i], bcnt[i]) == 0){
            g[i] = false;
            q.push(i);
        }
    }
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(!g[next]) continue;
            acnt[next] -= s[cur] == 'A';
            bcnt[next] -= s[cur] == 'B';
            if(min(acnt[next], bcnt[next]) == 0) {
                g[next] = false;
                q.push(next);
            }
        }
    }
    bool ans = false;
    for(int i = 0; i < n; i++){
        ans = ans || g[i];
    }
    cout << (ans ? "Yes" : "No") << "\n";
    
    return 0;
}