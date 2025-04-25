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

//Spring 2025 Columbia University Local Contest - F

//two pointers sliding window. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vl a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        vb ist(n, false);
        for(int i = 0; i < n - 2; i++){
            if((a[i + 1] - a[i]) * (a[i + 2] - a[i + 1]) < 0) ist[i] = true;
        }
        int ans = 2, r = 0, tcnt = 0;
        for(int i = 0; i < n; i++){
            while(r != n) {
                int ntcnt = tcnt;
                if(r - 2 >= i && ist[r - 2]) ntcnt ++;
                if(ntcnt > k) break;
                tcnt = ntcnt;
                r ++;
            }
            // cout << "I : " << i << " " << r << " " << tcnt << "\n";
            ans = max(ans, r - i);
            if(r - i >= 3 && ist[i]) tcnt --;
        }
        cout << ans << "\n";
    }
    
    return 0;
}