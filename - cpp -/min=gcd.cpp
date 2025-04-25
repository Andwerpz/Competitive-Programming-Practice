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

//Codeforces - 2084B

//note that the minimum in the min portion needs to be \leq the minimum in the gcd portion. This is
//because the gcd will always be \leq min in the gcd portion. Therefore, we have to place the global array 
//minimum in the min portion. After that, we can freely choose the other elements to be in the gcd
//portion to try to make the gcd equal to the minimum. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vl a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        int minind = 0;
        for(int i = 0; i < n; i++){
            if(a[i] < a[minind]) minind = i;
        }
        ll minval = a[minind];
        ll g = 0;
        for(int i = 0; i < n; i++){
            if(i == minind) continue;
            if(a[i] % minval == 0) g = gcd(g, a[i]);
        }
        cout << (g == minval? "YES" : "NO") << "\n";
    }
    
    return 0;
}