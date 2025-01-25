#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Kattis - joinstrings

//can represent the joins as edges in a directed rooted tree. 
//just do dfs through the tree. 

void dfs(int cur, vvi& c, vector<string>& a) {
    cout << a[cur];
    for(int x : c[cur]) dfs(x, c, a);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> s(n);
    for(int i = 0; i < n; i++) cin >> s[i];
    vi deg(n, 0);
    vvi c(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a --, b --;
        c[a].push_back(b);
        deg[b] ++;
    }
    int root = -1;
    for(int i = 0; i < n; i++) if(deg[i] == 0) root = i;
    dfs(root, c, s);
    cout << "\n";
    
    return 0;
}