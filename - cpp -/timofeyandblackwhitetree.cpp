#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1790F

//something, something, ... dfs?
//centroid decomposition should also work. 

int dfs(int cur, int p, vector<int>& min_dist, vector<bool>& black, vector<vector<int>>& c, int ans) {
    if(min_dist[cur] >= ans) {
        return ans;
    }
    if(black[cur]){
        ans = min(ans, min_dist[cur]);
    }
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        ans = min(ans, min_dist[cur] + 1 + min_dist[next]);
        if(min_dist[next] > min_dist[cur] + 1) {
            min_dist[next] = min_dist[cur] + 1;
            ans = min(ans, dfs(next, cur, min_dist, black, c, ans));
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- ){
        int n, rem_0;
        cin >> n >> rem_0;
        rem_0 --;
        vector<int> rem(n - 1);
        for(int i = 0; i < n - 1; i++){
            cin >> rem[i];
            rem[i] --;
        }
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        vector<bool> black(n, false);
        vector<int> v(n, -1);
        vector<int> min_dist(n, 1e9);
        //init min_dist
        min_dist[rem_0] = 0;
        int ans = n - 1;
        dfs(rem_0, -1, min_dist, black, c, ans);
        black[rem_0] = true;
        for(int i = 0; i < n - 1; i++){
            min_dist[rem[i]] = 0;
            ans = dfs(rem[i], -1, min_dist, black, c, ans);
            black[rem[i]] = true;
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
