#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//1673D

//to check if there are no possible 'a' progressions, there has to be a value in c that 
//doesn't exist in b. To check this, you need to check if any of these are true
//1. c-increment % b-increment != 0
//2. first element of c isn't contained in b
//3. last element of c isn't contained in b.

//to check if there are infinitely many 'a' progressions, you just need to check if
//last element of c + cInc or first element of c - cInc isn't in b.

//if both of the above aren't true, then there is a non-zero finite amount of sequences. 

//find all values, i, that lcm(i, bInc) == cInc. The answer is the sum of (cInc / i) ^ 2.

bool progressionContains(ll start, ll inc, ll amt, ll val){
    if(val < start){
        return false;
    }
    ll diff = val - start;
    if(diff % inc != 0){
        return false;
    }
    ll incAmt = diff / inc;
    if(incAmt > (amt - 1)){
        return false;
    }
    return true;
}

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

ll lcm(ll a, ll b){
    return (a * b) / gcd(a, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    ll mod = 1e9 + 7;
    cin >> t;
    while(t-- > 0){
        ll b, bInc, bNum, c, cInc, cNum;
        cin >> b >> bInc >> bNum >> c >> cInc >> cNum;
        //check if there are no a
        //increment not the same, and more than 1 element
        //elements contained in c not in b, 
        ll lastC = c + (cInc * cNum) - cInc;
        if((cInc % bInc != 0 && cNum > 1) || !progressionContains(b, bInc, bNum, lastC) || !progressionContains(b, bInc, bNum, c)){
            cout << "0\n";
            continue;
        }
        //check if there is infinite a
        if(!progressionContains(b, bInc, bNum, lastC + cInc) || !progressionContains(b, bInc, bNum, c - cInc)){
            cout << "-1\n";
            continue;
        }
        //there is a non-zero finite amount of progressions
        ll ans = 0;
        //calc divisors of cInc that are not multiples of bInc
        for(ll i = 1; i * i <= cInc; i++){
            if(lcm(i, bInc) == cInc){
                ans += max((ll) pow(cInc / i, 2ll), (ll) 1);
                ans %= mod;
            }
            if(i * i == cInc){
                break;
            }
            ll other = cInc / i;
            if(lcm(other, bInc) == cInc){
                ans += max((ll) pow(cInc / other, 2ll), (ll) 1);
                ans %= mod;
            }  
        }
        cout << ans << endl;
    }
    
    return 0;
}
