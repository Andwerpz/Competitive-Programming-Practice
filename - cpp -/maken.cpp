#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC139B

//let's first assert that a >= b. If they are not, then we can simply swap them. 
//also, assign y = min(y, x * a), and z = min(z, x * b).

//first, if a >= 1e5, then we can simply do a brute force solution; For every amount of 'a' we use,
//we can find the maximum amount of 'b' to use, then use 1s for the remainder. 

//else; a, b < 1e5. Then, we can just fix the amount of 1s we use, and look for the optimal combination
//of a and b to fill the remainder. 

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, a, b, x, y, z;
        cin >> n >> a >> b >> x >> y >> z;
        if(a < b) {
            swap(a, b);
            swap(y, z);
        }
        if(y > x * a) {
            y = x * a;
        }
        if(z > x * b) {
            z = x * b;
        }
        if(a >= 1e4) {
            ll ans = 2e18;
            ll nr_a = 0;
            while(nr_a * a <= n) {
                ll nr_b = (n - nr_a * a) / b;
                ll nr_1 = n - nr_a * a - nr_b * b;
                ans = min(ans, nr_1 * x + nr_a * y + nr_b * z);
                nr_a ++;
            }
            cout << ans << "\n";
            continue;
        }
        ll ans = 2e18;
        ll g = (a * b) / gcd(a, b);
        ll nr_gcd_a = g / a;
        //cout << "nr_gcd_a : " << nr_gcd_a << "\n";
        for(ll i = 0; i < nr_gcd_a; i++){
            ll base_sum = a * i;
            if(base_sum > n) {
                continue;
            }
            ll tgt = n - base_sum;
            ll rem = tgt % b;
            ll base_cost = rem * x + i * y;
            tgt -= rem;
            ll low = 0;
            ll high = tgt / g;
            //cout << "REM : " << rem << " " << high << " " << low << "\n";
            // ll low_ans = base_cost + (tgt / b) * z;
            // ll high_ans = base_cost + (tgt / g) * nr_gcd_a * y + ((tgt % g) / b) * z;
            while(high - low + 1 >= 4) {
                ll m0 = low + (high - low + 1) / 3;
                ll m1 = m0 + (high - low + 1) / 3;
                ll m0_ans = base_cost + m0 * nr_gcd_a * y + ((tgt - m0 * g) / b) * z;
                ll m1_ans = base_cost + m1 * nr_gcd_a * y + ((tgt - m1 * g) / b) * z;
                if(m0_ans <= m1_ans) {
                    high = m1;
                }
                else {
                    low = m0;
                }
            }
            for(ll j = low; j <= high; j++){
                ll c_ans = base_cost + j * nr_gcd_a * y + ((tgt - j * g) / b) * z;
                ans = min(ans, c_ans);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
