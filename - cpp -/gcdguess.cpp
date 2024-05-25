#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1665D

//we can find x bit by bit starting from the least significant bit. 

//to check if a bit b exists, we first must ensure that x + a and x + a + b is divisible by b / 2, 
//then, check if gcd(x + a, x + a + b) = b. Depending on whether or not it's equal, the bit will or will
//not exist. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        bool found_bit = false;
        vector<bool> bits(30, false);
        for(int i = 0; i < bits.size(); i++){
            if(!found_bit && i == bits.size() - 1) {
                bits[bits.size() - 1] = true;
                break;
            }
            //look at what we already know to compute the offset
            ll offset = 0;
            bool carry = false;
            for(int j = 0; j < i; j++){
                if(bits[j] && (j == 0 || !bits[j - 1]) && !carry) {
                    offset += (1ll << j);
                    carry = true;
                }
                else if(!bits[j] && carry) {
                    offset += (1ll << j);
                }
            }
            //checking for divisiblity by (1 << (i + 1))
            ll a, b;
            if(offset == 0){
                a = (1 << (i + 1));
                b = (2 << (i + 1));
            }
            else {
                a = offset;
                b = offset + (1 << (i + 1));
            }
            cout << "? " << a << " " << b << endl;
            ll g;
            cin >> g;
            bits[i] = g != (1 << (i + 1));
            if(carry) {
                bits[i] = !bits[i];
            }
            found_bit |= bits[i];
        }
        ll x = 0;
        for(int i = 0; i < bits.size(); i++){
            x += (bits[i] << i);
        }
        cout << "! " << x << endl;
    }
    
    return 0;
}
