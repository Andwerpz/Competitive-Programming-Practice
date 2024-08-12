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

//Codeforces - 2002C

//denote the distance between two points as dist(a, b). Consider a straight line path from s to g. 

//you can only get to the target if dist(s, g) < dist(a[i], g), for all centers a[i]. This is trivially true, because
//if for some a[i], dist(s, g) >= dist(a[i], g), then that circle would have already contained the goal before you
//reached it. 

//it's also true that if a circle is positioned to 'intercept' you on the straight line between s and g, then
//it's already closer to you than your starting point to g, so it's necessary and sufficient to just check the above
//condition for each circle. 

ll dist(pll a, pll b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
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
        for(int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
        }
        pll s, g;
        cin >> s.first >> s.second >> g.first >> g.second;
        ll s_dist = dist(s, g);
        // cout << "S_DIST : " << s_dist << "\n";
        bool is_valid = true;
        for(int i = 0; i < n; i++){
            // cout << "I : " << dist(a[i], g) << "\n";
            if(dist(a[i], g) <= s_dist) {
                is_valid = false;
            }
        }
        cout << (is_valid? "YES" : "NO") << "\n";
    }
    
    return 0;
}