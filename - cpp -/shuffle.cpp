#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1984E

//everytime you select a node to be a root, it can no longer be a leaf (except if you select the first node
//and it's a leaf, then it will end up being a leaf). So, we want to select the minimum amount of nodes
//as possible to become roots, so that the remaining nodes will become leaves. This is identical to
//minimum vertex cover.

//one important caveat is that you are able to pick a leaf as the initial root, and that gives you a 'free' 
//leaf. So instead of solving minimum vertex cover directly, you need to find the minimum vertex cover, if 
//one leaf node has been removed. 

//This implementation finds the maximum independent set in the tree, which is pretty much the complement of 
//minimum vertex cover in trees (i think). 

int solve(vector<vector<vector<int>>>& dp, vector<vector<int>>& c, int cur, int p, bool in_set, bool m_leaf) {
    if(dp[cur][in_set][m_leaf] != -1){
        return dp[cur][in_set][m_leaf];
    }
    int ans = 0;
    if(c[cur].size() == 1){
        if(m_leaf) {
            ans = 0;
        }
        else {
            ans = in_set;
        }
    }
    else {
        if(in_set) {
            ans ++;
        }
        if(m_leaf) {
            //exactly one of our children has to be missing a leaf
            vector<pair<int, int>> n_vals(0);   //{not missing, missing}
            if(in_set) {
                //none of our children can be in the set
                for(int i = 0; i < c[cur].size(); i++){
                    int next = c[cur][i];
                    if(next == p){
                        continue;
                    }
                    n_vals.push_back({solve(dp, c, next, cur, false, false), solve(dp, c, next, cur, false, true)});
                }
            }
            else {
                //it doesn't matter if our children are in the set
                for(int i = 0; i < c[cur].size(); i++){
                    int next = c[cur][i];
                    if(next == p){
                        continue;
                    }
                    int not_miss = max(solve(dp, c, next, cur, false, false), solve(dp, c, next, cur, true, false));
                    int miss = max(solve(dp, c, next, cur, false, true), solve(dp, c, next, cur, true, true));
                    n_vals.push_back({not_miss, miss});
                }
            }
            int nmiss_sum = 0;
            for(int i = 0; i < n_vals.size(); i++){
                nmiss_sum += n_vals[i].first;
            }
            int bans = 0;
            for(int i = 0; i < n_vals.size(); i++){
                bans = max(bans, ans + nmiss_sum - n_vals[i].first + n_vals[i].second);
            }
            ans = bans;
        }
        else {
            //operate normally
            if(in_set) {
                for(int i = 0; i < c[cur].size(); i++){
                    int next = c[cur][i];
                    if(next == p){
                        continue;
                    }
                    ans += solve(dp, c, next, cur, false, false);
                }
            }
            else {
                for(int i = 0; i < c[cur].size(); i++){
                    int next = c[cur][i];
                    if(next == p){
                        continue;
                    }
                    ans += max(solve(dp, c, next, cur, false, false), solve(dp, c, next, cur, true, false));
                }
            }
        }
    }
    dp[cur][in_set][m_leaf] = ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> c(n);
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        if(n == 2){
            cout << "2\n";
            continue;
        }
        //find some node in the tree that isn't a leaf
        int not_leaf = -1;
        for(int i = 0; i < n; i++){
            if(c[i].size() != 1){
                not_leaf = i;
                break;
            }
        }
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2, -1)));
        int ans = 1 + max(solve(dp, c, not_leaf, -1, true, true), solve(dp, c, not_leaf, -1, false, true));
        cout << ans << "\n";
    }
    
    return 0;
}