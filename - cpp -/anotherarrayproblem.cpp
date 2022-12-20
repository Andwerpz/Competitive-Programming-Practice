#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1763C

//notice that you can make any range of numbers equal to 0 by doing the operation twice over the same range. 

//lets try to make all elements in a equal to max(a). If max(a) is present at the left or right end of a, then we can just make
//the other end 0, and then perform the operation over the whole array. 
//if max(a) is present in the center, we can make both ends 0, and then do operations from the center. 

//what are the limitations? well, if n <= 3, then it is not guaranteed that we can make 2 elements equal to 0, 
//and keep max(a). 

//thus, if n >= 4, then the answer is simply n * max(a), else, we can do brute force. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> a(n);
        ll max = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            max = std::max(max, a[i]);
        }
        if(n >= 4){
            cout << max * (ll) n << "\n";
            continue;
        }
        //do brute force
        if(n == 2){
            cout << std::max(a[0] + a[1], abs(a[0] - a[1]) * 2) << "\n";
            continue;
        }
        ll ans = 0;
        ans = std::max(ans, a[0] + a[1] + a[2]);
        ans = std::max(ans, a[0] * 3);
        ans = std::max(ans, a[2] * 3);
        ll l = abs(a[0] - a[1]);
        ll r = abs(a[1] - a[2]);
        ans = std::max(ans, l * 2 + a[2]);
        ans = std::max(ans, r * 2 + a[0]);
        ans = std::max(ans, abs(l - r) * 2 + l);
        ans = std::max(ans, abs(l - r) * 2 + r);
        ans = std::max(ans, l * 3);
        ans = std::max(ans, r * 3);
        cout << ans << "\n";
    }
    
    return 0;
}
