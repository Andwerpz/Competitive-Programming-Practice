#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1852A

//i just wrote down a bunch of sample cases, and saw a pattern. 
//this is the implementation of that pattern i saw. 

//go read the tutorial for a better explanation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        ll k;
        cin >> n >> k;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        a.push_back(1e18);
        if(a[0] != 1){
            cout << "1\n";
            continue;
        }
        ll ans = 1;
        k --;
        ll carry = 0;
        for(int i = 0; i < n; i++){
            ans ++;
            //cout << "ANS : " << ans << "\n";
            ll inc = i + 1;
            ll toNext = a[i + 1] - ans;
            //cout << "TO NEXT : " << toNext << " " << inc << "\n";
            if(carry != 0){
                ll add = min(carry, toNext);
                //cout << "CARRY : " << carry << " " << add << "\n";
                ans += add;
                toNext -= add;
                carry -= add;
            }
            while(ans < a[i + 1] && k != 0) {
                //cout << "INC : " << ans << " " << k << "\n";
                toNext -= inc;
                ans += inc;
                k --;
            }
            if(ans < a[i + 1]){
                break;
            }
            carry += ans - a[i + 1];
            ans = a[i + 1];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
