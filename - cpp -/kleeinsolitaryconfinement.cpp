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

//UIUC IPL Team Tryout 2025 - L

//suppose that our target mode is some M. Then, only values M and M - K are relevant. If the segment we 
//choose covers M - K, then we gain one, if it contains M, then we lose one. We just want to find the 
//subarray with maximum value, this can be solved in O(N) using kadane's algorithm.

//actually, since each value matters for at most 2 modes, we can solve all N problems simultaneously using 
//N simultaneous kadanes. 

const int N = 5000000;
vi f(N, 0), dp(N, 0), mx(N, 0);

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vi a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] += N / 2;
    }
    for(int i = 0; i < n; i++) {
        f[a[i]] ++;
        dp[a[i]] = 0;
        dp[a[i] + k] = 0;
    }
    for(int i = 0; i < n; i++) {
        dp[a[i] + k] ++;
        if(dp[a[i]] != 0) dp[a[i]] --;
        mx[a[i]] = max(mx[a[i]], dp[a[i]]);
        mx[a[i] + k] = max(mx[a[i] + k], dp[a[i] + k]);
    }
    int ans = 0;
    for(int i = 0; i < N; i++) {
        ans = max(ans, f[i] + mx[i]);
    }
    cout << ans << "\n";
    
    return 0;
}