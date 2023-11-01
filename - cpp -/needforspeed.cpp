#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2017 - E

ld epsilon = 1E-10;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    int n, t; cin >> n >> t;
    vector<pair<int,int>> segs(n);
    for(auto &x: segs) cin >> x.first >> x.second;

    ld lo = -1e18;
    ld hi = 1e18;

    while(hi - lo > epsilon) {
        ld m = (lo + hi) / 2;
        ld time = 0;
        bool flag = false;
        for(int i = 0; i < n; i++) {
            time += segs[i].first / (segs[i].second + m);
            if(segs[i].second + m < 0) {
                lo = m;
                flag = true;
                break;
            }
        }
        if(flag) continue;
        if(time > t) {
            lo = m;
        } else {
            hi = m;
        }
    }
    cout << fixed << setprecision(10) << lo << '\n';

    return 0;
}
