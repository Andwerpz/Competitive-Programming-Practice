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

//Codeforces - 1842D

//weird greedy that idk how to prove. 

//start by taking everyone except for person n. Then, play for the maximum amount of time with this group.
//Afterwards, remove anyone that is restricting you from playing (they have a saturated edge to someone that
//is not chosen). Keep playing until person 1 gets unchosen. 

//At least I can see that if infinite playtime is possible (1 and n are disconnected), this will always find it. 
//it's because any node in the component that contains 1 will never be removed, while all nodes in the component 
//containing n will be removed. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvl c(n, vl(n, -1));
    for(int i = 0; i < m; i++){
        int u, v, y;
        cin >> u >> v >> y;
        u --, v --;
        c[u][v] = y, c[v][u] = y;
    }
    bool inf = false;
    ll ans = 0;
    vb v(n, true);
    v[n - 1] = false;
    vl anst;
    vvb ansg;
    while(v[0]) {
        vi in, out;
        for(int i = 0; i < n; i++){
            if(v[i]) in.push_back(i);
            else out.push_back(i);
        }
        ll t = 1e18;
        for(int u : in) for(int v : out) if(c[u][v] != -1) t = min(t, c[u][v]);
        if(t == 1e18) {inf = true; break;}
        ans += t;
        anst.push_back(t);
        ansg.push_back(v);
        for(int u : in) for(int v : out) if(c[u][v] != -1) c[u][v] -= t;
        for(int u : in) {
            bool rm = false;
            for(int v : out) if(c[u][v] == 0) rm = true;
            if(rm) v[u] = false;
        }
    }
    if(inf) {
        cout << "inf\n";
        return 0;
    }
    cout << ans << " " << anst.size() << "\n";
    for(int i = 0; i < anst.size(); i++){
        for(int j = 0; j < n; j++){
            cout << ansg[i][j];
        }
        cout << " " << anst[i] << "\n";
    }
    
    return 0;
}