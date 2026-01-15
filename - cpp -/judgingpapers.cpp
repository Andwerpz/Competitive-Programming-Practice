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

//2025 ICPC Asia Chengdu Regional Contest - J

//if a paper is already passing, no need to select it
//only select papers that are not already passing, but will pass if you select them. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, m, k, b;
        cin >> n >> m >> k >> b;
        vi x(n, 0), y(n, 0);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int s;
                cin >> s;
                x[i] += s;
                if(s >= 1) s --;
                else s ++;
                y[i] += s;
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++) {
            if(x[i] >= k) {
                ans ++;
                continue;
            }
            if(y[i] >= k && b) {
                b --;
                ans ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}