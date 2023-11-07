#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1891C

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        vector<bool> contr(n, false);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        int l = 0;
        int r = n - 1;
        ll ans = 0;
        while(l < r) {
            ll take = min(a[l], a[r]);
            ans += take;
            a[l] -= take;
            a[r] -= take;
            contr[r] = true;
            if(a[r] == 0){
                r --;
            }
            if(a[l] == 0){
                l ++;
            }
        }
        if(l > r) {
            for(int i = 0; i < n; i++){
                ans += contr[i];
            }
            cout << ans << "\n";
            continue;
        }
        if(a[l] == 1){
            ans ++;
        }
        else {
            contr[l] = true;
            ans += a[l] / 2 + (a[l] % 2);
        }
        for(int i = 0; i < n; i++){
            ans += contr[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
