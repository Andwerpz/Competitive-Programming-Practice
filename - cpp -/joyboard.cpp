#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1877C

//casework. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, m, k;
        cin >> n >> m >> k;
        if(k == 1){
            cout << "1\n";
            continue;
        }
        if(k == 2){
            //all multiples of n. 
            ll ans = m / n;
            //any number that is less than n
            ans += min(m, n - 1);
            cout << ans << "\n";
            continue;
        }
        if(k == 3){
            if(m < n) {
                cout << "0\n";
                continue;
            }
            //any number that is greater than n, that is not a multiple of n
            ll ans = (m + 1) - ((m / n) + (n - 1) + 1);
            cout << ans << "\n";
            continue;
        }
        cout << "0\n";
    }
    
    return 0;
}
