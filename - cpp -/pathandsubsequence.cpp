#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC150C

//let's say that dp[i] is the minimum index in B that you can be when you arrive at node i starting from
//node 1. Initialize all dp to k + 1, and the base case is dp[0], which is 0 or 1 depending on a[0] == b[0].

//when updating the dp, we'll do it using a dijstra like bfs; pick the node with the minimum dp value that
//hasn't been updated yet, and update all of it's neighboring nodes. 

//the answer is in dp[n], where if dp[n] is k, you should print 'Yes'. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    vector<int> dp(n, k + 1);
    vector<int> a(n, 0);
    vector<int> b(k, 0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < k; i++){
        cin >> b[i];
    }
    priority_queue<pair<int, int>> q;    //-dp[i], i
    q.push({-(b[0] == a[0]), 0});
    while(q.size()) {
        int cur = q.top().second;
        int dp_val = -q.top().first;
        q.pop();
        if(dp_val >= dp[cur]) {
            continue;
        }
        dp[cur] = dp_val;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            int n_dp = dp[cur];
            if(n_dp < k && b[n_dp] == a[next]) {
                n_dp ++;
            }
            if(n_dp < dp[next]) {
                q.push({-n_dp, next});
            }
        }
    }
    cout << (dp[n - 1] == k? "Yes\n" : "No\n");
    
    return 0;
}
