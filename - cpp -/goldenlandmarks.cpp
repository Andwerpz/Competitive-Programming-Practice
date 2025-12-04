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

//Mines HSPC 2025 Open Division - I

//implementation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    map<string, pll> m;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        ll x, y;
        cin >> x >> y;
        m[s] = {x, y};
    }
    ll ans = 0;
    pll prev;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        pll cur = m[s];
        if(i != 0) ans += abs(cur.first - prev.first) + abs(cur.second - prev.second);
        prev = cur;
    }
    cout << ans << "\n";
    
    return 0;
}