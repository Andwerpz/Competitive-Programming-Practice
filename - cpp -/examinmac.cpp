#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1935D

//it might be easier to count the bad pairs, than directly counting the good ones. 

//let's try to plot the bad pairs on the xy plane. For each element A in s, the point (0, A) is bad. 
//then, (1, A + 1), (2, A + 2), ... (C - A, C) are all bad. Similarly, (1, A - 1) to 
//(floor(A / 2), A - floor(A / 2)) are also bad. 

//the problem now is that we might double count. This is actually relatively easy to rectify; for each 
//element A, we just count the number of elements before it that share the same parity. This is 
//the exact amount of double counting. If you draw the tiles on the grid, you'll see what i mean
//(trust me bro)

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, c;
        cin >> n >> c;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll ans = (c + 1) * (c + 2) / 2;
        ll p0 = 0;
        ll p1 = 0;
        for(int i = 0; i < n; i++){
            ll low = a[i] / 2;
            ll high = c - a[i];
            ans -= low + high + 1;
            ans += (a[i] % 2 == 0? p0 : p1);
            p0 += a[i] % 2 == 0;
            p1 += a[i] % 2 == 1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
