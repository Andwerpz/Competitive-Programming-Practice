#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1725B

//We can greedily take the strongest players to be the 'captains' of the teams, and put the weakest players with them. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, d;
    cin >> n >> d;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    int ans = 0;
    for(int i = 0; i < a.size(); i++){
        ll amt = (d + 1 + a[i] - 1) / a[i];
        n -= amt;
        if(n >= 0){
            ans ++;
        }
        else {
            break;
        }
    }
    cout << ans << "\n";
    
    return 0;
}