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

//Codeforces - 2143B

//greedily use the discount with the lowest value on the most expensive items. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        ll ans = 0;
        vl a(n);
        for(ll& x : a) cin >> x;
        vi b(k);
        for(int i = 0; i < k; i++) cin >> b[i];
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        sort(b.begin(), b.end());
        int bptr = 0;
        for(int i = 0; i < n; i++) {
            if(bptr != k && i + b[bptr] <= n) {
                for(int j = 0; j < b[bptr] - 1; j++) ans += a[i + j];
                i += b[bptr] - 1;
                bptr ++;
            }
            else {
                ans += a[i];
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}