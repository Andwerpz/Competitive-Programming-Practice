#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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
        ll q = r_1 / r_0;
        r_0 = r_0 - r_1 * q;
        s_0 = s_0 - s_1 * q;
        t_0 = t_0 - t_1 * q;
        swap(r_0, r_1);
        swap(s_0, s_1);
        swap(t_0, t_1);
    }
    return {r_0, s_0, t_0};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    
    return 0;
}
