#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC Spring 2024 Open Contest - C

//a naive solutionw works, for each element, compute the number of subarrays where it is the "noteworthy" element. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll ans = 0;
        for(int i = 0; i < n; i++){
            ll cur = a[i];
            ll sum = 0;
            int l = i - 1;
            int r = i + 1;
            while(l >= 0 && sum + a[l] < cur) {
                sum += a[l];
                l --;
            }
            for(int j = l + 1; j <= i; j++){
                while(r < n && sum + a[r] < cur) {
                    sum += a[r];
                    r ++;
                }
                ans += r - i;
                sum -= a[j];
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
