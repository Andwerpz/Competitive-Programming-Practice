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

//2025 NAQ - F

//we can decompose the squared deviation from the mean as
//(u - x)^2 = u^2 - 2ux + x^2
//if we just keep track of the mean, sum, and squared sum, we can do this using sliding window. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, k;
    cin >> n >> k;
    vl a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    ld sum = 0, ssq = 0;
    ld ans = 1e18;
    for(int i = 0; i < n; i++) {
        sum += a[i];
        ssq += a[i] * a[i];
        if(i - k + 1 >= 0) {
            // cout << "TRY : " << i << " " << sum << " " << ssq << "\n";
            ld mean = sum / (ld) k;
            ld cans = mean * mean * (ld) k - 2.0 * mean * sum + ssq;
            ans = min(ans, cans);
            sum -= a[i - k + 1];
            ssq -= a[i - k + 1] * a[i - k + 1];
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}