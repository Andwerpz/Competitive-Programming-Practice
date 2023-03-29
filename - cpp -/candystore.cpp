#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1798C

//some sort of greedy + gcd + lcm 
//but whyyyyyyy...

//a[i] * b[i] = the total price of all the candies of type i. 
//if candy type i and j can have the same price, then that means that gcd(a[i] * b[i], a[j] * b[j]) must be divisible by 
//both b[i] and b[j], or in other words, gcd(a[i] * b[i], a[j] * b[j]) % lcm(b[i], b[j]) = 0. 

//for some reason, if we just start at one end, and greedily append on values, then we can generate the minimum. 

ll gcd(ll a, ll b) {
    return b == 0? a : gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    int cnt = 0;
    while(t-- > 0){
        cnt ++;
        int n;
        cin >> n;
        int ans = 1;
        ll g = 0;
        ll minB = INT32_MAX;
        for(int i = 0; i < n; i++){
            ll a, b;
            cin >> a >> b;
            g = gcd(g, a * b);
            if(i == 0){
                minB = b;
            }
            minB = (b * minB) / gcd(b, minB);
            //cout << a << " " << b << " " << g << " " << minB << "\n";
            if(g % minB != 0){
                g = a * b;
                minB = b;
                ans ++;
                //cout << "ADD 1" << "\n";
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
