#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC 04-05-2023 - C

//just test all points inside the big circle. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, r;
    cin >> n >> r;
    vector<pair<int, pair<int, int>>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second.first >> a[i].second.second;
    }
    int ans = 0;
    for(int x = -r; x <= r; x++) {
        for(int y = -r; y <= r; y++) {
            if(x * x + y * y > r * r){
                continue;
            }
            for(int i = 0; i < n; i++){
                int dx = a[i].second.first - x;
                int dy = a[i].second.second - y;
                if(dx * dx + dy * dy <= a[i].first * a[i].first) {
                    ans ++;
                    break;
                }
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
