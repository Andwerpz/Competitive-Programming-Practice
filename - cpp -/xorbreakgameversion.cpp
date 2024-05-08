#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1934D2

//if the number of bits is even, the person who is currently splitting wins, they can always
//split so that the other person has to take an odd amount of bits

//if the number of bits is odd, then they always have to split into an even and an odd amount

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        bool my_turn = __builtin_popcountll(n) % 2 == 0;
        cout << (my_turn? "first" : "second") << endl; 
        while(true){
            if(my_turn){
                ll most_sig = 0;
                ll tmp = n;
                while(tmp != 1){
                    tmp /= 2;
                    most_sig ++;
                }
                ll p1 = (1ll << most_sig);
                ll p2 = n ^ p1;
                cout << p1 << " " << p2 << endl;
            }
            else {
                ll p1, p2;
                cin >> p1 >> p2;
                if(p1 + p2 == 0){
                    break;
                }
                n = __builtin_popcountll(p1) % 2 == 0? p1 : p2;
            }
            my_turn = !my_turn;
        }
    }
    
    return 0;
}
