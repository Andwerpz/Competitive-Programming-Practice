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

//AtCoder - ARC79D

//if there wasn't a limit on a_i, then we could just solve it with N = 2. However, a_i <= 10^16 + 1000,
//so we probably have to solve it with N = 50. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll k;
    cin >> k;
    ll tmp = ((k + 49) / 50) * 50;
    ll mult = tmp / 50;
    vl a(50);
    for(int i = 0; i < 50; i++){
        a[i] = mult + i;
    }
    while(tmp != k) {
        ll ind = 0;
        for(int i = 1; i < 50; i++){
            if(a[i] > a[ind]) ind = i;
        }
        a[ind] -= 50;
        for(int i = 0; i < 50; i++){
            if(i == ind) continue;
            a[i] ++;
        }
        tmp --; 
    }
    cout << a.size() << "\n";
    for(ll x : a) cout << x << " ";
    cout << "\n";
    
    return 0;
}