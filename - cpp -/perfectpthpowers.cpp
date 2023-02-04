#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 03 G

//note that x can be negative. 

//the currently implemented solution is to generate all primes from 2 to sqrt(2^32) or 2^16, and then use those primes to 
//generate the prime factorization of x. 

//i think the intended solution is to generate all perfect powers of numbers from 2 to 2^16 that are less than 2^32. Since you 
//can only raise a number from 2 to 2^16 to a maximum of 32nd power before it gets bigger than 2^32, you can just store all the perfect
//powers into a map and use that to answer queries. 

//note that if x is negative, then p can't be even. 

int gcd(int a, int b) {
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    //linear sieve
    const ll N = (int) sqrt(((ll)1) << 33);
    vector<ll> lp(N+1);
    vector<ll> pr;
    for (ll i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; i * pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
    ll n;
    cin >> n;
    while(n != 0){
        bool isNeg = false;
        if(n < 0){
            isNeg = true;
            n = -n;
        }
        int pow = 0;
        for(int i = 0; i < pr.size(); i++){
            int cnt = 0;
            while(n % pr[i] == 0){
                //cout << pr[i] << endl;
                cnt ++;
                n /= pr[i];
            }
            if(cnt == 0){
                continue;
            }
            pow = gcd(pow, cnt);
        }
        if(n != 1){
            pow = 1;
        }
        if(isNeg) {
            while(pow % 2 == 0) {
                pow /= 2;
            }
        }
        cout << pow << "\n";
        cin >> n;
    }

    return 0;
}
