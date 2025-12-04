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

//Kattis - neighborhoodwatch

//consider all walks starting from their left point, they need to walk right until they reach a safe house. It's
//sufficient to just keep track of the last safe house you've seen to the right. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vi a(n, 0);
    for(int i = 0; i < k; i++){
        int h;
        cin >> h;
        h --;
        a[h] = 1;
    }
    ll ans = 0, prev = n;
    for(int i = n - 1; i >= 0; i--){
        if(a[i]) prev = i;
        ans += n - prev;
    }
    cout << ans << "\n";
    
    return 0;
}