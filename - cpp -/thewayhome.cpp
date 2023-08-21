#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1801D

//we can think of this like a dp problem, then apply shortest path algorithm to it. 

//let dp[i][j] = {minimum number of performances, maximum number of leftover money} where 
//i = current node
//j = node with maximum profit per performance that we've visited on the current path. 

//the transitions between the states should be pretty obvious. What is not obvious is what we should optimize for
//in each dp state, since we are storing two competing values. It can be proven that it is always optimal to 
//minimize the number of performances first, before maximizing the amount of leftover money. 

//return true if a is better than b
bool better(pair<ll, ll>& a, pair<ll, ll>& b) {
    if(a.first != b.first) {
        return a.first < b.first;
    }
    return a.second > b.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, p;
        cin >> n >> m >> p;
        vector<ll> w(n);
        for(int i = 0; i < n; i++){
            cin >> w[i];
        }
        vector<vector<pair<int, ll>>> c(n, vector<pair<int, ll>>(0));
        for(int i = 0; i < m; i++){
            int a, b, cost;
            cin >> a >> b >> cost;
            a --;
            b --;
            c[a].push_back({b, cost});
        }
        vector<vector<pair<ll, ll>>> dp(n, vector<pair<ll, ll>>(n, {1e18, 0}));
        dp[0][0] = {0, p};
        queue<pair<pair<int, int>, pair<ll, ll>>> q;
        q.push({{0, 0}, dp[0][0]});
        ll ans = 1e18;
        while(q.size() != 0){
            int curind = q.front().first.first;
            int maxind = q.front().first.second;
            pair<ll, ll> curval = q.front().second;
            q.pop();
            if(curval != dp[curind][maxind]) {
                continue;
            }
            //cout << curind << " " << maxind << " " << curval.first << " " << curval.second << "\n";
            if(curind == n - 1){
                ans = min(ans, curval.first);
            }
            for(int i = 0; i < c[curind].size(); i++){
                int next = c[curind][i].first;
                ll cost = c[curind][i].second;
                int nextmaxind = w[next] > w[maxind]? next : maxind;
                ll nextperf = curval.first;
                ll nextmoney = curval.second - cost;
                if(nextmoney < 0){
                    ll perf = abs(nextmoney) / w[maxind] + (abs(nextmoney) % w[maxind] == 0? 0 : 1);
                    nextperf += perf;
                    nextmoney += perf * w[maxind];
                }
                pair<ll, ll> nextval = {nextperf, nextmoney};
                if(better(nextval, dp[next][nextmaxind])) {
                    dp[next][nextmaxind] = nextval;
                    q.push({{next, nextmaxind}, nextval});
                }
            }
        }
        if(ans == 1e18){
            ans = -1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
