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

//AtCoder - AGC32D

//Imagine that the elements of the permutation are placed onto the real number line. For example, if p[2] = 3, 
//then at x = 2 we will place a token with the number '3' written on it. 

//Then, the left shift operation can be represented as moving a segment of stones to the left, while moving the 
//leftmost stone all the way to the right. Actually, if we don't care about the exact locations of the stones but 
//just the relative ordering, the left shift operation is just choosing a stone and moving it some distance to
//the right. Crucially, we don't have to move it an integer distance. 

//So now we have two operations: pay A to move a token any distance to the right, and B to move it to the left.
//Observe that we should only move each stone at most once; from its starting location directly to its ending 
//location. 

//Finally, we can arrive at a dp solution: dp[i][j] = min cost after moving first i tokens by value to range 
//(-\inf, j]. Transitions are simple, we can either move the next stone into the range, or expand the range. 
//When moving a stone, make sure to increment the total cost by the appropriate amount. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, a, b;
    cin >> n >> a >> b;
    vi p(n), ppos(n);
    for(int i = 0; i < n; i++){
        cin >> p[i];
        p[i] --;
        ppos[p[i]] = i;
    }
    //dp[i][j] = min cost after moving first i values to range (-\inf, j]
    vvl dp(n + 1, vl(n + 1, 1e18));
    dp[0][0] = 0;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            //increase range
            if(j != n) dp[i][j + 1] = min(dp[i][j + 1], dp[i][j]);
            //move value
            if(i != n) dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + a * (ppos[i] < j) + b * (ppos[i] > j));
        }
    }
    cout << dp[n][n] << "\n";
    
    return 0;
}