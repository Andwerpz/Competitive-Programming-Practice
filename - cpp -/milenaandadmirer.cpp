#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1898B

//note that you should never apply an operation to the last element. 

//then, for the second to last element, you want to split it into the minimum amount of pieces such that they are 
//all less than the last element, and the minimum among the pieces is maximized. 

//just do this greedily from right to left. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll next = a[n - 1];
        ll ans = 0;
        for(int i = n - 2; i >= 0; i--){
            ll parts = (a[i] / next) + (a[i] % next != 0? 1 : 0);
            ans += parts - 1;
            next = a[i] / parts;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
