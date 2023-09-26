#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1863E

//if we pick some start time, lets say 0, we can easily compute the total amount of time required
//to complete all the quests. 

//the problem is that there might exist some other start time that will make completing all the quests faster. 

//note that the optimal start time should be in the range [0, k), as starting at k or after is identical to starting
//somwhere within the first k hours, just mod k. 

//also note that we should also probably start on an hour with a quest that doesn't have any prerequisites. If we
//don't, then we are just stuck doing nothing for the first few hours. 

//let's say there are m quests that don't have any prerequisites, with starting times h[0], h[1], ... h[m - 1]. 
//also, lets say that h is sorted in ascending order. We can try all starting times in h in ascending order
//in linear time to n. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, m, k;
        cin >> n >> m >> k;
        vector<ll> h(n);
        for(int i = 0; i < n; i++){
            cin >> h[i];
        }
        vector<bool> isStart(n, true);
        vector<int> nrDependencies(n, 0);
        vector<vector<int>> children(n, vector<int>(0));
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            nrDependencies[b] ++;
            isStart[b] = false;
            children[a].push_back(b);
        }
        vector<ll> dp(n, 0);    //what day is this quest going to be done?
        queue<int> q;
        for(int i = 0; i < n; i++){
            if(nrDependencies[i] == 0){
                q.push(i);
            }
        }
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < children[cur].size(); i++){
                int next = children[cur][i];
                ll ndp = dp[cur];
                if(h[next] < h[cur]){
                    ndp ++;
                }
                dp[next] = max(dp[next], ndp);
                nrDependencies[next] --;
                if(nrDependencies[next] == 0){
                    q.push(next);
                }
            }
        }
        ll ans = 0;
        ll mxdp = 0;
        ll firstStart = k;
        for(int i = 0; i < n; i++){
            //cout << dp[i] << " ";
            ans = max(ans, dp[i] * k + h[i]);
            if(isStart[i]) {
                firstStart = min(firstStart, h[i]);
            }
        }
        //cout << "\n";
        mxdp = ans;
        ans -= firstStart;
        //cout << firstStart << " " << ans << "\n";
        //check if switching the starting point might give us a better time. 
        vector<pair<ll, int>> sh(n, {0, 0});
        for(int i = 0; i < n; i++){
            sh[i] = {h[i], i};
        }
        sort(sh.begin(), sh.end());
        int pstart = -1;
        for(int i = 0; i < n; i++){
            int ind = sh[i].second;
            if(!isStart[ind]){
                continue;
            }
            if(pstart == -1){
                pstart = ind;
                continue;
            }
            //upd pstart
            queue<int> qu;
            qu.push(pstart);
            dp[pstart] ++;
            while(qu.size() != 0){
                int cur = qu.front();
                qu.pop();
                mxdp = max(mxdp, dp[cur] * k + h[cur]);
                for(int j = 0; j < children[cur].size(); j++){
                    int next = children[cur][j];
                    if(dp[cur] * k + h[cur] > dp[next] * k + h[next]) {
                        while(dp[cur] * k + h[cur] > dp[next] * k + h[next]) {
                            dp[next] ++;
                        }
                        qu.push(next);
                    }
                }
            }
            // for(int j = 0; j < n; j++){
            //     cout << dp[j] << " ";
            // }
            // cout << "\n";
            // cout << "MXDP : " << mxdp << " " << sh[i].first << "\n";
            ans = min(ans, mxdp - sh[i].first);
            pstart = ind;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
