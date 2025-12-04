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

// BAPC 2023 - B

//it's optimal to greedily pick the move that reduces the size of the opponent as much as possible. 
//we just have to steer clear of floats, we can simulate it entirely using integers. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n;
    cin >> n;
    int ans = 0;
    bool isp2 = true;
    while(n != 1) {
        if(n % 2) isp2 = false;
        n /= 2;
        ans ++;
    }
    ans += !isp2;
    ans ++;
    cout << ans << "\n";
    
    return 0;
}