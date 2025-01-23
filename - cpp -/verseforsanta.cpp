#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Codeforces - 1279B

//just test every way to skip using pfx sum and binary search. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, s;
        cin >> n >> s;
        vl a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        vl pfx(n + 1, 0);
        for(int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + a[i - 1];
        int maxg = 0, skip = 0;
        for(int i = 1; i <= n; i++) if(s >= pfx[i]) maxg = i;
        for(int i = 0; i < n; i++){
            int low = 0, high = n;
            int cg = 0;
            while(low <= high) {
                int mid = low + (high - low) / 2;
                ll camt = pfx[mid] - (mid > i? a[i] : 0);
                if(s >= camt) cg = mid, low = mid + 1;
                else high = mid - 1;
            }
            cg --;
            if(cg > maxg) maxg = cg, skip = i + 1;
        }
        cout << skip << "\n";
    }
    
    return 0;
}