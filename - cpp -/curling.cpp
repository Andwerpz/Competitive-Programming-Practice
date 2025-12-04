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

//2025 NAQ - E

//implementation, make sure not to mess up the button position. 

ll dist_sq(pll a, pll b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    pll but = {144, 84};
    int rs = 0, ys = 0;
    for(int _ = 0; _ < 10; _++) {
        // cout << "ITER : " << _ << endl;
        int n, m;
        cin >> n;
        vector<pll> r(n);
        for(int i = 0; i < n; i++) {
            cin >> r[i].first >> r[i].second;
        }
        cin >> m;
        vector<pll> y(m);
        for(int i = 0; i < m; i++) {
            cin >> y[i].first >> y[i].second;
        }
        // cout << "DONE READING" << endl;
        ll rcd = 1e18, ycd = 1e18;
        for(int i = 0; i < n; i++) rcd = min(rcd, dist_sq(but, r[i]));
        for(int i = 0; i < m; i++) ycd = min(ycd, dist_sq(but, y[i]));
        // cout << rcd << " " << ycd << endl;
        if(rcd < ycd) {
            for(int i = 0; i < n; i++) {
                if(dist_sq(but, r[i]) < ycd) rs ++;
            }
        }
        else if(ycd < rcd) {
            for(int i = 0; i < m; i++) {
                if(dist_sq(but, y[i]) < rcd) ys ++;
            }
        }
        // cout << "DONE ITER" << endl;
    }
    cout << rs << " " << ys << "\n";
    
    return 0;
}