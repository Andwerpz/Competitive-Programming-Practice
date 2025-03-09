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

//UTPC Contest 2-26-25 Div.1 - F

//the given graph is a tree. 

//root the tree at node n, then compute the euler tour through the tree that visits all the marked nodes. 
//Then, subtract the distance from node 1 to n. Make sure to mark node 1. 

int calc_subt(int cur, int p, vvi& c, vi& subt, string& s, vi& d) {
    subt[cur] = s[cur] - '0';
    for(int x : c[cur]) if(x != p) d[x] = d[cur] + 1, subt[cur] += calc_subt(x, cur, c, subt, s, d);
    return subt[cur];
}

int tour_len(int cur, int p, vvi& c, vi& subt) {
    int ans = 0;
    for(int x : c[cur]) if(x != p && subt[x]) ans += 2 + tour_len(x, cur, c, subt);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    s[n - 1] = '1';
    s[0] = '1';
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vi subt(n, 0), d(n, -1);
    d[n - 1] = 0;
    calc_subt(n - 1, -1, c, subt, s, d);
    // cout << "SUBT : ";
    // for(int i = 0; i < n; i++) cout << subt[i] << " ";
    // cout << "\n";
    int ans = tour_len(n - 1, -1, c, subt);
    // cout << "TOUR : " << ans << "\n";
    ans -= d[0];
    cout << ans << "\n";
    
    return 0;
}