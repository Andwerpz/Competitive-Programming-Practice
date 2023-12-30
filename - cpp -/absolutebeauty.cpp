#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1898D

//let's examine what happens to the total area of two segments if you arbitrarily exchange endpoints between them. 

//if the segments are disjoint, the total area will always go up by exactly twice the distance between the segments. 
//if the segments are overlapping, the total area will always go down by exactly twice the intersection area. 

//we can treat each element in the summation as a segment, and |a[i] - b[i]| is just the area of the segment. 
//thus, we just need to find the two segments with the maximum distance between them, and swap their endpoints. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        ll ans = 0;
        vector<ll> a(n);
        vector<ll> b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
            ans += abs(a[i] - b[i]);
        }
        ll add = 0;
        ll min_r = 1e10;
        ll max_l = -1e10;
        for(int i = 0; i < n; i++){
            ll l = min(a[i], b[i]);
            ll r = max(a[i], b[i]);
            add = max(add, l - min_r);
            add = max(add, max_l - r);
            min_r = min(min_r, r);
            max_l = max(max_l, l);
        }
        add *= 2;
        ans += add;
        cout << ans << "\n";
    }
    
    return 0;
}
