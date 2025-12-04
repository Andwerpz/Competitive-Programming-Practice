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

//Mines HSPC 2025 Open Division - C

//sort all the endpoints of the lines by their slope. Then, slowly increase the slope and save the maximum amount of lines
//you can intersect. Use rational representations of slope to avoid floating point error. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<pll, int>> ev;
    for(int i = 0; i < n; i++){
        ll x, a, b;
        cin >> x >> a >> b;
        ev.push_back({{x, a}, 1});
        ev.push_back({{x, b}, -1});
    }
    sort(ev.begin(), ev.end(), [](pair<pll, int>& a, pair<pll, int>& b) -> bool {
        ll na = a.first.second, da = a.first.first, nb = b.first.second, db = b.first.first;
        na *= db, nb *= da;
        if(na == nb) return a.second < b.second;
        return na < nb; 
    });  
    int ans = 0, cnt = 0;
    for(int i = 0; i < ev.size(); i++) {
        cnt += ev[i].second;
        ans = max(ans, cnt);
    }
    cout << ans << "\n";
    
    return 0;
}