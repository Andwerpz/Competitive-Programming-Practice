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

//ECNA 2023 - D

//reading comprehension problem lmao

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll avg = 0;
    for(int i = 0; i < 5; i++) {
        ll a, l;
        cin >> a >> l;
        avg += a * l;
    }
    avg /= 5;
    ll n, k;
    cin >> n >> k;
    ll ans = (avg * n) / k;
    cout << ans << "\n";
    
    return 0;
}