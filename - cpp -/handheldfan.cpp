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

//Alberta Collegiate Programming Contest 2024, Open Division - M

//two pointers. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, w;
    cin >> n >> w;
    w *= 60;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] *= 2;
    }
    int ans = 0;
    int r = 0;
    int sum = 0;
    for(int i = 0; i < n; i++){
        while(r != n && sum + a[r] <= w){
            sum += a[r];
            r ++;
        }
        ans = max(ans, r - i);
        sum -= a[i];
    }
    cout << ans << "\n";
    
    return 0;
}