#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 2138 C1 C2

//bitset intended?? actually intended is O(n * sqrt(n))

//observe that the longest we can ever make the LCA is equal to the depth of the least deep leaf. 
//actually, if we fill up the nodes in BFS order with 1s and the rest 0s, it always results in a LCA of at least
//depth of least deep leaf - 1, so we just have to figure out if it's possible to fill up every layer
//with exactly the same values. 

//To do this, we just have to do knapsack to see if we can create some value in [k - E, k] using the layer counts
//above the minimum depth. For easy version, n^2 knapsack is fine, and for hard version, bitset n^2 knapsack works. 

//you can actually do knapsack in n * sqrt(n), just have to observe that if you have 3 elements of the same value x,
//then you can replace the three with one element of value x and one of value 2x. Then, for each value there can only
//be at most 2 elements of that value, the number of total elements is limited to around sqrt(n)

void dfs(int cur, int p, vvi& c, vi& d) {
    for(int x : c[cur]) {
        d[x] = d[cur] + 1;
        dfs(x, cur, c, d);
    }
}

const int N = 1e5 + 1;
bitset<N> dp;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vvi c(n);
        for(int i = 1; i < n; i++) {
            int par;
            cin >> par;
            par --;
            c[par].push_back(i);
        }
        vi d(n);
        dfs(0, -1, c, d);
        int min_leaf = 1e9;
        for(int i = 0; i < n; i++) {
            if(c[i].size() == 0) min_leaf = min(min_leaf, d[i]);
        }
        min_leaf ++;
        vi lcnt(1, 1);
        {
            vi l(1, 0);
            while(l.size() != 0) {
                vi nl;
                for(int x : l) for(int xx : c[x]) nl.push_back(xx);
                l = nl;
                lcnt.push_back(nl.size());
            }
        }
        //do knapsack
        int dpn = min(k, n - k);
        dp &= 0;
        dp[0] = 1;
        for(int i = min_leaf - 1; i >= 0; i--){
            int val = lcnt[i];
            dp |= (dp << val);
        }
        int extra = 0;
        for(int i = min_leaf; i < lcnt.size(); i++) extra += lcnt[i];
        int ans = min_leaf - 1;
        for(int i = 0; i <= extra; i++) {
            if(dpn - i < 0) break;
            if(dp[dpn - i]) {
                ans ++;
                break;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}