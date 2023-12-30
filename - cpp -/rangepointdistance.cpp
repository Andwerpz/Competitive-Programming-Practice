#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC129B

//we only care about the leftmost right point and the rightmost left point. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<ll, ll>> a(n, {0, 0});
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    ll min_r = 1e18;
    ll max_l = -1e18;
    for(int i = 0; i < n; i++){
        min_r = min(min_r, a[i].second);
        max_l = max(max_l, a[i].first);
        if(min_r >= max_l) {
            cout << "0\n";
            continue;
        }
        ll dist = max_l - min_r;
        cout << (dist + 1) / 2 << "\n";
    }
    
    return 0;
}
