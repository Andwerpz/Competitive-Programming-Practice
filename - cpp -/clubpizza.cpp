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

//Mines HSPC 2025 Open Division - G

//for each hour, just go to the club with the minimum amount of pizza

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, c;
    cin >> n >> c;
    vl a(24, 1e9);
    for(int i = 0; i < n; i++){
        int t, p;
        cin >> t >> p;
        a[t] = min(a[t], (ll) p);
    }
    sort(a.begin(), a.end());
    ll sum = 0, ans = 0;
    for(int i = 0; i < a.size(); i++) {
        sum += a[i];
        if(sum <= c) ans ++;
    }
    cout << ans << "\n";
    
    return 0;
}