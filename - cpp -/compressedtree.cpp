#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1901E

//i read the editorial to solve this problem, but i still have no idea how someone would have come up with 
//this solution. 
//UPDATE: after sleeping, i can kind of see how someone would come up with this.

//since the number of connections to the node determines whether or not it is in the final compressed tree, 
//we want to solve for each node's subtree while controlling the number of connections. Since we also want
//to root the tree somewhere, we'll have to return two answers with some conditions:
// - current node and parent node has to remain
// - ans has to be max in current node's subtree; cannot depend on parent node. 

//then, we can write a recursive function to solve. 

pair<ll, ll> solve(int cur, int p, vector<vector<int>>& c, vector<ll>& a) { //{ans with this and parent node, max ans in subt}
    pair<ll, ll> ans = {-1e16, 0};
    vector<pair<ll, ll>> c_ans(0);
    ll first_sum = 0;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        c_ans.push_back(solve(next, cur, c, a));
    }
    sort(c_ans.begin(), c_ans.end());
    reverse(c_ans.begin(), c_ans.end());
    //calc first ans
    if(p != -1){
        //remove all children
        {
            ll cur_ans = a[cur];
            ans.first = max(ans.first, cur_ans);
        }
        //remove all but 1 child
        if(c_ans.size() >= 1){
            ll cur_ans = c_ans[0].first;
            ans.first = max(ans.first, cur_ans);
        }
        //leave 2 or more children
        if(c_ans.size() >= 2) {
            ll cur_ans = c_ans[0].first + c_ans[1].first + a[cur];
            for(int i = 2; i < c_ans.size(); i++){
                if(c_ans[i].first < 0){
                    break;
                }
                cur_ans += c_ans[i].first;
            }
            ans.first = max(ans.first, cur_ans);
        }
    }
    //calc second ans
    {   
        //take max ans out of all children
        {
            for(int i = 0; i < c_ans.size(); i++){
                ans.second = max(ans.second, c_ans[i].second);
            }
        }
        //remove all children
        {
            ans.second = max(ans.second, a[cur]);
        }
        //remove all but 1 child
        if(c_ans.size() >= 1){
            ll cur_ans = c_ans[0].first + a[cur];
            ans.second = max(ans.second, cur_ans);
        }
        //remove all but 2 children
        if(c_ans.size() >= 2) {
            ll cur_ans = c_ans[0].first + c_ans[1].first;
            ans.second = max(ans.second, cur_ans);
        }
        //leave 3 or more children
        if(c_ans.size() >= 3) {
            ll cur_ans = c_ans[0].first + c_ans[1].first + c_ans[2].first + a[cur];
            for(int i = 3; i < c_ans.size(); i++){
                if(c_ans[i].first < 0){
                    break;
                }
                cur_ans += c_ans[i].first;
            }
            ans.second = max(ans.second, cur_ans);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
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
        cout << solve(0, -1, c, a).second << "\n";
    }
    
    return 0;
}
