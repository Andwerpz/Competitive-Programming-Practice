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

//Codeforces - 2084D

//to raise the mex, we need to guarantee that the final sequence will have a 0, then a 1, and so on. 

//To guarantee a 0, we can use pidgeonhole. If we place m + 1 0s at least k apart, then one removal
//can remove at most 1 zero, therefore there must be a zero remaining. 

//can do the same with the other numbers. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        int p = n / (m + 1);
        vi ans(n);
        // p = max(p, k);
        if(p < k) {
            for(int i = 0; i < n; i++){
                ans[i] = min(i % k, p - 1);
            }
        }
        else {
            for(int i = 0; i < n; i++){
                ans[i] = i % p;
            }
        }
        for(int i = 0; i < n; i++) cout << ans[i] << " ";
        cout << "\n";
    }
    
    return 0;
}