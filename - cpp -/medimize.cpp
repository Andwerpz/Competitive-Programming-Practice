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

//Codeforces - 1993D

//note that any final array that can be obtained from the procedure described in the problem statement can also
//be obtained by this procedure:
//let the original array = a, and final array = b. Keep a ptr, initially 0. At every step, we can either:
//1. append a[ptr] to b, ptr += 1
//2. ptr += k

//this procedure actually lends itself quite well to a dp solution. 
//given some target median tgt, we can test whether or not it's possible to make the median >= tgt:
//dp[i][j] = max number of taken values >= tgt where
//i = number skips
//j = number taken
//transitions should be relatively obvious. 

//we can just binary search for the minimum tgt that works. 

bool is_valid(int n, int k, vi& a, int val) {
    int rem = n % k;
    if(rem == 0){
        rem = k;
    }
    int mult = (n - rem) / k;
    vi pfx(n + 1, 0);
    for(int i = 1; i <= n; i++){
        pfx[i] = pfx[i - 1] + (a[i - 1] >= val);
    }
    vvi dp(mult + 1, vi(rem + 1, 0));
    dp[0][0] = 0;
    for(int i = 0; i <= mult; i++){
        for(int j = 0; j <= rem; j++){
            //take current one
            if(j < rem){
                int nind = i * k + j;
                dp[i][j + 1] = max(dp[i][j + 1], dp[i][j] + (a[nind] >= val));
            }
            //skip k
            if(i < mult) {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            }
        }
    }
    return dp[mult][rem] * 2 > rem;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int low = 0;
        int high = 1e9;
        int ans = low;
        while(low <= high){
            int mid = low + (high - low) / 2;
            if(is_valid(n, k, a, mid)) {
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