#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1520F1

//binary search. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, t;
    cin >> n >> t;
    int k;
    cin >> k;
    int ans = n;
    int low = 1;
    int high = n - 1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        cout << "? " << 1 << " " << mid << endl;
        int nr_zero;
        cin >> nr_zero;
        nr_zero = mid - nr_zero;
        if(nr_zero >= k){
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    cout << "! " << ans << "\n";
    
    return 0;
}