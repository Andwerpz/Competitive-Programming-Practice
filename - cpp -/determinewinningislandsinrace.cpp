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

//Codeforces - 1998D

//consider some starting position s. Since Bessie can only follow a fixed track towards island n, lets consider what 
//it would mean if Ellie is able to win. Ellie can win if she can ever hop to an island that is in front of Bessie. 
//If Bessie starts at s, and Ellie can win, it means that there must be some auxillary bridge that connects an island
//before s to some island in front of s, and that Ellie has enough time to travel to that bridge and use it to get in
//front of Bessie. 

//for each island, we can compute the minimum time for Ellie to get there using dp. Then, we can consider each starting
//point from 1 to n. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vvi c(n);
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        for(int i = 0; i < n - 1; i++){
            c[i].push_back(i + 1);
            c[i + 1].push_back(i);
        }
        int mx_sup = -1;
        vi mint(n, 1e9);
        mint[0] = 0;
        vb ans(n, true);
        for(int i = 0; i < n; i++){
            //determine if bessie can win here
            ans[i] = mx_sup < i;
            //compute mint[i]
            for(int j = 0; j < c[i].size(); j++){
                int next = c[i][j];
                if(next >= i){
                    continue;
                }
                mint[i] = min(mint[i], mint[next] + 1);
            }
            //update mx_sup
            for(int j = 0; j < c[i].size(); j++){
                int next = c[i][j];
                if(next <= i + 1) {
                    continue;
                }
                mx_sup = max(mx_sup, next - mint[i] - 2);
            }
        }
        for(int i = 0; i < n - 1; i++){
            cout << ans[i];
        }
        cout << "\n";
    }
    
    return 0;
}