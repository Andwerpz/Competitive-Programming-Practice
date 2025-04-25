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

//Kattis - signals

//just find the LIS

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vi dp(n + 1, 1e9);
    dp[0] = -1e9;
    int ans = 0;
    for(int i = 0; i < n; i++){
        int low = 0, high = n - 1, ind = 0;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(dp[mid] < a[i]) ind = mid, low = mid + 1;
            else high = mid - 1;
        }
        dp[ind + 1] = min(dp[ind + 1], a[i]);
        ans = max(ans, ind + 1);
    }
    cout << ans << "\n";
    
    return 0;
}