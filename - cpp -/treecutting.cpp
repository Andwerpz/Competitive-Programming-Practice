#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1946C

//we can binary search for the maximum x. 
//lets root the tree at an arbitrary node. Then, perform dfs on this rooted tree. 

//for each node, we want to return the number of 'free' nodes in it's subtree. A free node is a node that is
//still connected to the root. 

//Before returning, if the number of free nodes in the subtree is >= x, then we want to disconnect this subtree from the root,
//increasing the number of edges removed by 1, but reducing the number of free nodes to 0. 

//seems like it doesn't matter what node we root the tree at, it works regardless. 

//{nr edges removed, nr free nodes in subt}
pair<int, int> dfs(int cur, int p, vector<vector<int>>& c, int x) {
    pair<int, int> ans = {0, 0};
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        pair<int, int> n_ans = dfs(next, cur, c, x);
        ans.first += n_ans.first;
        ans.second += n_ans.second;
    }
    ans.second ++;
    if(ans.second >= x){
        ans.first ++;
        ans.second = 0;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        int low = 1;
        int high = n;
        int ans = 1;
        while(low <= high){
            int mid = low + (high - low) / 2;
            if(dfs(0, -1, c, mid).first >= k + 1) {
                ans = max(ans, mid);
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
