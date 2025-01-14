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

//AtCoder - AGC4D

//the graph given is a functional graph with exactly 1 cycle. In order for us to ensure that each node
//is exactly k successors away from node 1, the cycle must be of length 1. 

//so the problem boils down to this:
//given a rooted tree, we want to reassign some nodes parents such that the maximum depth in the tree
//is no greater than k. Minimize the amount of reassignments

//we can actually solve this greedily. Do a BFS from the leaves, and when there is a node that is exactly
//k away from the furthest leaf in its subtree, reroot it's children to the root. 

//don't forget that if node 1 isn't already pointing to itself, that takes another operation.

int solve(int cur, int p, int k, vvi& c, int& ans) {
    int mxd = 0;
    for(int x : c[cur]) if(x != p) mxd = max(mxd, solve(x, cur, k, c, ans) + 1);
    if(p != -1 && p != 0 && mxd == k - 1) ans += 1, mxd = -1;
    return mxd;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vvi c(n);
    int ans = 0;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        a --;
        if(i == 0) {
            ans += a != 0;
            continue;
        }
        c[i].push_back(a);
        c[a].push_back(i);
    }
    solve(0, -1, k, c, ans);
    cout << ans << "\n";
    
    return 0;
}