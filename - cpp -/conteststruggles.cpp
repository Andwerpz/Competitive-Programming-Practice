#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//NWERC 2020 - C

//we can directly compute the average difficulty of the remaining problems. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ld n, k;
    cin >> n >> k;
    ld d, s;
    cin >> d >> s;
    //k * s + (n - k) * x = d * n;
    //x = (d * n - k * s) / (n - k);
    ld x = (d * n - k * s) / (n - k);
    if(x < 0 || x > 100){
        cout << "impossible\n";
    }
    else{
        cout << fixed << setprecision(10) << x << "\n";
    }
    
    return 0;
}
