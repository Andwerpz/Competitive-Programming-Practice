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

//CTU Open 2021 - G

//treat this like a coin change problem, where all the denominations are factors of each other. 
//this means we can just greedily select the coins from largest to smallest. 

vl fac;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll y;
    cin >> y;
    if(y == 1){
        cout << "0\n";
        return 0;
    }
    fac = vl(10);
    fac[0] = 1;
    for(int i = 1; i < 10; i++){
        fac[i] = fac[i - 1] * i;
    }
    string ans = "";
    for(int i = 9; i >= 1; i--){
        while(y >= fac[i]) {
            y -= fac[i];
            ans.push_back('0' + i);
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
    
    return 0;
}