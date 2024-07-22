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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1990C

//first, notice that the first application of MAD sum will sort a, and then the second application will
//remove any unique values. After the second application, all the values will shift left by one for 
//every application, so we can just simulate the first two applications, and then sum all 
//prefix sums to get the answer. 

ll calc_mad(vi& a) {
    ll sum = 0;
    vi ans(a.size());
    int mad = 0;
    map<int, int> m;
    for(int i = 0; i < a.size(); i++){
        sum += a[i];
        m[a[i]] ++;
        if(m[a[i]] > 1){
            mad = max(mad, a[i]);
        }
        ans[i] = mad;
    }
    a = ans;
    return sum;
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
        ll ans = calc_mad(a);
        ans += calc_mad(a);
        vl pfx(n + 1, 0);
        for(int i = 1; i <= n; i++){
            pfx[i] = pfx[i - 1] + a[i - 1];
            ans += pfx[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}