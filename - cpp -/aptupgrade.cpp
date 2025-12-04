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

// BAPC 2023 - A

//up to k + m packages can be finished downloading, so just greedily pick the largest ones. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    vd a(n);
    ld sum = 0;
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for(int i = 0; i < n; i++) sum += a[i];
    ld fsum = 0;
    for(int i = 0; i < min(n, m + k); i++) fsum += a[i];
    cout << fixed << setprecision(10) << (fsum / sum * 100.0) << "\n";
    
    return 0;
}