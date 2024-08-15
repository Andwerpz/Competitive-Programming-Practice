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

//Codeforces - 1835A

//first, iterate through all possible values of A. For each value of A, find how many values of B there are.
//if the kth smallest equality is given with the current value of A, just find it, otherwise subtract the amount
//of B values from k, and move to the next A value. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        ll a, b, c, k;
        cin >> a >> b >> c >> k;
        a --;
        b --;
        c --;
        k --;
        ll ans_a = -1, ans_b = -1;
        ll a_start = 1;
        for(int i = 0; i < a; i++){
            a_start *= 10;
        }
        ll b_start = 1;
        for(int i = 0; i < b; i++){
            b_start *= 10;
        }
        ll c_start = 1;
        for(int i = 0; i < c; i++){
            c_start *= 10;
        }
        for(int i = a_start; i < a_start * 10; i++){
            ll cb_start = c_start - i;
            ll cb_end = (c_start * 10) - i;
            cb_start = max(cb_start, b_start);
            cb_end = min(cb_end, b_start * 10);
            ll diff = max(0ll, cb_end - cb_start);
            if(diff > k){
                ans_a = i;
                ans_b = cb_start + k;
                break;
            }
            k -= diff;
        }
        if(ans_a == -1){
            cout << "-1\n";
            continue;
        }
        cout << ans_a << " + " << ans_b << " = " << ans_a + ans_b << "\n";
    }
    
    return 0;
}