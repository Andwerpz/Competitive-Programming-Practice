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

//Codeforces - 440C

//brute force recursion with pruning.

//observe that placing more than 11 of the same type of number is never optimal. 

const int D = 16;
vl val(D, 0), mxadd(D + 1, 0);
int ans = 1e9;
void solve(ll sum, ll tgt, int ind, int cans) {
    if(cans >= ans) return;
    if(tgt < sum - mxadd[ind] || sum + mxadd[ind] < tgt) return;
    if(ind == D) {
        ans = min(ans, cans);
        return;
    }
    int ans = 1e9;
    for(ll i = -11; i <= 11; i++){
        solve(sum + i * val[ind], tgt, ind + 1, cans + (D - ind) * (int) abs(i));
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n;
    cin >> n;
    val[0] = 1;
    ll pow10 = 1;
    for(int i = 1; i < D; i++){
        pow10 *= 10;
        val[i] = val[i - 1] + pow10;
    }
    reverse(val.begin(), val.end());
    mxadd[D - 1] = val[D - 1] * 11;
    for(int i = D - 1; i >= 0; i--){
        mxadd[i] = mxadd[i + 1] + (ll) 11 * val[i];
    }
    solve(0, n, 0, 0);
    cout << ans << "\n";
    
    return 0;
}