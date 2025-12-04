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

//Codeforces - 2122B

//if the piles just have 0s, then the answer is simply half the sum of absolute differences between original and 
//target sizes. 

//with the 1s, you need to get them on top first, so do the same, but also factor that in. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        ll odiff = 0, zdiff = 0, ans = 0;
        for(int i = 0; i < n; i++){
            ll a, b, c, d;
            cin >> a >> b >> c >> d;
            odiff += abs(a - c);
            zdiff += abs(b - d);
            //put ones on top
            if(d < b) ans += min(a, c);
        }
        ans += odiff / 2;
        ans += zdiff / 2;
        cout << ans << "\n";
    }
    
    return 0;
}