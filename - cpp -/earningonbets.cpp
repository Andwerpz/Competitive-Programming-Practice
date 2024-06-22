#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1979C

//let's have a pool of money that we bet out of, and let the size of this pool be the LCM of all the money 
//multipliers for all the bets. 

//then, for each bet, we'll bet LCM / a[i], where a[i] is the money multiplier for that bet. We can see that if we win
//this bet, then we'll win LCM money. 

//so, this works only if sum(LCM / a[i]) < LCM, or equivalently sum(1 / a[i]) < 1. to be honest, i don't know why
//this works for all cases. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll lcm = 1;
        for(int i = 0; i < n; i++){
            lcm = (lcm * a[i]) / gcd(lcm, a[i]);
        }
        int sum = 0;
        vector<int> ans(n);
        for(int i = 0; i < n; i++){
            ans[i] = lcm / a[i];
            sum += ans[i];
        }
        if(sum >= lcm) {
            cout << "-1\n";
            continue;
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}