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

//Codeforces - 1887 A1, A2

//when m = 1, we can just binary search for the answer. The strat is to sort both arrays into ascending order, 
//and remove the greatest elements from a and remove smallest elements from b. This is sufficient for the easy version. 

//for the hard version, m can be very large. The idea is to start m at 1, and slowly increment it upwards. 
//we can notice that the answer will only change at specific points, namely when it is equal to some value in a or b. 
//the implementation is pretty tricky. 

bool is_valid(vi& a, vi& b, int val) {
    for(int i = 0; i < a.size() - val; i++){
        if(a[i] >= b[i + val]) {
            return false;
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vi a(n), b(n);
        a[0] = 1;
        for(int i = 1; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int low = 0;
        int high = n;
        ll ans = high;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(is_valid(a, b, mid)) {
                ans = min(ans, (ll) mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        //we've found the answer for when m = 1. 
        ll sum = 0;
        ll mptr = 1;
        int aptr = 1;
        int bptr = ans;
        while(aptr <= n - ans && (aptr != n || bptr != n)) {
            // cout << "MPTR : " << mptr << " " << aptr << " " << bptr << " " << ans << "\n";
            if(aptr != n && (bptr == n || a[aptr] < b[bptr])) {
                ll diff = a[aptr] - mptr;
                mptr = a[aptr];
                sum += diff * ans;
                // cout << "APTR : " << diff << " " << diff * ans << "\n";
                if(mptr > m) {
                    sum += ans * (m - mptr + 1);
                    mptr = m + 1;
                    break;
                }
                aptr ++;
                if(bptr != n){
                    bptr ++;
                }
            }
            else {
                ll diff = b[bptr] - mptr;
                mptr = b[bptr];
                sum += diff * ans;
                // cout << "BPTR : " << diff << " " << diff * ans << "\n";
                if(mptr > m){
                    sum += ans * (m - mptr + 1);
                    mptr = m + 1;
                    break;
                }
                bptr ++;
                ans ++;
            }
        }
        // cout << "REM : " << mptr << " " << ans * (m - mptr + 1) << "\n";
        sum += ans * (m - mptr + 1);
        cout << sum << "\n";
    }
    
    return 0;
}