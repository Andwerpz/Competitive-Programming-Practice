#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1436D

//we can first simulate the movements of the citizens, and then the bandit will just go to the leaf node with
//the most citizens. Therefore, we want to try to minimize the maximum amount of citizens that gather in any leaf node.

//to do so, we can kinda simulate it from the leaf upwards. For every node, look at their children and determine where
//the citizens in this node should go. 

//(look at the code, im tired rn D:)

void solve(int cur, vector<vector<int>>& c, vector<ll>& subt_sum, vector<ll>& leaf_cnt, vector<ll>& subt_max, vector<ll>& a) {
    if(c[cur].size() == 0){
        subt_sum[cur] = a[cur];
        leaf_cnt[cur] = 1;
        subt_max[cur] = subt_sum[cur];
        return;
    }
    subt_sum[cur] = a[cur];
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        solve(c[cur][i], c, subt_sum, leaf_cnt, subt_max, a);
        subt_sum[cur] += subt_sum[next];
        leaf_cnt[cur] += leaf_cnt[next];
        subt_max[cur] = max(subt_max[next], subt_max[cur]);
    }
    subt_max[cur] = max(subt_max[cur], (subt_sum[cur] + leaf_cnt[cur] - 1) / leaf_cnt[cur]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int p;
        cin >> p;
        p --;
        c[p].push_back(i + 1);
    }
    vector<ll> subt_sum(n, 0), leaf_cnt(n, 0), subt_max(n, 0), a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    solve(0, c, subt_sum, leaf_cnt, subt_max, a);
    cout << subt_max[0] << "\n";
    
    return 0;
}