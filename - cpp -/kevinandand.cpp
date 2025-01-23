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

//Codeforces - 2061E

//let's consider each element a[i] seperately. Given some amount of operations from 1 to m, what's the minimum we
//can make a[i]? Since m is really small, we can test all 2^m combinations. 

//denote mn[j] as the minimum we can make a[i] in exactly j moves. What you notice is that the decrease between 
//mn[j] to mn[j + 1] is always greater than mn[j + 1] to mn[j + 2]. This is because if you could decrease that much 
//on the second operation, then you might as well do it on the first one. 

//This leads to a greedy solution. Sort all the decreases in descending order and pick the k greatest ones. Since 
//the decreases within a specific a[i] are already sorted in descending order, this is always a valid order. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        vi a(n), b(m);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < m; i++) cin >> b[i];
        ll ans = 0;
        for(int i = 0; i < n; i++) ans += a[i];
        vi dec(n * m);
        vi bits((1 << m), (1 << 30) - 1), bcnt((1 << m), -1);
        for(int i = 0; i < (1 << m); i++){
            bcnt[i] = __builtin_popcount(i);
            for(int j = 0; j < m; j++) if(i & (1 << j)) bits[i] &= b[j];
        }
        for(int i = 0; i < n; i++){
            vi mn_val(m + 1, a[i]);
            for(int j = 0; j < (1 << m); j++) mn_val[bcnt[j]] = min(mn_val[bcnt[j]], a[i] & bits[j]);
            for(int j = 0; j < m; j++) dec[i * m + j] = mn_val[j] - mn_val[j + 1];
        }
        sort(dec.begin(), dec.end());
        reverse(dec.begin(), dec.end());
        for(int i = 0; i < k; i++) ans -= dec[i];
        cout << ans << "\n";
    }
    
    return 0;
}