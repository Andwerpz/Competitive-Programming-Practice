#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1836B

//for each person, you can initially give them 1 under the round up threshold. 
//so, the current answer is (g / 2 - (g % 2 == 0)) * n. 

//then, since you can only save a multiple of g silver coins, subtract from ans, 
//ans % g. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, k, g;
        cin >> n >> k >> g; 
        ll ans = (g / 2 - (g % 2 == 0)) * n;
        ll tot = g * k;
        ans = min(ans, tot);
        ans -= ans % g;
        cout << ans << "\n";
    }
    
    return 0;
}
