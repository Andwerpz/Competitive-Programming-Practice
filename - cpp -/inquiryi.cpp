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

//Kattis - inquiryi

//note that you can vary k
//just compute pfx sfx sums. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    ll pfx = 0, sfx = 0;
    ll ans = 0;
    for(int i = 0; i < n; i++) sfx += a[i];
    for(int i = 0; i < n; i++){
        pfx += a[i] * a[i];
        sfx -= a[i];
        ans = max(ans, pfx * sfx);
    }
    cout << ans << "\n";
    
    return 0;
}