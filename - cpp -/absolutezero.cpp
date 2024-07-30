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

//Codeforces - 1991C

//we can continually halve the maximum element by putting in decreasing powers of 2. This only works
//if all the numbers are the same parity, so we check that first. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        bool even = true, odd = true;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            if(a[i] % 2 == 0){
                odd = false;
            }
            if(a[i] % 2 == 1){
                even = false;
            }
        }
        if(!even && !odd) {
            cout << "-1\n";
            continue;
        }
        vi ans(0);
        for(int i = 29; i >= 0; i--){
            ans.push_back(1 << i);
        }
        if(even){
            ans.push_back(1);
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}