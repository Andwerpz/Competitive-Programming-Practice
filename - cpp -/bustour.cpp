#include <bits/stdc++.h>
#pragma GCC optimize("O3")
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;
using namespace chrono;

//ICPC World Finals 2012 - C

//holy moly, this one took a bit to get right. 
//when solving bitset dp problems, always use the looping. 

int unv = 1e8;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    int tcnt = 0;
    while(!cin.eof() && n != -1){
        tcnt ++;
        int h = n - 2;
        vector<vector<int>> dp0((1 << h), vector<int>(n, unv));
        vector<vector<int>> dp1((1 << h), vector<int>(n, unv));
        vector<vector<int>> adj(n, vector<int>(n, 1e9));
        for(int i = 0; i < m; i++){
            int u, v, t;
            cin >> u >> v >> t;
            adj[u][v] = t;
            adj[v][u] = t;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                for(int k = 0; k < n; k++){
                    adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
                    adj[j][i] = min(adj[j][i], adj[j][k] + adj[k][i]);
                }
            }
        }
        for(int i = 0; i < (1 << h); i++){
            if(__builtin_popcount(i) == 1){
                int cur = -1;
                for(int j = 0; j < h; j++){
                    if(i & (1 << j)) {
                        cur = j;
                        break;
                    }
                }
                dp0[i][cur] = adj[0][cur + 1];
                dp1[i][cur] = adj[n - 1][cur + 1];
                continue;
            }
            for(int j = 0; j < h; j++){
                //you must end at hotel j
                if((i & (1 << j)) == 0){
                    continue;
                }
                for(int k = 0; k < h; k++){
                    if(k == j){
                        continue;
                    }
                    if((i & (1 << k)) == 0){
                        continue;
                    }
                    //we can come from this state
                    dp0[i][j] = min(dp0[i][j], dp0[i ^ (1 << j)][k] + adj[k + 1][j + 1]);
                    dp1[i][j] = min(dp1[i][j], dp1[i ^ (1 << j)][k] + adj[k + 1][j + 1]);
                }
            }
        }
        //extract answer from dp
        int nr_prio = h / 2;
        int ans = 1e9;
        for(int i = 0; i < (1 << h); i++){
            if(__builtin_popcount(i) != nr_prio) {
                continue;
            }
            int bits = i;
            int cbits = 0;
            for(int j = 0; j < h; j++){
                if((bits & (1 << j)) == 0){
                    cbits += (1 << j);
                }
            }
            for(int j = 0; j < h; j++){
                for(int k = 0; k < h; k++){
                    if((bits & (1 << j)) == 0) {
                        continue;
                    }
                    if((bits & (1 << k)) == 0){
                        continue;
                    }
                    int cans = 0;
                    cans += dp0[bits][j];
                    cans += dp1[cbits | (1 << j)][j];
                    cans += dp1[bits][k];
                    cans += dp0[cbits | (1 << k)][k];
                    ans = min(ans, cans);
                }
            }
        }
        if(n == 3){
            ans = (adj[0][1] + adj[1][2]) * 2;
        }
        cout << "Case " << tcnt << ": " << ans << "\n";
        cin >> n >> m;
    }
    
    return 0;
}
