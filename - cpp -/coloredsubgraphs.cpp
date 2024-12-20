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

//Codeforces - 1796E

//implementation mess
//came up with really inefficient tree rerooting solution.
//seems like editorial had same idea, but with much cleaner implementation. 

//consider rooting the tree, and computing the maximum score coloring. If we know the root, we can solve
//in O(n) using a greedy solution. Any color group has to create a vertical path from some node to one
//of the leaves, so for each subtree root, we can just see which of it's children's vertical paths to continue, 
//and we always want to continue the shortest one. 

//So to solve the actual problem, we can just compute the answer but over all roots and take the maximum. 
//apparently there is an O(n) solution using prefix sums. 

vvi c;
vector<set<int>> miss;
vector<set<pii>> rlens, anss;
map<pii, pii> dp;
pii dfs(int cur, int p) {
    if(dp.count({cur, p})) {
        return dp[{cur, p}];
    }
    while(true){
        auto ptr = miss[cur].begin();
        while(ptr != miss[cur].end() && *ptr == p){
            ptr ++;
        }
        if(ptr == miss[cur].end()){
            break;
        }
        int next = *ptr;
        miss[cur].erase(next);
        pii ret = dfs(next, cur);
        rlens[cur].insert({ret.second, next});
        anss[cur].insert({min(ret.first, ret.second), next});
    }
    //we should have everything in the sets, just have to remove entry corresponding to parent
    if(p != -1 && !miss[cur].count(p)){
        pii ret = dp[{p, cur}];
        rlens[cur].erase({ret.second, p});
        anss[cur].erase({min(ret.first, ret.second), p});
    }
    //find current root len and answer
    int crootlen, cans;
    if(rlens[cur].size() == 0){
        //this is leaf
        crootlen = 0;
        cans = 1e9;
    }
    else {
        //min root len index
        int mrli = rlens[cur].begin()->second;
        crootlen = dp[{mrli, cur}].second;
        cans = dp[{mrli, cur}].first;
        int oans = min(cans, crootlen);
        anss[cur].erase({oans, mrli});
        if(anss[cur].size() != 0){
            cans = min(cans, anss[cur].begin()->first);
        }
        anss[cur].insert({oans, mrli});
    }
    if(p != -1 && !miss[cur].count(p)){
        pii ret = dp[{p, cur}];
        rlens[cur].insert({ret.second, p});
        anss[cur].insert({min(ret.first, ret.second), p});
    }
    crootlen ++;
    dp[{cur, p}] = {cans, crootlen};
    return dp[{cur, p}];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        c = vvi(n);
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        //need to be able to quickly query min ans, and which subtree has min root_len
        miss = vector<set<int>>(n);
        rlens = vector<set<pii>>(n);
        anss = vector<set<pii>>(n);
        dp = map<pii, pii>();   //{{cur, p}, {ans, root len}}
        for(int i = 0; i < n; i++){
            for(int j = 0; j < c[i].size(); j++){
                miss[i].insert(c[i][j]);
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            pii ret = dfs(i, -1);
            ans = max(ans, min(ret.first, ret.second));
        }
        cout << ans << "\n";
    }
    
    return 0;
}