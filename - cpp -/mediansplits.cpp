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

//Codeforces - 2103C

//observe that we only care about whether a number is <= k or > k. Lets say b[i] = 1 if a[i] <= k and -1 otherwise. 
//then, a subarray [l, r) will have median <= k iff b[l, r) >= 0. 

//since we're taking the median of the prefix, suffix, and middle, we just need to fix two of the medians to be above k. 
//we can test all 3 combinations in linear time. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) a[i] = a[i] <= k? 1 : -1;
        int bud = 0;
        for(int i = 0; i < n; i++) bud += a[i];
        vi pfx(n, 0), sfx(n, 0);
        pfx[0] = a[0], sfx[n - 1] = a[n - 1];
        for(int i = 1; i < n; i++) pfx[i] = pfx[i - 1] + a[i];
        for(int i = n - 2; i >= 0; i--) sfx[i] = sfx[i + 1] + a[i];
        bool is_valid = false;
        //prefix - suffix
        {
            int pind = 1e9, sind = -1;
            for(int i = 0; i < n; i++) if(pfx[i] >= 0) {pind = i; break;}
            for(int i = n - 1; i >= 0; i--) if(sfx[i] >= 0) {sind = i; break;}
            if(pind < sind) is_valid = true;
        }   
        //prefix - mid
        {
            int minp = 1e9;
            for(int i = 0; i < n; i++){
                if(pfx[i] >= minp) is_valid = true;
                if(pfx[i] >= 0) minp = min(minp, pfx[i]);
            }
        }   
        //suffix - mid
        {
            int minp = 1e9;
            for(int i = n - 1; i >= 0; i--){
                if(sfx[i] >= minp) is_valid = true;
                if(sfx[i] >= 0) minp = min(minp, sfx[i]);
            }
        }
        cout << (is_valid? "YES" : "NO") << "\n";
    }
    
    return 0;
}