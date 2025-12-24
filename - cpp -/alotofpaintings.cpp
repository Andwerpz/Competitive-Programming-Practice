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

//2025 ICPC Asia Chengdu Regional Contest - A

//suppose that we fix the total number of paintings that get submitted. 

//then, each person has a range in which it can be in. We can compute the minimum and maximum amount for
//each person. 
//fill each element to the bottom of its range, if we still have stuff left, fill each to near the top

//either, we don't have enough elements to fill everyone up to the minimum, or we have too many elements so 
//that we have some leftover after filling everyone up to the maximum. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi d(n);
        for(int i = 0; i < n; i++) cin >> d[i];
        const ll P = 1e7;
        ll tot = P * 100;
        vl lo(n), hi(n);
        for(int i = 0; i < n; i++) {
            if(d[i] == 0) {
                lo[i] = 0;
                hi[i] = P / 2 - 1;
            }
            else {
                lo[i] = d[i] * P - P / 2;
                hi[i] = lo[i] + P - 1;
            }
        }
        vl ans(n, 0);
        bool is_valid = true;
        for(int i = 0; i < n; i++) {
            if(tot < lo[i]) {
                is_valid = false;
                break;
            }
            tot -= lo[i];
            ans[i] += lo[i];
        }
        if(!is_valid) {
            cout << "No\n";
            continue;
        }
        for(int i = 0; i < n; i++) {
            ll amt = min(hi[i] - lo[i], tot);
            tot -= amt;
            ans[i] += amt;
        }
        if(tot != 0) {
            cout << "No\n";
            continue;
        }
        cout << "Yes\n";
        for(int i = 0; i < n; i++) cout << ans[i] << " ";
        cout << "\n";
    }
    
    return 0;
}