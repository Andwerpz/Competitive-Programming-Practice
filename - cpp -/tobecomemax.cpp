#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1856C

//bruh

//since n is so small, we can just try to maximize every element. 

//when maximizing an element, we just keep track of the bound of elements that we need to increase to increase 
//the current element once. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        ll k;
        cin >> n >> k;
        vector<ll> a(n, 0);
        ll ans = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            ans = max(ans, a[i]);
        }
        for(int i = 0; i < n; i++){
            ll r = i;
            ll curans = a[i];
            ll cur = a[i];
            ll cnt = 0;
            while(true) {
                while(r != n && a[r] <= cur) {
                    cnt += cur - a[r];
                    r ++;
                    cur --;
                }
                if(r == n || cnt > k){
                    break;
                }
                ll inc = a[r] - cur;
                ll diff = r - i;
                if(inc * diff + cnt <= k){
                    cur += inc;
                    curans += inc;
                    cnt += inc * diff;
                    continue;
                }
                ll amt = (k - cnt) / diff;
                if(amt < 0){
                    break;
                }
                cur += amt;
                curans += amt;
                break;
            }
            ans = max(ans, curans);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
