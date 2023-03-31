#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1615C

//notice that the operation that you are doing is identical to first inverting the string, then changing 
//one candle that is not lit to being lit. Observe that if you do this operation an even amount of times, the
//total amount of lit candles will not change. 

//also, if you count the number of lit candles after the first operation, if you do it an even amount of times from there, 
//the amount of lit candles will not change. 

//Lets say that x is the number of initially lit candles. So, if the target string doesn't have x or n - x + 1 lit candles, 
//then it is impossible. 

//otherwise, you can do it. Consider two cases, one where you need an even amount of operations, and one where you need an
//odd amount. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;
        int asum = 0;
        int bsum = 0;
        for(int i = 0; i < n; i++){
            asum += a[i] == '1';
            bsum += b[i] == '1';
        }
        if(!(asum == bsum || n - asum + 1 == bsum)) {
            cout << "-1\n";
            continue;
        }
        int ans = n * 2;
        if(n - asum + 1 == bsum) {
            int nans = 0;
            for(int i = 0; i < n; i++){
                nans += a[i] == b[i];
            }
            ans = min(ans, nans);
        }
        if(asum == bsum) {
            int nans = 0;
            for(int i = 0; i < n; i++){
                nans += a[i] != b[i];
            }
            ans = min(ans, nans);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
