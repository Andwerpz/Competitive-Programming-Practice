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

//Codeforces - 2025F

//first, ignore the requirement that after every query the values must be non-negative. If at the end
//the values are non-negative, we can simply rearrange where we add and subtract to make it so that
//after every query everything is non-negative. 

//we can reinterpret the problem as a graph problem. We are given n nodes and q undirected edges, the 
//ith edge being between x[i] and y[i]. We want to direct the edges such that the amount of nodes
//with odd indegree is minimized. 

//directing edges is analagous to picking x or y to increment, and nodes with even indegree mean that
//we can equally assign '+' and '-' operations so that the final value is 0. This is why we want to
//minimize odd indegree nodes, because then the final value has to be 1. 

//We can first randomly direct every edge, then for every connected component, find the MST. Then, we can
//process the nodes from the leaf to the root: if the current node has odd indegree, we can simply 
//invert the direction of the edge from the current node to it's parent, and the current node
//will have even indegree. Therefore, in every connected component, the maximum amount of nodes
//with odd indegree after minimizing is 1 (the root). 

//finally, we can choose for each edge to add or subtract, and print the answer. 

void dfs(int cur, int p, int p_eind, vector<vector<pii>>& c, vb& tx, vb& v, vb& indeg) {
    v[cur] = true;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i].first;
        int eind = c[cur][i].second;
        if(next == p || v[next]){
            continue;
        }
        dfs(next, cur, eind, c, tx, v, indeg);
    }
    if(p != -1){
        if(indeg[cur]) {
            indeg[cur] = !indeg[cur];
            indeg[p] = !indeg[p];
            tx[p_eind] = !tx[p_eind];
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<pii> e(q);
    vb tx(q, true), pos(q, true);
    vector<vector<pii>> c(n);   //{node, eind}
    vb indeg(n, false);
    for(int i = 0; i < q; i++){
        int x, y;
        cin >> x >> y;
        x --;
        y --;
        indeg[x] = !indeg[x];
        c[x].push_back({y, i});
        c[y].push_back({x, i});
        e[i] = {x, y};
    }
    //for each component, find MST and reduce amount of odd indeg nodes as much as possible.
    vb v(n, false);
    for(int i = 0; i < n; i++){
        if(v[i]){
            continue;
        }
        dfs(i, -1, -1, c, tx, v, indeg);
    }
    //for each node, find what edges go into it
    vvi inc(n);
    for(int i = 0; i < q; i++){
        if(tx[i]) {
            inc[e[i].first].push_back(i);
        }
        else {
            inc[e[i].second].push_back(i);
        }
    }
    //build answer (determine which edges are positive or negative)
    for(int i = 0; i < n; i++){
        reverse(inc[i].begin(), inc[i].end());
        for(int j = 0; j < inc[i].size() / 2; j++){
            pos[inc[i][j]] = false;
        }
    }
    for(int i = 0; i < q; i++){
        cout << (tx[i]? "x" : "y") << (pos[i]? "+" : "-") << "\n";
    }
    
    return 0;
}