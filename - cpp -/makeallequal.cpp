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

//Codeforces - 2001A

//since you can remove pretty much any element, just remove everything except for the most frequent
//element. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        map<int, int> m;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            m[a[i]] ++;
        }
        int ans = n;
        for(auto i = m.begin(); i != m.end(); i++){
            ans = min(ans, n - i->second);
        }
        cout << ans << "\n";
    }
    
    return 0;
}