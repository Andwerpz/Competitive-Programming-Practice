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

//Codeforces - 509F

//dp[l][r] = number of rooted forests possible over [l, r) segment of a
//to compute dp[l][r], we have three options:
// - add singleton node to existing forest
// - add new tree to existing forest
// - merge existing forest into one tree 

const ll mod = 1e9 + 7;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    if(n == 1){
        cout << "1\n";
        return 0;
    }
    vvl dp(n + 1, vl(n + 1, 0));
    for(int i = 1; i <= n; i++){
        for(int j = 0; j + i <= n; j++){
            int l = j;
            int r = j + i;
            if(i == 1){
                //base case
                dp[l][r] = 1;
                continue;
            }
            //add singleton node
            if(a[l] < a[l + 1]){
                dp[l][r] += dp[l + 1][r];
                dp[l][r] %= mod;
            }
            //add new tree
            for(int k = l + 2; k < r; k++){
                if(a[l] > a[k]) continue;
                dp[l][r] += dp[l + 1][k] * dp[k][r];
                dp[l][r] %= mod;
            }
            //merge into root
            dp[l][r] += dp[l + 1][r];
            dp[l][r] %= mod;
            // cout << "WAYS : " << l << " " << r << " " << dp[l][r] << "\n";
        }
    }
    cout << dp[1][n] << "\n";
    
    return 0;
}