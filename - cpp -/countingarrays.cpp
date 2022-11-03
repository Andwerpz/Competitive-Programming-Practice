#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1749D

//notice that ambiguous arrays and un-ambiguous arrays are mutually exclusive. We can count the amount of
//un-ambiguous arrays, and subtract that amount from the number of total arrays to get the number of ambiguous arrays. 

//solving for the total amount of arrays is easy, it is simply m^1 + m^2 + m^3 + ... + m^n. 

//solving for the amount of un-ambiguous arrays is more difficult. 

//notice that given an arbitrary array a, there is always one removal sequence that can always be done;
//always remove the first element, since gcd(x, 1) = 1. 

//thus it follows that if you can ever remove an element that is not the first, then that array must be ambiguous. 
//so the task is to count the number of arrays where we can only ever remove the first element. 

//notice that constructing such an array is not as simple as setting a_i = x * i, since gcd(a_i, j) must hold for 1 <= j <= i.
//since a_i must share a factor with all numbers from 1 to i, it must be a multiple of the product of primes from 1 to i. 

ll pow(ll a, ll p, ll mod) {
    if(p == 0){
        return 1;
    }
    ll ans = pow(a, p / 2, mod);
    ans = (ans * ans) % mod;
    if(p % 2 == 1){
        ans *= a;
        ans %= mod;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ll m;
    cin >> n >> m;
    ll mod = 998244353;
    ll ans = 0;
    vector<bool> isPrime(n + 1, true);
    for(int i = 2; i < isPrime.size(); i++){
        if(isPrime[i]) {
            for(int j = i * i; j < isPrime.size(); j += i){
                isPrime[j] = false;
            }
        }
    }
    for(int i = 1; i <= n; i++){
        ans += pow(m % mod, i, mod);
        ans %= mod;
    }
    ll pProd = 1;
    ll sub = 1;
    for(int i = 1; i <= n; i++){
        if(pProd > m){
            break;
        }
        if(isPrime[i]){
            pProd *= i;
        }
        sub *= (m / pProd) % mod;
        sub %= mod;
        ans -= sub;
        if(ans < 0){
            ans += mod;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
