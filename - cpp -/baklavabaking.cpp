#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC Contest 12-01-23 Div. 1 B

//if a number's least significant digit is 0 or 5, then it is divisible by 5. Since we are reversing N, the least
//significant digit cannot be 0, as it cannot be the original N's most significant digit. Thus, the most significant
//digit in the original N has to be 5. 

//Then, all we have to do is count how many numbers from 5 * 10^8 to 6 * 10^8 - 1 are divisible by K. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll nr = 100000000;
        ll ptr = 500000000;
        ll k;
        cin >> k;
        if(ptr % k == 0){
            cout << (nr / k) + (nr % k == 0? 0 : 1) << "\n";
            continue;
        }
        ll diff = k - (ptr % k);
        nr -= diff;
        ptr += diff;
        //cout << ptr << "\n";
        //cout << nr << "\n";
        cout << (nr / k) + (nr % k == 0? 0 : 1) << "\n";
    }
    
    return 0;
}
