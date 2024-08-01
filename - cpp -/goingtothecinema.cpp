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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        int ans = 0;
        if(a[0] != 0){
            ans ++;
        }
        for(int i = 0; i < n; i++){
            if(i >= a[i] && (i == n - 1 || i + 1 < a[i + 1])) {
                ans ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}