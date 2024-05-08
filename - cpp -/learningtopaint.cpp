#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1942D

//to find the k highest values, it might be useful to think about how to find 'the' highest value. 
//we can do this with dp. dp[i] = max value in the ith prefix. Transitions are O(n). 

//Now, to compute the k highest values, we can just save for every dp[i], the k highest values. 
//the problem is now how is this going to run in time. Every transition is O(nk), and we have n states, so
//O(n^2 * k), which is > 10^9. 

//we can be clever here. Note that for dp[i], we only need to save the k highest values, so ideally it would only
//take O(k) to compute every state. Therefore, instead of forwards propogating, we can instead look from the perspective
//of dp[i]. Out of all the states that it could have come from, we take the highest value, and then take the next highest
//value, and so on for k times. Once we're done, then we'll have computed dp[i] in k steps. 

//to do this, we can use a priority queue. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<vector<int>> a(n + 1, vector<int>(0));
        for(int i = 0; i <= n; i++){
            a[i].push_back(0);
            for(int j = 0; j < n - i; j++){
                int next;
                cin >> next;
                a[i].push_back(next);
            }
        }
        vector<vector<int>> dp(n + 2, vector<int>(0));
        dp[0].push_back(0);
        for(int i = 1; i < n + 2; i++){
            priority_queue<pair<int, pair<int, int>>> q;
            for(int j = 0; j < i; j++){
                int val = dp[j][0] + a[j][i - j - 1];
                q.push({val, {j, 0}});
            }
            for(int j = 0; j < k && q.size() != 0; j++){
                int which = q.top().second.first;
                int it = q.top().second.second;
                int val = q.top().first;
                q.pop();
                dp[i].push_back(val);
                it ++;
                if(it != dp[which].size()) {
                    q.push({dp[which][it] + a[which][i - which - 1], {which, it}});
                }
            }
        }
        for(int i = 0; i < k; i++){
            cout << dp[n + 1][i] << " \n"[i == k - 1];
        }
    }
    
    return 0;
}
