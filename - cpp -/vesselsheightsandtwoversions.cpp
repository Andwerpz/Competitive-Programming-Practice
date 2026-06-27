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

//Codeforces - 2234C

//suppose that the vessels were not cyclic (the edge between vessels n and 1 does not exist)
//then if we want to fix some vessel i to have 0 water, we can observe for some j < i 
//that a[j] >= a[j + 1], and for j > i, a[j - 1] <= a[j]

//then if we re-add the cyclic edge, we can think of each vessel being under two simultaneous 
//constraints. It's actually sufficient to just take the minimum of the two values. 
//doing this in O(n^2) solves the easy version. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vl a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) {
            vl l(n, 0), r(n, 0);
            for(int j = 1; j < n; j++) {
                l[(i + j) % n] = max(l[(i + j - 1 + n) % n], a[(i + j - 1 + n) % n]);
                r[(i - j + n) % n] = max(r[(i - j + 1 + n) % n], a[(i - j + n) % n]);
            }
            ll ans = 0;
            for(int j = 0; j < n; j++) ans += min(l[j], r[j]);
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}