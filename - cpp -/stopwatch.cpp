#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - stopwatch

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    if(n % 2 == 1){
        cout << "still running\n";
        return 0;
    }
    int ans = 0;
    for(int i = 0; i < n / 2; i++){
        int x, y;
        cin >> x >> y;
        ans += y - x;
    }
    cout << ans << "\n";
    
    return 0;
}
