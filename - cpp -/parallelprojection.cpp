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

int calc(int a, int b, int f, int g, int x, int y){
    return abs(a - x) + abs(b - y) + abs(f - x) + abs(g - y);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int w, d, h;
        cin >> w >> d >> h;
        int a, b, f, g;
        cin >> a >> b >> f >> g;
        int ans = 1e9;
        for(int i = 0; i <= w; i++){
            ans = min(ans, calc(a, b, f, g, i, 0));
            ans = min(ans, calc(a, b, f, g, i, d));
        }
        for(int i = 0; i <= d; i++){
            ans = min(ans, calc(a, b, f, g, 0, i));
            ans = min(ans, calc(a, b, f, g, w, i));
        }
        ans += h;
        cout << ans << "\n";
    }
    
    return 0;
}