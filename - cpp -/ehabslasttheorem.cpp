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

//Codeforces - 1325F

//we can use a DFS tree approach. First, do a dfs traversal, and for each node, note all of its
//backedges (including the edge to its parent). 

//if there exists a node with sqrt(n) or more backedges, then this node will always be part of a 
//cycle with sqrt(n) or more nodes, due to pidegonhole. 

//however, if there doesn't exist a node with sqrt(n) backedges, then it's always possible to create
//an independent set of size sqrt(n), using a topological sort like technique on the backedge graph.
//since we can guarantee that selecting a node will only eliminate at most sqrt(n) nodes, then
//at minimum we can select sqrt(n) nodes. 

void dfs(int cur, int par, vvi& c, vvi& t, vvi& back, vi& v, vi& p) {
    p[cur] = par;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(v[next] == -1){
            v[next] = v[cur] + 1;
            t[cur].push_back(next);
            dfs(next, cur, c, t, back, v, p);
        }
        else if(v[next] < v[cur]) {
            back[cur].push_back(next);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi c(n), t(n), back(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    vi p(n), v(n, -1);
    v[0] = 0;
    dfs(0, -1, c, t, back, v, p);
    int rn = ceil(sqrt(n));
    for(int i = 0; i < n; i++){
        if(back[i].size() >= rn - 1) {
            int ptr = i;
            vi cy(0);
            int mn_back = i;
            for(int j = 0; j < back[i].size(); j++){
                if(v[mn_back] > v[back[i][j]]){
                    mn_back = back[i][j];
                }
            }
            cy.push_back(ptr);
            while(ptr != mn_back) {
                ptr = p[ptr];
                cy.push_back(ptr);
            }
            cout << "2\n" << cy.size() << "\n";
            for(int i = 0; i < cy.size(); i++){
                cout << cy[i] + 1 << " ";
            }
            cout << "\n";
            return 0;
        }
    }
    vi indeg(n, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < back[i].size(); j++){
            indeg[back[i][j]] ++;
        }
    }
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(indeg[i] == 0){
            q.push(i);
        }
    }
    vi ans(0);
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        if(ans.size() < rn) {
            ans.push_back(cur);
        }
        for(int i = 0; i < back[cur].size(); i++){
            int next = back[cur][i];
            for(int j = 0; j < back[next].size(); j++){
                int nnext = back[next][j];
                indeg[nnext] --;
                if(indeg[nnext] == 0){
                    q.push(nnext);
                }
            }
        }
    }
    cout << "1\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] + 1 << " ";
    }
    cout << "\n";
    
    return 0;
}