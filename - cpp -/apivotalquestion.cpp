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

//ECNA 2023 - A

//just need to create a max pfx and min sfx array, and then can just linear scan to get all of the pivots. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vi pfx(n + 1, -1e9), sfx(n + 1, 1e9);
    for(int i = 0; i < n; i++) {
        pfx[i + 1] = max(pfx[i], a[i]);
    }
    for(int i = n - 1; i >= 0; i--) {
        sfx[i] = min(sfx[i + 1], a[i]);
    }
    vi ans(0);
    for(int i = 0; i < n; i++) {
        // cout << "PFX SFX : " << pfx[i] << " " << sfx[i + 1] << "\n";
        if(pfx[i] <= a[i] && a[i] <= sfx[i + 1]) {
            ans.push_back(a[i]);
        }
    }
    cout << ans.size() << " ";
    for(int i = 0; i < min((int) ans.size(), 100); i++) cout << (ans[i]) << " ";
    cout << "\n";
    
    return 0;
}