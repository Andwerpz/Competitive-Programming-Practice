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

//Codeforces - 1994C

//first, precompute for each l, the closest r such that sum on [l, r) > x. Then, we can go backwards from
//n - 1 to 0 and calculate for each l, how many r such that it satisfies the condition in the problem. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, x;
        cin >> n >> x;
        vl a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vb gts(n, false);
        vi rp(n, -1);
        ll sum = 0;
        int r = 0;
        for(int i = 0; i < n; i++){
            while(r != n && sum <= x) {
                sum += a[r];
                r ++;
            }
            rp[i] = r;
            if(sum > x){
                gts[i] = true;
            }
            sum -= a[i];
        }
        ll ans = 0;
        vl amt(n + 1, 0);
        for(int i = n - 1; i >= 0; i--){
            amt[i] = amt[rp[i]] + (rp[i] - i) - gts[i];
            ans += amt[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}