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

//UTPC Contest 11-20-24 Div1 - F

//if n = 1, answer is 0 0
//if n = 2, answer is 1 (sq dist between chicks)
//else, n >= 3. 

//in this case, the minimum amount of handshakes is always 2, so the chicks are always going to form a linked list. 
//since n <= 18, we can just do bitset dp. 

ll dist_sq(pll a, pll b){
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    if(n == 1){
        cout << "0 0\n";
        return 0;
    }
    if(n == 2){
        cout << "1 " << dist_sq(a[0], a[1]) << "\n";
        return 0;
    }
    vvl dp((1 << n), vl(n, 1e18));
    //base cases
    for(int i = 0; i < n; i++){
        dp[(1 << i)][i] = 0;
    }
    for(int i = 1; i < (1 << n); i++){
        for(int j = 0; j < n; j++){
            if(dp[i][j] == 1e18) {
                continue;
            }
            for(int k = 0; k < n; k++){
                if(i & (1 << k)) continue;
                dp[i ^ (1 << k)][k] = min(dp[i ^ (1 << k)][k], max(dp[i][j], dist_sq(a[j], a[k])));
            }
        }
    }
    ll ans = 1e18;
    for(int i = 0; i < n; i++){
        ans = min(ans, dp[(1 << n) - 1][i]);
    }
    cout << 2 << " " << ans << "\n";
    
    return 0;
}