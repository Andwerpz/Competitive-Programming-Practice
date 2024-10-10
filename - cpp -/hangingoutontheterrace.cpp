#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - hangingout

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int l, x;
    cin >> l >> x;
    int ans = 0;
    int sum = 0;
    for(int i = 0; i < x; i++){
        string t;
        cin >> t;
        int next;
        cin >> next;
        if(t == "leave") {
            sum -= next;
        }
        else {
            if(sum + next > l) {
                ans ++;
            }
            else {
                sum += next;
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
