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

//AtCoder - ABC366F

//nice problem where you have to first make some mathematical observation. 

//lets say that f(x) = Ax + B and g(x) = Cx + D. When is f(g(x)) > g(f(x))? Well, lets simplify and see
//where it goes:
//f(g(x)) > g(f(x)) ==> ACx + AD + B > ACx + BC + D
// ==> AD + B > BC + D
// ==> D(A - 1) > B(C - 1)
// ==> (A - 1) / B > (C - 1) / D

//so for any f(x) and g(x), if the above is true, then we'd want to take f(g(x)). This leads to a rather natural
//solution where we sort all elements in ascending order based off of (A - 1) / B, and do dp. However, there is 
//an apparent issue with this solution: What is the float value of f(g(x))? Does it increase? Note that if it
//increases past the float value of f(x), then we may have a problem, as we would want to use f(g(x)) as the
//outside function for some function after f(x). 

//well, we can check like so:
//(AC - 1) / (AD + B) > (A - 1) / B
// ==> ABC - B > A^2D + AB - AD - B
// ==> BC > AD + B - D
// ==> B(C - 1) > D(A - 1)
// ==> (C - 1) / D > (A - 1) > B

//so the float value can only increase if we take g(f(x)), which is not going to happen as it's suboptimal. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<pll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end(), [](pll a, pll b) -> bool {
        ld da = (a.first - 1.0) / (ld) a.second;
        ld db = (b.first - 1.0) / (ld) b.second;
        return da < db;
    });
    vvl dp(n + 1, vl(k + 1, 0));
    //base case
    for(int i = 0; i <= n; i++){
        dp[i][0] = 1;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] * a[i].first + a[i].second);
        }
    }
    ll ans = 0;
    for(int i = 0; i <= n; i++){
        ans = max(ans, dp[i][k]);
    }
    cout << ans << "\n";
    
    return 0;
}