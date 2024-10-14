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

//Codeforces - 2025A

//just find the largest common prefix, and subtract that from the sum of the two strings. 
//the only exception is if there is no common prefix, in which we just build the two strings 
//independently. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string a, b;
        cin >> a >> b;
        int ans = a.size() + b.size();
        int lcp = 0;
        for(int i = 0; i < min(a.size(), b.size()); i++){
            if(a[i] != b[i]){
                break;
            }
            lcp ++;
        }
        if(lcp > 0){
            ans -= lcp - 1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}