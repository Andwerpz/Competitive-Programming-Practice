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

//UTPC 11-12-2025 Div1 - C G

//observe that for any collection of lengths such that the maximum length is less than the sum of the rest of the 
//lengths, it's always possible to arrange the lengths into a polygon that can be circumscribed by a circle

//for the easy version, it's sufficient to fix the largest length, then do two pointers on the remaining lengths
//to compute the number of triples.

//for the hard version, we need to do dp. 
//dp[i][j][k] = number of ways given
// i = number of lengths we've considered
// j = number of lengths we've taken
// k = length sum remaining until we've exceeded the maximum

//to avoid having to run this once per maximum, we can do base case injection. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vl a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        int rptr = n - 1;
        for(int j = i + 1; j < n; j++) {
            while(rptr > j && a[j] + a[rptr] <= a[i]) rptr --;
            if(rptr == j) break;
            assert(rptr > j);
            // cout << "TRIPLE : " << i << " " << j << " " << rptr << "\n";
            ans += rptr - j;
        }
    }
    cout << ans << "\n";
    
    return 0;
}

// const ll mod = 1e9 + 7;
// const int MAXA = 10000;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL); cout.tie(NULL);

//     int n, _k;
//     cin >> n >> _k;
//     vi a(n);
//     for(int i = 0; i < n; i++) cin >> a[i];
//     sort(a.begin(), a.end());
//     reverse(a.begin(), a.end());
//     vector dp(2, vector(_k, vector(MAXA + 2, 0)));
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < _k; j++) {
//             for(int k = 0; k < MAXA + 2; k++) {
//                 dp[1][j][k] = 0;
//             }
//         }
//         //base case
//         dp[1][0][a[i] + 1] = 1;
//         //do dp
//         for(int j = 0; j < _k; j++) {
//             for(int k = 0; k < MAXA + 2; k++) {
//                 //don't take
//                 dp[1][j][k] = (dp[1][j][k] + dp[0][j][k]) % mod;
//                 //take
//                 if(j != _k - 1) {
//                     dp[1][j + 1][max(0, k - a[i])] = (dp[1][j + 1][max(0, k - a[i])] + dp[0][j][k]) % mod;
//                 }
//             }
//         }
//         swap(dp[0], dp[1]);
//     }
//     cout << dp[0][_k - 1][0] << "\n";
    
//     return 0;
// }