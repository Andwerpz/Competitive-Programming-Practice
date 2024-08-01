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

//Codeforces - 1997D

//we can binary search for the answer. 

//if we want to set the root to some value x, and x > a[0], then we need to increment it by x - a[0]. That means that
//the direct children of the root have to be at least x - a[0]. We can recursively apply this logic down to the leaves,
//to check whether some x is valid. 

bool is_valid(int cur, vvi& c, vi& a, ll tgt) {
    // cout << "IS_VALID : " << cur << " " << inc << "\n";
    if(c[cur].size() == 0){
        // cout << "LEAF" << a[cur] << "\n";
        return a[cur] >= tgt;
    }
    if(tgt > 1e10){
        return false;
    }
    // tgt = max(tgt - a[cur], 0ll);
    tgt += max(0ll, tgt - a[cur]);
    bool ans = true;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        ans = ans && is_valid(next, c, a, tgt);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vvi c(n, vi(0));
        for(int i = 0; i < n - 1; i++){
            int p;
            cin >> p;
            p --;
            c[p].push_back(i + 1);
        }
        ll low = 0;
        ll high = 1e10; 
        ll ans = 0;
        while(low <= high) {
            ll mid = low + (high - low) / 2;
            // cout << "TEST : " << mid << "\n";
            bool cur_valid = true;
            for(int i = 0; i < c[0].size(); i++){
                int next = c[0][i];
                cur_valid = cur_valid && is_valid(next, c, a, max(0ll, mid - a[0]));
            }
            if(cur_valid) {
                ans = max(ans, mid);
                low = mid + 1;
            }
            else { 
                high = mid - 1;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}