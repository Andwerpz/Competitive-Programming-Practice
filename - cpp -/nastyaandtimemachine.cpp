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

//Codeforces - 1341F

//constructive tree problem. 

//idea is to do an euler tour of the tree, while locally minimizing the time at each node. 
//the key is when we visit a subtree with time t, we always want to enforce that we return to 
//the root with time t + 1. 

//to enforce the above, we need to make sure that we leave the current node for the parent with t
//one less than what we arrived with. Trivially, this is always possible if we just wait until the end
//and set our time to 1 less than what we arrived with (and ofc we start with t >= 1, which should be true
//for all except the tree root). 

//however, this might not actually minimize the time. To minimize the time, note we sometimes can use the time
//machine before we've visited all our children, especially when the starting time is high. Since the amount
//of time gain when visiting each child is predictable, we can easily tell when to activate the time machine early.

//ig i left out the proof that this minimizes the maximum time. I claim that the maximum time this
//traversal produces is equal to the maximum degree of any node - 1. Since this is the best you can do, this
//algorithm is optimal. 

void dfs(int cur, int p, vvi& c, vector<pii>& path, int t) {
    path.push_back({cur, t});
    int st = t;
    int left = c[cur].size() - 1;
    if(st != 0 && st - left - 1 >= 0 && t >= st){
        path.push_back({cur, st - left - 1});
        t = st - left - 1;
    }
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p) continue;
        dfs(next, cur, c, path, t + 1);
        t ++;
        path.push_back({cur, t});
        left --;
        if(st != 0 && st - left - 1 >= 0 && t >= st){
            path.push_back({cur, st - left - 1});
            t = st - left - 1;
        }
    }
    if(st != 0 && t >= st){
        path.push_back({cur, st - 1});
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    if(n == 1){
        cout << "1\n";
        cout << "1 0\n";
        return 0;
    }
    vector<pii> path;
    dfs(0, -1, c, path, 0);
    cout << path.size() << "\n";
    for(pii x : path){
        cout << x.first + 1 << " " << x.second << "\n";
    }

    return 0;
}