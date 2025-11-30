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

const ld epsilon = 1e-7;

ld calc_cost(ld pos, vd& a, int l, int r) {
    ld ans = 0;
    for(int i = l; i < r; i++) {
        ans += (a[i] - pos) * (a[i] - pos);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vd a(n + m);
    for(int i = 0; i < n + m; i++) cin >> a[i];
    n += m;
    sort(a.begin(), a.end());
    vd asq(n);
    for(int i = 0; i < n; i++) asq[i] = a[i] * a[i];
    vd pfx_asq(n + 1, 0), pfx_a(n + 1, 0);
    for(int i = 0; i < n; i++) {
        pfx_a[i + 1] = pfx_a[i] + a[i];
        pfx_asq[i + 1] = pfx_asq[i] + asq[i];
    }
    //for each segment, precompute the cost of the best placement
    vvd cost(n + 1, vd(n + 1, 1e18));
    for(int l = 0; l < n; l++) {
        for(int r = l + 1; r <= n; r++){
            ld x_s = pfx_a[r] - pfx_a[l];
            ld xsq_s = pfx_asq[r] - pfx_asq[l];
            ld low = a[l];
            ld high = a[r - 1];
            while(high - low > epsilon) {
                ld m1 = low + (high - low) / 3.0 * 1.0;
                ld m2 = low + (high - low) / 3.0 * 2.0;
                ld v1 = xsq_s + (r - l) * m1 * m1 - 2.0 * m1 * x_s;
                ld v2 = xsq_s + (r - l) * m2 * m2 - 2.0 * m2 * x_s;
                if(v1 < v2) {
                    high = m2;
                }
                else {
                    low = m1;
                }
            }
            cost[l][r] = xsq_s + (r - l) * low * low - 2.0 * low * x_s;
        }
    }
    vvd dp(n + 1, vd(k + 1, 1e18));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++) {
        for(int _k = 0; _k < k; _k++) {
            for(int j = i + 1; j <= n; j++) {   
                dp[j][_k + 1] = min(dp[j][_k + 1], dp[i][_k] + cost[i][j]);
            }
        }
    }
    ld ans = dp[n][k];
    // cout << "DP : " << dp[n][k] << "\n";
    ans += n * (s / 2.0) * (s / 2.0);
    cout << fixed << setprecision(10) << ans << "\n";

    
    return 0;
}