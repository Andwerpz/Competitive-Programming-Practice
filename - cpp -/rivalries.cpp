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

//Mines HSPC 2025 Open Division - O

//observe the graph consists of a bunch of cycles and trees hanging off of the cycles. We're tasked with finding some maximum
//matching on the graph. 

//maximum matching on trees can be solved in linear time using dp. To solve for each cycle, we need to see if we want to match cycle
//nodes or not. We can do dp on each cycle. Keep in mind that the cycle is cyclic, so you have to also shift all the nodes over by 
//1 and do dp again to properly try everything. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi p(n);
    for(int i = 0; i < n; i++) cin >> p[i];
    for(int i = 0; i < n; i++) p[i] --;
    vvi c(n);
    for(int i = 0; i < n; i++) c[p[i]].push_back(i);
    vb iscyc(n, false);
    vvi cyc(0);
    vb v(n, false);
    for(int i = 0; i < n; i++){
        // cout << "I : " << i << "\n";
        int ptr = i;
        vi path;
        while(!v[ptr]) path.push_back(ptr), v[ptr] = true, ptr = p[ptr];
        int cycind = -1;
        for(int j = 0; j < path.size(); j++) if(path[j] == ptr) cycind = j;
        if(cycind != -1) {
            vi yc;
            for(int j = cycind; j < path.size(); j++) {
                yc.push_back(path[j]);
                iscyc[path[j]] = true;
            }
            cyc.push_back(yc);
        }
        // cout << "PATH : ";
        // for(int x : path) cout << x << " ";
        // cout << "\n";
    }
    vvi dp(n, vi(2, -1));    //max amount of pairings in subtree given that root is/isnot paired
    function<int(int, int)> dfs = [&](int cur, int pai) -> int {
        if(dp[cur][pai] != -1) return dp[cur][pai];
        int ans = 0;
        int nopais = 0;
        for(int x : c[cur]) if(!iscyc[x]) nopais += dfs(x, 0);
        ans = max(ans, nopais);
        if(!pai) {
            for(int x : c[cur]) if(!iscyc[x]) ans = max(ans, nopais - dfs(x, 0) + dfs(x, 1) + 1);
        }
        dp[cur][pai] = ans;
        return ans;
    };
    int ans = 0;
    for(int i = 0; i < cyc.size(); i++){
        vi cy = cyc[i];
        // cout << "CY : ";
        // for(int x : cy) cout << x << " ";
        // cout << "\n";
        for(int x : cy) dfs(x, 0), dfs(x, 1);
        int cans = 0;
        for(int j = 0; j < 2; j++) {
            vi dp2(cy.size() + 1, 0);
            for(int j = 0; j < cy.size(); j++){
                dp2[j + 1] = max(dp2[j + 1], dp2[j] + dp[cy[j]][0]);
                if(j + 2 <= cy.size()) dp2[j + 2] = max(dp2[j + 2], dp2[j] + dp[cy[j]][1] + dp[cy[j + 1]][1] + 1);
            }
            cans = max(cans, dp2[cy.size()]);
            vi tmp(cy.size());
            for(int i = 0; i < cy.size(); i++) tmp[(i + 1) % cy.size()] = cy[i];
            cy = tmp;
        }
        ans += cans;
    }
    cout << n - 2 * ans << "\n";
    
    return 0;
}