#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1916C

//the operation just takes the sum of the two numbers, and sets the ones bit to 0. 
//thus, we will only decrease the value if we add two numbers of different parity. 

//the numbers that can actually lose value are the odd ones, so the optimal move for masha is to
//only take pairs of odd numbers to conserve as much value as possible. Olya on the other hand
//always wants to take one odd and one even number. 

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
        ll pfx = 0;
        int nr_even = 0;
        int nr_odd = 0;
        for(int i = 0; i < n; i++){
            pfx += a[i];
            if(a[i] % 2 == 1){
                nr_odd ++;
                pfx --;
            }
            else {
                nr_even ++;
            }
            ll ans = pfx;
            if(i == 0){
                ans = a[i];
            }
            //masha only takes odds
            {
                int nr_moves = nr_odd / 3;
                int rem_odd = nr_odd - nr_moves * 3;
                ans = max(ans, ans + nr_moves * 2 + (rem_odd / 2) * 2);
            }
            cout << ans << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
