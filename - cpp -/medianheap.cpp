#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//USACO 2025 January Contest Gold 1

int n;
vl a, c, fa;

bool inter(int l1, int r1, int l2, int r2) {
    return (l1 <= l2 && l2 < r1) || (l2 <= l1 && l1 < r2);
}

ll solve(int cur, int l, int r) {
    if(cur * 2 > n) return (l <= a[cur] && a[cur] < r)? 0 : c[cur];
    if(l <= fa[cur] && fa[cur] < r) return 0;
    int x = a[cur], y = fa[cur * 2], z = fa[cur * 2 + 1];
    ll ans = 1e18;
    if(y <= x && x <= z){
        if(inter(l, r, -1e9, y + 1)) {

        }
    }
    else if(z <= x && x <= y){

    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n;
    a = vl(n + 1), c = vl(n + 1), fa = vl(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i] >> c[i];
    for(int i = 1; i <= n; i++) fa[i] = a[i];
    for(int i = n; i >= 0; i--){
        if(i * 2 > n) continue;
        int x = a[i], y = fa[i * 2], z = fa[i * 2 + 1];
        if(x > y) swap(x, y);
        if(x > z) swap(x, z);
        if(y > z) swap(y, z);
        fa[i] = y;
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int m;
        cin >> m;
        cout << solve(1, m, m + 1) << "\n";
    }
    
    return 0;
}