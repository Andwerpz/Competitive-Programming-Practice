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

//AtCoder - AGC14D

//we can prove that the second player will win iff there exists a perfect matching on the tree. 

//it's obvious that if there exists a perfect matching, the second player will win. When the first 
//player colors a node, the second just has to color the corresponding matched node, and therefore
//any white node will be adjacent to a black node. 

//if a perfect matching does not exist, the first player always wins. We can follow this strategy:
// - root the tree arbitrarily
// - choose the deepest leaf and it's parent. Color the parent white, and the second player is forced to color
//   the leaf black, as if they don't, the first player can win by coloring the leaf white. 
// - remove the two colored nodes from the tree
// - repeat

//since a perfect matching does not exist, eventually there will be a leaf with no parents, and the first
//player can just color that node white. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    if(n % 2) {
        cout << "First\n";
        return 0;
    }
    bool first = false;
    vi indeg(n, 0);
    vb v(n, false);
    queue<int> q;
    for(int i = 0; i < n; i++){
        indeg[i] = c[i].size();
        if(indeg[i] == 1) q.push(i);
    }
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        if(v[cur]) continue;
        int other = -1;
        for(int x : c[cur]) if(!v[x]) {other = x; break;}
        if(other == -1) break;
        v[cur] = true, v[other] = true;
        for(int x : c[other]) {
            if(v[x]) continue;
            indeg[x] --;
            if(indeg[x] == 1) q.push(x);
        }
    }
    for(bool x : v) if(!x) first = true;
    cout << (first? "First" : "Second") << "\n";
    
    return 0;
}