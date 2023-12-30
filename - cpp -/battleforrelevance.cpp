#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ACPC 2023 Fall Contest B

//binary search for the minimum suitable number

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int l, d, x;
    cin >> l >> d >> x;
    ld ratio = (ld) x / 100.0;
    int ans = 1e9;
    int low = 0;
    int high = 1e9;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        ld n_ratio = (ld) (l + mid) / (ld) (l + mid + d);
        if(n_ratio >= ratio) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
