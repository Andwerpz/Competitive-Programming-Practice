#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - fractionallotion

//we can directly solve for y:
//1/x + 1/y = 1/n
//1/y = 1/n - 1/x
//y = 1 / (1/n - 1/x)
//y = 1 / ((x - n) / nx)
//y = nx / (x - n)

//so given a x, if nx / (x - n) is an integer, then y exists. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    while(!cin.eof()) {
        ll n = stoi(s.substr(2));
        ll ans = 0;
        for(ll x = n + 1; x < 1e7; x++){
            if((ld) (n * x) / (ld) (x - n) + 1 < x) {
                break;
            }
            ans += (n * x) % (x - n) == 0;
        }
        cout << ans << "\n";
        cin >> s;
    }
    
    return 0;
}
