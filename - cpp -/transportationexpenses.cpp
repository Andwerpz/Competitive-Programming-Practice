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

//AtCoder - ABC365C

//binary search. To determine if it's infinite, just check if the sum of all a[i] <= m. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll n, m;
    cin >> n >> m;
    ll sum = 0;
    vl a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sum += a[i];
    }
    if(m >= sum) {
        cout << "infinite\n";
        return 0;
    }
    ll ans = 0;
    ll low = 0;
    ll high = m;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        ll csum = 0;
        for(int i = 0; i < n; i++){
            csum += min(mid, a[i]);
        }
        if(csum <= m) {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}