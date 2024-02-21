#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC NAQ 2023 - E

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for(auto &x : v) cin >> x.first >> x.second;

    int cnt = 0;
    for(int i = 0; i < n - 2; i++) {
        //trying i + 1, i + 2, i + 3
        bool ok = 1;
        for(int j = 0; j < 3; j++) {
            if(v[i+j].first <= i + 1 && v[i+j].second >= i + 3) {

            } else {
                ok = 0;
            }
        }
        if(ok) {
            cnt++;
            i += 2;
        }
    }
    cout << cnt << '\n';
    return 0;
}
