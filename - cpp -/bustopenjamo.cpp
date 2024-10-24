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

//Codeforces - 2022A

//first, pair off people from the same family. Then, we want to assign stragglers to as many of their
//own rows as possible, can just use a loop. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, r;
        cin >> n >> r;
        vi a(n);
        int ans = 0;
        int rem = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            r -= a[i] / 2;
            ans += (a[i] / 2) * 2;
            a[i] %= 2;
            rem += a[i];
        }
        while(rem > 0 && rem / 2 <= r - 1) {
            ans ++;
            rem --;
            r --;
        }
        cout << ans << "\n";
    }
    
    return 0;
}