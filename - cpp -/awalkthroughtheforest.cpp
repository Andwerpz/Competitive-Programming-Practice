#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - walkforest

//first, compute distances for all nodes to home. 

//then, we can run dp on all the nodes, in the order of descending distance to home. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n;
    while(n != 0){
        cin >> m;
        vector<vector<pair<int, ll>>> c(n, vector<pair<int, ll>>(0));
        for(int i = 0; i < m; i++){
            int a, b, cost;
            cin >> a >> b >> cost;
            a --;
            b --;
            c[a].push_back({b, cost});
            c[b].push_back({a, cost});
        }
        vector<ll> d(n, 1e18);
        priority_queue<pair<ll, int>> q;    //{-dist, ind};
        q.push({0, 1});
        while(q.size() != 0){
            ll cdist = -q.top().first;
            int cur = q.top().second;
            q.pop();
            if(d[cur] <= cdist) {
                continue;
            }
            d[cur] = cdist;
            for(int i = 0; i < c[cur].size(); i++){
                int next = c[cur][i].first;
                ll ndist = cdist + c[cur][i].second;
                q.push({-ndist, next});
            }
        }
        vector<ll> dp(n, 0);
        dp[0] = 1;
        vector<pair<ll, int>> order(0);
        for(int i = 0; i < n; i++){
            order.push_back({d[i], i});
        }
        sort(order.begin(), order.end());
        reverse(order.begin(), order.end());
        for(int i = 0; i < n; i++){
            int cur = order[i].second;
            // cout << "ORDER : " << cur << " " << d[cur] << "\n";
            for(int j = 0; j < c[cur].size(); j++){
                int next = c[cur][j].first;
                if(d[next] < d[cur]) {
                    dp[next] += dp[cur];
                }
            }
        }
        cout << dp[1] << "\n";
        cin >> n;
    }
    
    return 0;
}
