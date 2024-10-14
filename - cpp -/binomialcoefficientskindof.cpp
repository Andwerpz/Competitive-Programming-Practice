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

//Codeforces - 2025B

//if you simulate it, then you'll find that C[n][k] = 2^k if n != k, and 1 otherwise. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // int n = 10;
    // vvl dp(n, vl(n, 0));
    // for(int i = 0; i < n; i++){
    //     dp[i][0] = 1;
    //     dp[i][i] = 1;
    //     for(int j = 1; j < i; j++){
    //         dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1];
    //     }
    //     for(int j = 0; j <= i; j++){
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    ll mod = 1e9 + 7;
    vl pow2(1e6, 0);
    pow2[0] = 1;
    for(int i = 1; i < pow2.size(); i++){
        pow2[i] = (pow2[i - 1] * 2) % mod;
    }
    int t;
    cin >> t;
    vl a(t), b(t);
    for(int i = 0; i < t; i++){
        cin >> a[i];
    }
    for(int i = 0; i < t; i++){
        cin >> b[i];
    }
    for(int i = 0; i < t; i++){
        if(a[i] == b[i]) {
            cout << "1\n";
        }   
        else {
            cout << pow2[b[i]] << "\n";
        }
    }
    
    return 0;
}