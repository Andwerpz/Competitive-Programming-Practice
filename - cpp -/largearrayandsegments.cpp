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

//Codeforces - 2086B

//we just want to see what's the largest index i such that the sum in range [i, n) is still greater than or
//equal to x. You could binary search, or you could compute it directly, just compute the number of repetitions
//you need, and then walk the index back. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, k, x;
        cin >> n >> k >> x;
        vl a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        ll sum = 0;
        for(int i = 0; i < n; i++) sum += a[i];
        if(sum * k < x) {
            cout << "0\n";
            continue;
        }
        ll rep = (x + sum - 1) / sum;
        // cout << "REP : " << rep << endl;
        ll ans = n * (k - rep) + 1;
        ll cx = rep * sum;
        for(int i = 0; i < n; i++){
            cx -= a[i];
            if(cx < x) break;
            ans ++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}