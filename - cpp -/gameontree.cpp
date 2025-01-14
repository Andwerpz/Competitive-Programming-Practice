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

//AtCoder - AGC17D

//we can root the tree at node 1 and make some observations on how to compute the grundy numbers. 

//first if there are multiple subtrees connected to the root, then we can consider them seperately
//and xor them together. 

//second, if the root has exactly 1 child, we can compute the grundy number as 1 + the grundy number
//of just the child subtree itself. We can prove this using induction. 

//therefore, we can compute the grundy number using a single dfs. 

int calc_g(int cur, int p, vvi& c){
    int g = 0;
    for(int x : c[cur]) if(x != p) g ^= calc_g(x, cur, c) + 1;
    return g;
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
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    cout << (calc_g(0, -1, c)? "Alice" : "Bob") << "\n";
    
    return 0;
}