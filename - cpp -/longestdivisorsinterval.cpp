#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1855B

//1 is always included in the longest interval of divisors. 
//don't ask me why D:

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- ){
        ll n;
        cin >> n;
        ll ans = 0;
        while(n % (ans + 1) == 0){
            ans ++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
