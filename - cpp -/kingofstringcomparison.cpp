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

//UIUC IPL Team Tryout 2025 - K

//for each starting point, just consider how many subarrays start there and satisfy the condition. 
//can do one backwards sweep

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    string t;
    cin >> t;
    ll ans = 0;
    int prev = n;
    bool s_better = false;
    for(int i = n - 1; i >= 0; i--) {
        if(s[i] != t[i]) {
            prev = i;
            s_better = s[i] < t[i];
        }
        // cout << "PREV : " << i << " " << prev << "\n";
        if(s_better) ans += n - prev;
    }
    cout << ans << "\n";
    
    return 0;
}