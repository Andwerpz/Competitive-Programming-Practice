#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Calgary 2022 - B

//compute the expected number of flips to stop flipping, and divide by the probability that 
//we generate a number under c. 

ld calc_ev(ll pow2, ll base, ll c) {
    if(pow2 == 0){
        return 0;
    }
    ll amt = (1 << (pow2 - 1));
    if(base + (1 << pow2) < c){
        return pow2;
    }
    else if(base >= c){
        return 0;
    }
    ld ans = 1 + (calc_ev(pow2 - 1, base, c) + calc_ev(pow2 - 1, base + amt, c)) / 2.0;
    // cout << "ANS : " << pow2 << " " << base << " " << ans << "\n";
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll c;
    cin >> c;
    ll pow2 = 0;
    ll ptr = 1;
    while(ptr < c){
        ptr *= 2;
        pow2 ++;
    }
    // cout << "PTR : " << ptr << "\n";
    ld p_succ = (c / (ld) ptr);
    ld ev = calc_ev(pow2, 0, c);
    ld ans = ev / p_succ;
    // cout << "EV : " << ev << "\n";
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}