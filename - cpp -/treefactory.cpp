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

//Codeforces - 1225F

//guessed the solution, now to prove it

//a bamboo blank is essentially just a chain or linked list. 
//instead of building the tree from the bamboo blank, we'll build the bamboo blank from the tree, and 
//just reverse the operations. 

//to create the bamboo blank from the tree, my idea is to use a DFS traversal. The idea is whenever we go
//deeper into the tree, we should use an operation, and when we return from a subtree, we just record the root
//of the subtree we've left as the target for the next operation. The only times we don't have to use an operation 
//is on our first descent into the tree, as we don't have a subtree root recorded yet. This is why we want to
//visit the deepest node on our first descent. 

void solve(int cur, vvi& c, vi& move, vi& label, int& lastup) {
    for(int next : c[cur]) {
        if(lastup != -1) move.push_back(lastup);
        solve(next, c, move, label, lastup);
    }
    label.push_back(cur);
    lastup = cur;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi p(n, -1);
    for(int i = 1; i < n; i++){
        cin >> p[i];
    }
    vvi c(n);
    for(int i = 1; i < n; i++){
        c[p[i]].push_back(i);
    }
    //find deepest node
    vi d(n, 0);
    function<void(int)> dfs = [&](int cur) -> void { 
        for(int x : c[cur]) {
            d[x] = d[cur] + 1;
            dfs(x);
        }
    };
    dfs(0);
    int deep = 0;
    for(int i = 0; i < n; i++){
        if(d[i] > d[deep]) deep = i;
    }
    //rearrange adj list such that deepest node is visited first in dfs traversal
    int ptr = deep;
    while(p[ptr] != -1) {
        int par = p[ptr];
        sort(c[par].begin(), c[par].end(), [&](int a, int b) -> bool {
            return a == ptr;
        });
        ptr = par;
    }
    //solve problem
    vi move(0), label(0);
    int lastup = -1;
    solve(0, c, move, label, lastup);
    reverse(label.begin(), label.end());
    reverse(move.begin(), move.end());
    for(int i = 0; i < n; i++){
        cout << label[i] << " ";
    }
    cout << "\n";
    cout << move.size() << "\n";
    for(int i = 0; i < move.size(); i++){
        cout << move[i] << " ";
    }
    cout << "\n";
    
    return 0;
}