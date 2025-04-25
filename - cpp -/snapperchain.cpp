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

//Kattis - snapperhard

//the snapper chain is just a binary counter lol. Snappers will toggle if they are *receiving power*.
//so the lightbulb is on iff all the snappers are on, so this happens iff k === 2^n - 1 mod 2^n. 

bool calc_state(int n, int k) {
    if(n == 0 && k == 0) return true;
    if(n > k) return false;
    int pow2 = 1;
    while(n >= pow2 * 2 || k >= pow2 * 2) pow2 *= 2;
    n %= pow2;
    k %= pow2;
    return calc_state(n, k);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    int casi = 0;
    while(t--){
        casi ++;
        int n, k;
        cin >> n >> k;
        // vb a(n, false);
        // for(int i = 0; i < k; i++){
        //     vb na = a;
        //     for(int j = n - 1; j >= 1; j--) na[j] = a[j] ^ a[j - 1];
        //     na[0] = a[0] ^ 1;
        //     a = na;
        //     for(int j = 0; j < n; j++) cout << na[j];
        //     cout << "\n";
        // }
        // int mxk = 0;
        // while(k & (1 << mxk)) {
        //     mxk ++;
        // }
        // mxk = (1 << mxk) - 1;
        // bool ans = k <= mxk;
        // for(int i = 0; i < k; i++) {
        //     for(int j = 0; j < n; j++) {
        //         cout << calc_state(j, i);
        //     }
        //     cout << "\n";
        // }
        // bool ans = true;
        // while(n != 0) ans &= calc_state(n --, k);
        k %= (1 << n);
        bool ans = k == (1 << n) - 1;
        cout << "Case #" << casi << ": " << (ans? "ON" : "OFF") << "\n";
    }
    
    return 0;
}