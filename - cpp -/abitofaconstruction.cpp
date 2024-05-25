#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1957B

//if n = 1, then you have to print out k. 

//otherwise, n >= 2. For the first element, just print out the largest 1 minus some power of 2. This will 
//guarantee that we get the most bits possible. The second number, you just print out the remaining difference to
//k, and the rest can be 0s. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        if(n == 1){
            cout << k << "\n";
            continue;
        }
        int pow2 = 2;
        while(pow2 * 2 - 1 <= k){
            pow2 *= 2;
        }
        pow2 --;
        cout << pow2 << " " << k - pow2 << " ";
        for(int i = 0; i < n - 2; i++){
            cout << "0 ";
        }
        cout << "\n";
    }
    
    return 0;
}
