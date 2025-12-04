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

//CodeSprint LA 2025 Open - B

//let s = n / k, or the size of the sets that you need to split the runes into. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    map<int, int> f;
    for(int i = 0; i < n; i++) f[a[i]] ++;
    set<int> s;
    int ans = 0;
    int gs = n / k;
    int l = gs * (1 + k / 2) - 1;
    int r = (n - k / 2) - 1;
    for(int i = l; i <= r; i++){
        if(s.count(a[i])) continue;
        s.insert(a[i]);
        ans += f[a[i]];
    }
    cout << ans << "\n";
    
    return 0;
}