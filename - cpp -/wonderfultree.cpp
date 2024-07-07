#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1987E

//we can do a bottom up solution. This guarantees that whenever we're trying to fix a node, all of it's children 
//are already wonderful. 

//To fix a node, we want to increment it's children so that the sum of children becomes equal to the current
//node's value. Notice that unless the node we're incrementing is a leaf node, by incrementing the child we're
//making it not wonderful, so we'll have to increment one of it's children as well. 

//we'll get to stop incrementing if we hit a leaf node, or some node that is already greater than the sum of it's
//children. Note that we want to greedily stop at the earliest node possible, as the cost associated with a single
//increment is equal to the distance between the node we're fixing and the 'sink' node that we find. 

//To find sink nodes, we can just do a naive dfs. Notice that fixing a node is amortized O(n), even if we implement
//O(n) dfs, as if we find a non-leaf node, we either exhaust it, which prevents it from becoming a sink node again,
//or we fix the current node. Of course, if we find a leaf node, then it's impossible to exhaust. 

pair<int, int> dfs(int cur, vector<vector<int>>& c, vector<ll>& left, int cdist) {
    //minimize dist, don't care about anything else
    if(left[cur] != 0){
        return {cdist, cur};
    }
    pair<int, int> ans = {1e9, 1e9};
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        ans = min(ans, dfs(next, c, left, cdist + 1));
    }
    return ans;
}

ll fix(int cur, vector<vector<int>>& c, vector<ll>& a, vector<ll>& left) {
    //first fix all children
    ll ans = 0;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        ans += fix(next, c, a, left);
    }
    //leaf node
    if(c[cur].size() == 0){
        left[cur] = 1e18;
        return 0;
    }
    //see if we are initially good
    ll csum = 0;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        csum += a[next];
    }
    if(csum >= a[cur]) {
        left[cur] = csum - a[cur];
        return ans;
    }
    //otherwise, we'll need to increment children to become good
    while(a[cur] > csum) {
        pair<int, int> _dfs = dfs(cur, c, left, 0);
        int ind = _dfs.second;
        ll dist = _dfs.first;
        ll amt = min(a[cur] - csum, left[ind]);
        left[ind] -= amt;
        csum += amt;
        ans += amt * dist;
    }
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
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 1; i < n; i++){
            int p;
            cin >> p;
            p --;
            c[p].push_back(i);
        }
        vector<ll> left(n, 0);
        cout << fix(0, c, a, left) << "\n";
    }
    
    return 0;
}