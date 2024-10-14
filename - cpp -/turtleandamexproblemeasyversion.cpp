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

//Codeforces - 2003D1

//note that applying the operation once on a list will set x to the mex (if x wasn't already the mex), 
//and applying it twice will increase it past the mex. I'll call these two mexs m1 and m2 for each list. 

//denote the maximum m2 as max_mex. If m < max_mex, then we can raise it to max_mex, otherwise we shouldn't
//perform any operations as it will only lower m. 

ll arith_sum(ll start, ll nr_elem, ll inc) {
    ll ans = start * nr_elem;
    ans += inc * nr_elem * (nr_elem - 1) / 2;
    return ans;
}

ll calc_mex(vl& a){
    sort(a.begin(), a.end());
    if(a[0] != 0){
        return 0;
    }
    for(int i = 1; i < a.size(); i++){
        if(a[i] - 1 > a[i - 1]) {
            return a[i - 1] + 1;
        }
    }
    return a[a.size() - 1] + 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, m;
        cin >> n >> m;
        ll mx_mex = 0;
        for(int i = 0; i < n; i++){
            int len;
            cin >> len;
            vl a(len);
            for(int j = 0; j < len; j++){
                cin >> a[j];
            }
            ll cmex = calc_mex(a);
            a.push_back(cmex);
            mx_mex = max(mx_mex, calc_mex(a));
        }
        ll ans = 0;
        if(m <= mx_mex) {
            ans = (m + 1) * mx_mex;
        }
        else {
            ans = (mx_mex + 1) * mx_mex;
            ans += arith_sum(mx_mex + 1, m - mx_mex, 1);
        }
        cout << ans << "\n";
    }
    
    return 0;
}