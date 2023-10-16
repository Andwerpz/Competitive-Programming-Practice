#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1875A

//since you can use any tool at any time, we can just sum the maximum contributions for each tool. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll a, b, n;
        cin >> a >> b >> n;
        vector<ll> x(n);
        ll ans = b;
        for(int i = 0; i < n; i++){
            cin >> x[i];
            ans += min(x[i], a - 1);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
