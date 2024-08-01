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

//Codeforces - 1592C

//denote the xor sum of all the nodes as xsum. If xsum == 0, then we can remove any edge and the two remaining
//connected components will have equal xor sum, since x ^ x = 0 (and trivially, x = x). 

//otherwise, xsum != 0. In this case, lets say we can successfully partition the tree into q components, each with 
//xor sum x. We observe that the xor sum of the total tree must be x ^ x ^ ... (q times), and since it is non-zero,
//q must be odd, which means that xsum = x. We can easily compute the maximum amount of subtrees we can cut off with
//xor sum = x with a dfs. 

//since q is odd, the constraint on the amount of edges we can cut actually matters. In this case, if k > 2, then it
//always works. This is because we can always reduce the answer by 2 by merging 3 components into 1. 

int dfs(int cur, int p, vvi& c, vi& a, int& cnt, int tgt){
    int xsum = a[cur];
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        xsum ^= dfs(next, cur, c, a, cnt, tgt);
    }
    if(xsum == tgt){
        cnt ++;
        xsum = 0;
    }
    return xsum;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vvi c(n);
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        int xsum = 0;
        for(int i = 0; i < n; i++){
            xsum ^= a[i];
        }
        if(xsum == 0){
            cout << "YES\n";
            continue;
        }
        int cnt = 0;
        dfs(0, -1, c, a, cnt, xsum);
        cout << (cnt != 1 && k > 2? "YES" : "NO") << "\n";
    }
    
    return 0;
}