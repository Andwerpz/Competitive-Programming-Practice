#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//AtCoder - ARC189C

//I'll call the edges on which the red balls travel red edges, and blue edges are the ones that blue balls travel on
//Notice that one operation is just choosing a node and sending all the red balls along the outgoing red edge and 
//the blue balls along the outgoing blue edge. 

//If we consider all edges of one color independently, then we notice that it's just a functional graph, which means that
//the graph is made up of a bunch of connected components, and each component is just a simple cycle. So, we can see that 
//if there exists a ball that is not on the cycle that X is, then we can say it's impossible. Otherwise, it's always possible. 

//Now, we can assume that all balls are on the same cycle as X. Here, notice that we only really care about the furthest
//red and blue balls from X, as if we only do operations on the furthest balls, the rest of the balls are guaranteed to 
//reach X when the furthest balls reach X. So we want to minimize the amount of operations to get the furthest balls to X. 

//Denote alen and blen as the distance of the red and blue ball from X. At most, our answer will be alen + blen, however 
//it's possible that it could be less. The worst case assumes that each operation only affects one of the red or blue balls,
//however if the two cycles happen to coincide, we can move the balls to the same node, and then spend one operation to move
//both of the balls, saving an operation. Finding the maximum amount of saved operations can be done with LIS. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, x;
    cin >> n >> x;
    x --;
    vi a(n), b(n), p(n), q(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    for(int i = 0; i < n; i++) cin >> p[i];
    for(int i = 0; i < n; i++) cin >> q[i];
    for(int i = 0; i < n; i++) p[i] --, q[i] --;
    vb av(n, false), bv(n, false);
    int ptr = x, alen = 0, blen = 0;
    while(!av[ptr]) av[ptr] = true, ptr = p[ptr], alen ++;
    while(!bv[ptr]) bv[ptr] = true, ptr = q[ptr], blen ++;
    bool is_valid = true;
    for(int i = 0; i < n; i++) if((!av[i] && a[i]) || (!bv[i] && b[i])) is_valid = false;
    if(!is_valid) {
        cout << "-1\n";
        return 0;
    }
    vi d(n, -1);
    int ans = 0, dptr = 0;
    for(int i = 0; i < n; i++) av[i] = false, bv[i] = false;
    bool found = false;
    ptr = p[x], alen --;
    while(ptr != x) {
        if(!found && a[ptr]) found = true;
        if(found) av[ptr] = true;
        else alen --;
        ptr = p[ptr];
    }
    ptr = q[x], blen --, found = false;
    while(ptr != x) {
        if(!found && b[ptr]) found = true;
        if(found) bv[ptr] = true, d[ptr] = dptr;
        else blen --;
        ptr = q[ptr];
        dptr ++;
    }
    ans = alen + blen;
    vi dp(n + 10, 1e9);
    dp[0] = -1e9;
    ptr = p[x];
    int lis = 0;
    while(ptr != x) {
        if(d[ptr] != -1 && av[ptr]) {
            //find last elem less than current
            int low = 0, high = dp.size() - 1, ind = low;
            while(low <= high) {
                int mid = low + (high - low) / 2;
                if(dp[mid] < d[ptr]) ind = mid, low = mid + 1;
                else high = mid - 1;
            }
            dp[ind + 1] = d[ptr];
            lis = max(lis, ind + 1);
        }
        ptr = p[ptr];
    }
    ans -= lis;
    cout << ans << "\n";
    
    return 0;
}