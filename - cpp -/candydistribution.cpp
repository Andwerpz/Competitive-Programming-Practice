#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Kattis - candydistribution

//we have K * X + 1 = C * Y, where we want to solve for positive integer X and Y. Rearranging, we get
//C * Y - K * X = 1

//observe that the right side must be a multiple of gcd(C, K), therefore gcd(C, K) = 1. If this is not the case, 
//then it's impossible. 

//Otherwise, we can find a solution using the extended euclidean algorithm. 

//Standard euclidean algorithm
ll gcd(ll a, ll b) {
    return b == 0? a : gcd(b, a % b);
}

//Extended euclidian algorithm. 
//use if you want to find integer solutions for x, y in equations of form ax + by = gcd(a, b). 
vector<ll> extended_euclid(ll a, ll b) {
    ll r_0 = a; ll r_1 = b; //gcd
    ll s_0 = 1; ll s_1 = 0; //x
    ll t_0 = 0; ll t_1 = 1; //y
    while(r_1 != 0){
        ll q = r_0 / r_1;
        r_0 = r_0 - r_1 * q;
        s_0 = s_0 - s_1 * q;
        t_0 = t_0 - t_1 * q;
        ll tmp = r_0;
        r_0 = r_1;
        r_1 = tmp;
        tmp = s_0;
        s_0 = s_1;
        s_1 = tmp;
        tmp = t_0;
        t_0 = t_1;
        t_1 = tmp;
    }
    return {r_0, s_0, t_0};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll k, c;
        cin >> k >> c;
        if(gcd(k, c) != 1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        vector<ll> ans = extended_euclid(-k, c);
        ll rans = ans[2];
        if((c * ans[2]) % k != 1) {
            rans = ans[2] * (c - 1) + 1;
        }
        cout << rans << "\n";
    }
    
    return 0;
}
