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

//Kattis - perfectpathpatrol
//2020 ICPC NAQ

//the graph given is a tree. If you look at the leaves, they only have one outgoing edge, so you know that
//exactly that many patrols must have an endpoint at that leaf. 

//then, looking at the parent of leaves, you can choose to merge the paths coming in from the leaves, 
//however you should first use the leaf paths to send them to your own parent, as merging paths saves you
//one path, while reusing them saves you two paths. 

//this motivates a recursive solution. 

ll solve(vector<vector<pii>>& c, int cur, int par, int topar) {
    vl le(0);
    ll ans = 0;
    for(pii x : c[cur]) {
        if(x.first == par) continue;
        le.push_back(x.second);
        ans += solve(c, x.first, cur, x.second);
    }
    if(le.size() == 0) {
        return topar;
    }
    sort(le.begin(), le.end());
    reverse(le.begin(), le.end());
    ll lesum = 0;
    for(ll x : le) lesum += x;
    ll mxrm = 0;
    if(le[0] * 2 > lesum) mxrm = lesum - le[0];
    else mxrm = lesum / 2;
    ans += max(0ll, topar - lesum);
    lesum = max(0ll, lesum - topar);
    ans -= min(mxrm, lesum / 2);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<pii>> c(n);
    vi deg(n, 0);
    for(int i = 0; i < n - 1; i++) {
        int u, v, p;
        cin >> u >> v >> p;
        c[u].push_back({v, p});
        c[v].push_back({u, p});
        deg[u] ++;
        deg[v] ++;
    }
    ll ans = solve(c, 0, -1, 0);
    cout << ans << "\n";
    
    return 0;
}