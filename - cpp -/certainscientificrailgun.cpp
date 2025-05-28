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

//2020 ICPC Asia Nanjing Regional Contest - C

//nice monotonic divide and conquer problem. 

//first observation to make is that any optimal solution will look something like: 
// - go some distance -x
// - backtrack to origin
// - go some distance -y
// - backtrack to origin
// - go some distance +x
// - go some distance +y
//of course, it might be optimal to backtrack in some different direction, but we can try all these cases by just mirroring
//the points around both axes. So for now we can find an optimal solution of the above form. 

//let cost(A, B) be the minimum cost of eliminating all the points given you've travelled A units in the -x direction and B 
//units in the +x direction. This can be computed in constant time using some pfx/sfx, min/max arrays. 

//suppose for some left bound L, you've found the right bound R such that cost(L, R) is minimized. The next observation is to 
//notice that for L' < L, R' >= R. So for increasing L, the optimal R is monotonically decreasing. 

//using this and the fact that queries to cost(A, B) can be computed in constant time, we can make a divide and conquer 
//solution to this problem in O(n * log(n)). 

ll solve(vector<pll> a, int n) {
    sort(a.begin(), a.end());
    vl pfx_min(n, 1e18), pfx_max(n, -1e18), sfx_min(n, 1e18), sfx_max(n, -1e18);
    pfx_min[0] = a[0].second;
    pfx_max[0] = a[0].second;
    for(int i = 1; i < n; i++) {
        pfx_max[i] = max(pfx_max[i - 1], a[i].second);
        pfx_min[i] = min(pfx_min[i - 1], a[i].second);
    }
    sfx_min[n - 1] = a[n - 1].second;
    sfx_max[n - 1] = a[n - 1].second;
    for(int i = n - 2; i >= 0; i--){
        sfx_max[i] = max(sfx_max[i + 1], a[i].second);
        sfx_min[i] = min(sfx_min[i + 1], a[i].second);
    }
    int zind = -1;
    int lzind = -1;
    for(int i = 0; i < n; i++) if(a[i].first == 0) lzind = i;
    for(int i = 0; i < n; i++) if(a[i].first == 0) {zind = i; break;}
    function<ll(int, int, int, int)> dfs = [&](int l, int r, int sl, int sr) -> ll {
        if(r == l) return 1e18;
        int mid = l + (r - l) / 2;
        ll ans = 1e18;
        int ansind = -1;
        for(int i = sl; i < sr; i++){
            ll cans = abs(a[mid].first) * 2 + a[i].first;
            ll yneg = 0;
            if(mid != 0) yneg = max(yneg, -pfx_min[mid - 1]);
            if(i + 1 != n) yneg = max(yneg, -sfx_min[i + 1]);
            cans += yneg * 2;
            ll ypos = 0;
            if(mid != 0) ypos = max(ypos, pfx_max[mid - 1]);
            if(i + 1 != n) ypos = max(ypos, sfx_max[i + 1]);
            cans += ypos;
            if(cans < ans) {
                ans = cans;
                ansind = i;
            }
        }
        ans = min(ans, dfs(l, mid, ansind, sr));
        ans = min(ans, dfs(mid + 1, r, sl, ansind + 1));
        return ans;
    };
    return dfs(0, zind + 1, lzind, n);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pll> a(n);
        for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
        a.push_back({0, 0});
        n ++;
        ll ans = 1e18;
        for(int i = 0; i < 4; i++){
            vector<pll> na = a;
            for(int j = 0; j < n; j++){
                if(i & 1) na[j].first *= -1;
                if(i & 2) na[j].second *= -1;
            }
            ans = min(ans, solve(na, n));
        }
        cout << ans << "\n";
    }
    
    return 0;
}