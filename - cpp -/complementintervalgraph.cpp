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

//AtCoder - ARC193A

//if the two segments are initially unconnected, then the best path is to just go directly from s to t.

//otherwise, there are only a few ways to get from s to t.
// - travel from s to a segment that doesn't intersect either s or t, then travel to t. 
// - travel from s to a segment that only intersects t, then to a segment that only intersects s, then to t. 
//any other path is strictly worse; you can reduce them to one of these two. 

//we can check both of these in O(1) time given some preprocessing. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl w(n);
    for(int i = 0; i < n; i++) cin >> w[i];
    vl pfx(2 * n + 1, 1e18), sfx(2 * n + 1, 1e18);
    vi l(n), r(n);
    for(int i = 0; i < n; i++){
        cin >> l[i] >> r[i];
        l[i] --;
        pfx[r[i]] = min(pfx[r[i]], w[i]);
        sfx[l[i]] = min(sfx[l[i]], w[i]);
    }
    for(int i = 1; i <= 2 * n; i++) pfx[i] = min(pfx[i], pfx[i - 1]);
    for(int i = 2 * n - 1; i >= 0; i--) sfx[i] = min(sfx[i], sfx[i + 1]);
    int q;
    cin >> q;
    while(q--) {
        int s, t;
        cin >> s >> t;
        s --, t --;
        ll ans = 1e18;
        int sl = l[s], sr = r[s], tl = l[t], tr = r[t];
        int ll = min(sl, tl), rr = max(sr, tr);
        if(sl > tl) swap(s, t), swap(sl, tl), swap(sr, tr);
        if(sr <= tl) ans = min(ans, w[s] + w[t]);
        ans = min(ans, w[s] + w[t] + pfx[ll]);
        ans = min(ans, w[s] + w[t] + sfx[rr]);
        ans = min(ans, w[s] + w[t] + pfx[tl] + sfx[sr]);
        cout << (ans == 1e18? -1 : ans) << "\n";
    }
    
    return 0;
}