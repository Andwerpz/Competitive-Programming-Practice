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

//Codeforces - 2125C

//do a lil inclusion exclusion. Observe that there are only 4 primes with less than 2 digits. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    vl pr = {2, 3, 5, 7};
    int t;
    cin >> t;
    while(t--){
        ll l, r;
        cin >> l >> r;
        r ++;
        ll ans = 0;
        for(int i = 0; i < (1 << 4); i++){
            ll p = 1, cnt = 0;
            for(int j = 0; j < 4; j++){
                if(i & (1 << j)) {
                    p *= pr[j];
                    cnt ++;
                }
            }
            if(cnt % 2) ans -= ((r - 1) / p) - ((l - 1) / p);
            else ans += ((r - 1) / p) - ((l - 1) / p);
        }
        cout << ans << "\n";
    }
    
    return 0;
}