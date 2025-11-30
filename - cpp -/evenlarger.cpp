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

//Codeforces - 2134C

//first, make the observation that if all subarrays of length 2 and length 3 are good, then all subarrays
//are good. 

//To fix all subarrays of length 2, you need to make every odd indexed element at most the min of its neighbors
//Then, you can use a greedy approach to fix all subarrays of length 3. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        ll ans = 0;
        vl a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i += 2){
            ll mn = 1e18;
            if(i != 0) mn = min(mn, a[i - 1]);
            if(i + 1 != n) mn = min(mn, a[i + 1]);
            if(mn < a[i]) {
                ans += a[i] - mn;
                a[i] = mn;
            }
        }
        for(int i = 2; i < n; i += 2){
            ll sum = a[i - 2] + a[i];
            if(sum > a[i - 1]) {
                ll diff = sum - a[i - 1];
                assert(diff <= a[i]);
                ans += diff;
                a[i] -= diff;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}