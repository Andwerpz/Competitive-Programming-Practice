#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1832B

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, k;
        cin >> n >> k;
        int l = 0;
        int r = n - 1;
        vector<ll> a(n, 0);
        ll sum = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            sum += a[i];
        }
        sort(a.begin(), a.end());
        for(int i = 0; i < k; i++){
            sum -= a[r];
            r --;
        }
        ll ans = sum;
        for(int i = 0; i < k; i++){
            sum += a[r + 1];
            r ++;
            sum -= a[l] + a[l + 1];
            l += 2;
            ans = max(ans, sum);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
