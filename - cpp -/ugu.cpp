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

//Codeforces - 1732B

//start from the front and greedily flip any '1's you see. Note that you can leave the last section of '1's. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        s = "0" + s;
        n += 1;
        int ans = 0;
        for(int i = 0; i < n;) {
            int r = i;
            while(r != n && s[r] == s[i]) r ++;
            ans ++;
            i = r;
        }
        ans -= 2;
        ans = max(ans, 0);
        cout << ans << "\n";
    }
    
    return 0;
}