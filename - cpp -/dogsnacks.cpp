#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1453E

//i initially misread the problem; i didn't think that there was a biscuit on every node, only on specific
//nodes. Having a biscuit on every node makes the problem much easier. 

//Under these rules, when Badugi enters a subtree, he will not leave it until every biscuit in that subtree is eaten
//Therefore, for every subtree, we want to minimize the distance from the subtree root to the last biscuit that
//is eaten in the subtree. 

//to do so, we can rearrange the order in which we visit the children of each node. In the general case, we want
//to save the child which has minimum distance to it's last node for last. 

//The only edge case is the root node. As it doesn't have a parent, we don't need to minimize the distance to the 
//last biscuit, instead we want to minimize the overall maximum distance. Therefore, for the root, we save the maximum
//distance for last. 


//returns the distance between this node and the last node visited in this subtree
int solve(int cur, int p, vector<vector<int>>& c, int& ans) {
    vector<int> d(0);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        d.push_back(solve(next, cur, c, ans) + 1);
    }
    if(d.size() == 0){
        //this is leaf
        return 0;
    }
    sort(d.begin(), d.end());
    int c_ans;
    if(p == -1){
        //this is the root
        //choose subtree with largest final dist to go last. 
        //every other subtree will have 1 extra cost
        reverse(d.begin(), d.end());
        c_ans = d[0];
        for(int i = 1; i < d.size(); i++){
            c_ans = max(c_ans, d[i] + 1);
        }
        ans = max(ans, c_ans);
    }
    else {
        //this is parent of some subtree
        //choose the subtree with the smallest final dist to go last
        //every other subtree with have 1 extra cost
        c_ans = d[0];
        for(int i = 1; i < d.size(); i++){
            ans = max(ans, d[i] + 1);
        }
    }
    return c_ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        int ans = 1;
        solve(0, -1, c, ans);
        cout << ans << "\n";
    }
    
    return 0;
}
