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

//Codeforces - 2138A

//simulating going forward seems infeasible, but going backwards is extremely easy. 
//what does going backwards look like? it looks like this:
//a* = 2a
//b* = b - a
//and the other way around ofc. Observe that this is only possible if a <= b, and if we're working backwards
//then we stop when a == b so there is only one possible move if a != b. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        ll k, x;
        cin >> k >> x;
        ll a = x, b = (1ll << (k + 1ll)) - x;
        vi ans(0);
        while(a != b) {
            if(a > b) { 
                ans.push_back(2);
                a -= b;
                b *= 2;
            }
            else {  
                ans.push_back(1);
                b -= a;
                a *= 2;
            }
        }
        reverse(ans.begin(), ans.end());
        
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
        cout << "\n";
    }
    
    return 0;
}