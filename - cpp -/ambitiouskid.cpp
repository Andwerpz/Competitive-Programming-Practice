#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//COMPFEST 15 A

//what's the minimum amount of moves to make an element 0?
//just take the minimum absolute value. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int ans = 1e9;
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        ans = min(ans, abs(next));
    }
    cout << ans << "\n";
    
    return 0;
}
