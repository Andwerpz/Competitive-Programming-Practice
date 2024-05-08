#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1946B

//first, find the subarray with the maximum value (just need the value)
//then, put that value into the maximum subarray, essentially doubling the value. 
//keep doubling. print the final value.  

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll mod = 1e9 + 7;
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<ll> a(n);
        ll sum = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            sum += a[i];
        }
        ll mx_sum = 0;
        ll pfx = 0;
        for(int i = 0; i < n; i++){
            pfx += a[i];
            if(a[i] > pfx) {
                pfx = a[i];
            }
            mx_sum = max(mx_sum, pfx);
        }
        mx_sum %= mod;
        ll add = 0;
        for(int i = 0; i < k; i++){
            add += mx_sum;
            add %= mod;
            mx_sum *= 2;
            mx_sum %= mod;
        }
        sum += add;
        sum %= mod;
        if(sum < 0){
            sum += mod;
            sum %= mod;
        }
        cout << sum << "\n";
    }
    
    return 0;
}
