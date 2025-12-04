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

// BAPC 2023 - F

//we can simulate the queue to see at every minute how many people are going to be in line. 
//then, when we join the line, anybody that joins after us doesn't matter to our waiting time, so we can compute
//the waiting time in O(1). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, c;
    cin >> n >> c;
    vl a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    ll sum = 0;
    int ans = -1;
    ll mnw = 1e18;
    for(int i = 0; i < n; i++) {
        sum += a[i];
        ll w = (sum + 1 + c - 1) / c;
        // cout << "SUM : " << i << " " << sum << " " << w << " " << mnw << "\n";
        if(i + w <= n && w < mnw) {
            mnw = w;
            ans = i;
        }
        sum = max(0ll, sum - c);
    }
    if(ans == -1) cout << "impossible\n";
    else cout << ans << "\n";
    
    return 0;
}