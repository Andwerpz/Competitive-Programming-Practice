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

//Codeforces - 2002E

//having to find the answer on every prefix hints at an incremental solution. Note that the answer is always
//monotonically increasing, and in order for the answer to increase, it must somehow use the new segment
//that we add for every prefix. 

//we can use a monotonic stack. When adding a segment onto the end, it can either merge with other segments of the
//same value, or it can 'overshadow' segments of different value from being merged. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n), b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i] >> b[i];
        }
        ll ans = 0;
        stack<pll> s;
        for(int i = 0; i < n; i++){
            ll amt = a[i];
            int val = b[i];
            ll sub = 0;
            while(s.size() != 0){
                ll n_amt = s.top().first;
                int n_val = s.top().second;
                if(n_val != val) {
                    if(amt <= n_amt) {
                        break;
                    }
                    s.pop();
                    sub = n_amt;
                }
                else {
                    s.pop();
                    amt += n_amt - sub;
                }
            }
            ans = max(ans, amt);
            s.push({amt, val});
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}