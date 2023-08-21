#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1860B

//we can first try to use m % k 1 coins, to make the remaining m a multiple of k. 
//then, we use m / k k coins. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int m, k, a, b;
        cin >> m >> k >> a >> b;
        int ans = 0;
        //try to gather m % k 1 value coins
        {
            int amt = m % k;
            amt = min(amt, a);
            a -= amt;
            m -= amt;
        }
        b += a / k;
        //use as many k coins as you can
        {
            int amt = m / k;
            amt = min(amt, b);
            b -= amt;
            m -= amt * k;
        }
        {
            int amt = m % k;
            m -= amt;
            ans += amt;
        }
        //use value k fancy coins
        {
            int amt = m / k;
            m -= amt * k;
            ans += amt;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
