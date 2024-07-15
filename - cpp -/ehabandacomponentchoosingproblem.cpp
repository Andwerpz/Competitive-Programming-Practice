#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1088E

//the problem is worded very weirdly. You're supposed to select k connected components in the tree, such that 
//each node is in at most 1 component. Note that the components do not need to partition the tree, so there can
//exist nodes that are not in any component. The goal is to maximize the sum of selected nodes divided by the amount 
//of components. 

//first, notice that each component that you select should have the same sum. If you ever have components of 
//different sum, you can always remove the component with the lowest sum to increase the value of the fraction. 

//second, since you want to maximize the fraction, you would therefore want to pick components with the largest
//sum possible. So the problem boils down to finding the maximum number of disjoint components you can pick such that
//each component has the largest sum possible within the tree. 

//finding the largest sum possible isn't too bad, we can simply root the tree, then solve for the largest sum in each
//subtree, then the answer is the largest sum on the root. 

//finding the maximum amount of components with the largest sum is a little trickier though, and idk how my solution
//works. It's pretty much the same as finding the largest sum, but once we find one, we just subtract it from the 
//subtree sum, and continue as normal. Just have to count the number of times we subtract. 

void solve(int cur, int p, vector<vector<int>>& c, vector<pll>& mcmp, vector<ll>& a) {
    pll ans = {a[cur], a[cur]};
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        solve(next, cur, c, mcmp, a);
        ans.first = max(ans.first, mcmp[next].first);
        if(mcmp[next].second >= 0) {
            ans.second += mcmp[next].second;
        }
    }
    ans.first = max(ans.first, ans.second);
    // cout << "SOLVE : " << cur << " " << ans.first << " " << ans.second << "\n";
    mcmp[cur] = ans;
}

int solve2(int cur, int p, vector<vector<int>>& c, vector<pll>& mcmp, vector<ll>& a, ll mx) {
    int cnt = 0;
    pll ans = {a[cur], a[cur]};
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        cnt += solve2(next, cur, c, mcmp, a, mx);
        ans.first = max(ans.first, mcmp[next].first);
        if(mcmp[next].second >= 0) {
            ans.second += mcmp[next].second;
        }
    }
    ans.first = max(ans.first, ans.second);
    if(ans.second == mx) {
        ans.second = 0;
        cnt ++;
    }
    // cout << "SOLVE : " << cur << " " << ans.first << " " << ans.second << "\n";
    mcmp[cur] = ans;
    return cnt;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<int>> c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    vector<pll> mcmp(n);    //{subt max, subt max including this}
    solve(0, -1, c, mcmp, a);
    ll mx = mcmp[0].first;
    ll cnt = solve2(0, -1, c, mcmp, a, mx);
    cout << mx * cnt << " " << cnt << "\n";
    
    return 0;
}