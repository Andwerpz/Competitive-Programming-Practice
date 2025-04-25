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

//Rutgers University Programming Contest Spring 2025 - F

//First, when is it always possible to make a string? If there exists a red-blue alternating cycle, then it's always possible,
//otherwise there exists some impossible string. 

//We can detect whether or not there exists some red-blue alternating cycle using some toposort-like algorithm. 

//Once we determine it's impossible, we need to find the minimal impossible string. Here, I assumed that the minimum impossible
//string will always be alternating (RBRB...). We can then just do dp (dfs) on the graph starting from each node, dp[i][c] = 
//maximum alternating path length starting at node i with color c. Since there doesn't exist a red-blue alternating cycle, 
//processing dp[i][c] should never return us back to dp[i][c], as that would imply the existence of an alternating cycle. 

vvi cr, cb;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        cr = vvi(n), cb = vvi(n);
        for(int i = 0; i < m; i++){
            int u, v;
            string c;
            cin >> u >> v >> c;
            u --, v --;
            if(c == "R") cr[u].push_back(v), cr[v].push_back(u);
            else cb[u].push_back(v), cb[v].push_back(u);
        }
        //determine whether or not it's impossible
        queue<int> q;
        vi ri(n, 0), bi(n, 0);
        vb v(n, false);
        for(int i = 0; i < n; i++){
            for(int x : cr[i]) ri[x] ++;
            for(int x : cb[i]) bi[x] ++;
        }
        for(int i = 0; i < n; i++) if(min(ri[i], bi[i]) == 0) q.push(i), v[i] = true;
        while(q.size() != 0) {
            int cur = q.front();
            q.pop();
            // cout << "CUR : " << cur << "\n";
            ri[cur] = 0, bi[cur] = 0;
            for(int x : cr[cur]) {
                if(v[x]) continue;
                ri[x] --;
                if(ri[x] == 0 && !v[x]) q.push(x), v[x] = true;
            }
            for(int x : cb[cur]) {
                if(v[x]) continue;
                bi[x] --;
                if(bi[x] == 0 && !v[x]) q.push(x), v[x] = true;
            }
        }
        bool impos = true;
        for(int i = 0; i < n; i++) if(min(ri[i], bi[i])) impos = false;
        if(!impos) {
            cout << "-1\n";
            continue;
        }
        //it's impossible, find minimum string, just do dfs
        vi rdp(n, -1), bdp(n, -1);
        function<int(int, int)> dfs = [&](int cur, int col) -> int {
            // cout << "DFS : " << cur << " " << col << endl;
            if(col == 0) {
                if(rdp[cur] != -1) return rdp[cur];
                int ans = 0;
                for(int x : cr[cur]) ans = max(ans, 1 + dfs(x, 1));
                rdp[cur] = ans;
                return ans;
            }
            else {
                if(bdp[cur] != -1) return bdp[cur];
                int ans = 0;
                for(int x : cb[cur]) ans = max(ans, 1 + dfs(x, 0));
                bdp[cur] = ans;
                return ans;
            }
        };
        int rans = 0, bans = 0;
        for(int i = 0; i < n; i++){
            rans = max(rans, dfs(i, 0)), bans = max(bans, dfs(i, 1));
        }
        rans ++, bans ++;
        if(rans < bans) {
            for(int i = 0; i < rans; i++) {
                cout << (i % 2 == 0? "R" : "B");
            }
            cout << "\n";
        }
        else {
            for(int i = 0; i < bans; i++){
                cout << (i % 2 == 0? "B" : "R");
            }
            cout << "\n";
        }
    }
    
    return 0;
}