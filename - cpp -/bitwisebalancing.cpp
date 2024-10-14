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

//Codeforces - 2020C

//can just build the answer bit by bit. This works because carrys will never happen. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll b, c, d;
        cin >> b >> c >> d;
        ll ans = 0;
        bool is_valid = true;
        for(int i = 62; i >= 0; i--){
            ans *= 2;
            bool bb = (b >> i) & 1;
            bool cb = (c >> i) & 1;
            bool db = (d >> i) & 1;
            if(bb && cb && db) {
                //off
            }
            if(bb && cb && !db) {
                ans ++;
            }
            if(bb && !cb && db) {
                //either
            }
            if(bb && !cb && !db) {
                is_valid = false;
            }
            if(!bb && cb && db) {
                is_valid = false;
            }
            if(!bb && cb && !db) {
                //either
            }
            if(!bb && !cb && db) {
                ans ++;
            }
            if(!bb && !cb && !db) {
                //off
            }
        }
        // cout << "CHECK : " << (b | ans) - (c & ans) << "\n";
        cout << (is_valid? ans : -1) << "\n";
    }
    
    return 0;
}