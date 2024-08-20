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

//AtCoder - ABC365E

//for each bit, we want to determine its contribution to the final sum. It's pretty useful to consider
//for a fixed right bound, how many times do we add some bit to the sum. 

//lets say there is some right bound r where there are zcnt left bounds that have 0 contribution and ocnt 
//ones that have 1 contribution. Then if we want to update the cnts for r + 1, we add 1 to zcnt, and then 
//swap them if a[r] has the bit. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vvl> pfx(n + 1, vvl(30, vl(2, 0)));
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < 30; j++){
            int bit = (a[i - 1] >> j) & 1;
            pfx[i][j][0] = pfx[i - 1][j][0 ^ bit] + (1 ^ bit);
            pfx[i][j][1] = pfx[i - 1][j][1 ^ bit] + (0 ^ bit);
        }
    }
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans -= a[i];
        for(int j = 0; j < 30; j++){
            ll bit = (1 << j);
            ans += bit * pfx[i + 1][j][1];
        }
    }
    cout << ans << "\n";

    return 0;
}