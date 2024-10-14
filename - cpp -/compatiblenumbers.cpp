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

//Codeforces - 165E

//classic SOS dp problem. For some number x, we want to find any other number in the array y such that 
//y is a subset of ~x. We can precompute dp[i] where dp[i] is not -1 if there is an element of the array 
//that is a subset of i using SOS dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int BITS = 22;
    int n;
    cin >> n;
    vi a(n), dp((1 << BITS), -1);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        dp[a[i]] = a[i];
    }
    for(int i = 0; i < BITS; i++){
        for(int j = 0; j < (1 << BITS); j++){
            if(j & (1 << i)) {
                dp[j] = max(dp[j], dp[j ^ (1 << i)]);
            }
        }
    }
    // for(int i = 1; i <= BITS; i++){
    //     for(int j = 0; j < (1 << BITS); j++){
    //         if((j >> (i - 1)) & 1) {
    //             //bit is 1, can either have 0 or 1
    //             dp[j][i] = max(dp[j][i], dp[j][i - 1]); //1
    //             dp[j][i] = max(dp[j][i], dp[j ^ (1 << (i - 1))][i - 1]);    //0
    //         }
    //         else {
    //             //bit is 0, must have 0
    //             dp[j][i] = max(dp[j][i], dp[j][i - 1]);
    //         }
    //     }
    // }
    for(int i = 0; i < n; i++){
        int ans = -1;
        int x = 0;
        for(int j = 0; j < BITS; j++){
            if(!((a[i] >> j) & 1)) {
                x += (1 << j);
            }
        }
        cout << dp[x] << " ";
    }
    cout << "\n";

    return 0;
}