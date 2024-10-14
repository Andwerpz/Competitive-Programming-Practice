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

//Codeforces - 19E

//seemingly hard problem turned seemingly easy, which then turns seemingly hard again as you disregard all
//of the edge cases. 

//We can solve this using DFS trees. Do a dfs traversal through the graph, and color it according to the 
//span edges. Then, backedges are the only ones that can 'break' our coloring. 

//it's safe to remove a backedge only if it's the only one that's breaking the coloring. Otherwise, we can only 
//remove span edges. 

//it's safe to remove a span edge if the set of backedges that go over it is exactly the set of backedges that
//is breaking the coloring. 

//be careful of the graph not being initially connected. 

void dfs(int cur, int par, vvi& c, vi& v, vi& color, vector<pii>& elist, vi& ocnt, vi& p, int& vcnt, vi& vlist) {
    v[cur] = vcnt ++;
    p[cur] = par;
    vlist.push_back(cur);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == par){
            continue;
        }
        if(v[next] == -1) {
            color[next] = color[cur] ^ 1;
            dfs(next, cur, c, v, color, elist, ocnt, p, vcnt, vlist);
        }
        else if(v[next] < v[cur]) {
            if(color[next] == color[cur]) {
                elist.push_back({next, cur});
                ocnt[cur] ++;
                ocnt[next] --;
            }
            else {
                ocnt[cur] += 1e4 + 100;
                ocnt[next] -= 1e4 + 100;
            }
        }
    }
    if(par != -1){
        ocnt[par] += ocnt[cur];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi c(n);
    map<pii, int> indmp;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
        indmp[{a, b}] = i;
        indmp[{b, a}] = i;
    }
    vi ans(0);
    vi v(n, -1), color(n, 0), ocnt(n, 0), p(n);
    vector<pii> elist(0);
    int vcnt = 0;
    for(int i = 0; i < n; i++){
        if(v[i] != -1){
            continue;
        }
        vi vlist(0);
        dfs(i, -1, c, v, color, elist, ocnt, p, vcnt, vlist);
    }
    if(elist.size() == 0){
        for(int i = 0; i < m; i++){
            ans.push_back(i);
        }
    }
    else {
        if(elist.size() == 1){
            ans.push_back(indmp[elist[0]]);
        }
        for(int i = 0; i < n; i++){
            if(ocnt[i] == elist.size()) {
                ans.push_back(indmp[{i, p[i]}]);
            }
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] + 1 << " ";
    }
    cout << "\n";
    
    return 0;
}