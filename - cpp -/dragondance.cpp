#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//UTPC Contest 1-29-25 Div.1 - C

//just find the maximum subarray with no difference greater than k

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    int ans = 1;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    int cur = 1;
    for(int i = 1; i < n; i++){
        if(abs(a[i] - a[i - 1]) > k) cur = 0;
        cur ++;
        ans = max(ans, cur);
    }
    cout << ans << "\n";
    
    return 0;
}