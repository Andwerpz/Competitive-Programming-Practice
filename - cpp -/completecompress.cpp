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

//AtCoder - AGC34E

//We can fix some node as the root, and then check if it's possible to move all the tokens to the root. 
//If we can check some root in O(n), then our entire solution will be O(n^2). 

//First, I claim that all moves we perform will select two tokens and move them both towards the root. 
//Note that for two tokens to move towards the root, one node cannot be the ancestor of the other node.
//So essentially each operation, we want to select two nodes from different subtrees and move them both 
//closer to the root. 

//How can we better model this problem? We can see that each subtree from the root will have a sum of 
//distances for all tokens. In one operation we can choose two subtrees and decrease their distance sums
//by 1, and we're done when distance sums of all subtrees are 0. So we can see that a sequence of moves is 
//always possible if the maximum distance subtree is <= half of total distance, and the total distance
//is divisible by 2. 

//However, if the above conditions do not hold, it still may be possible, specifically with the condition that 
//the max distance sum is <= half total distance. It may be possible that within the max subtree, we can select
//two nodes within it that are in different subtrees, and therefore reduce the distance of the max subtree by 2. 

//{total, req, amt}
array<int, 3> check_valid(int cur, int p, vvi& c, string& s) {
    int tot = 0, mx_req = 0, mx_tot = 0, amt = s[cur] - '0';
    for(int x : c[cur]) {
        if(x == p) continue;
        array<int, 3> tmp = check_valid(x, cur, c, s);
        tot += tmp[0];
        if(tmp[1] > mx_req) {
            mx_req = tmp[1], mx_tot = tmp[0];
        }
        amt += tmp[2];
    }
    int req = max(0, mx_req - (tot - mx_tot));
    if(p != -1) req += amt, tot += amt;
    return {tot, req, amt};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    vvi c(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    int ans = 1e9;
    for(int i = 0; i < n; i++) {
        array<int, 3> tmp = check_valid(i, -1, c, s);
        if(tmp[0] % 2 == 0 && tmp[1] == 0) ans = min(ans, tmp[0] / 2);
    }
    cout << (ans == 1e9? -1 : ans) << "\n";
    
    return 0;
}