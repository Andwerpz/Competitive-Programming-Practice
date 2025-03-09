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

//Baekjoon - 16192

//for each query, you can just loop through all of the voronoi points and see which are the closest. 
//this actually runs in less than a second (800ish ms). 

ll dist_sq(pll& a, pll& b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<pll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    for(int i = 0; i < q; i++){
        pll cur;
        cin >> cur.first >> cur.second;
        ll min_dist = 1e18;
        vector<int> ans(0);
        for(int j = 0; j < n; j++){
            ll cdist = dist_sq(cur, a[j]);
            if(cdist < min_dist) {
                min_dist = cdist;
                ans.clear();
            }
            if(cdist == min_dist && ans.size() < 3) {
                ans.push_back(j + 1);
            }
        }
        if(ans.size() == 1) cout << "REGION " << ans[0] << "\n";
        else if(ans.size() == 2) cout << "LINE " << ans[0] << " " << ans[1] << "\n";
        else if(ans.size() == 3) cout << "POINT" << "\n";
    }
    
    return 0;
}