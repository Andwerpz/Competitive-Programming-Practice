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

//UIUC IPL Team Tryout 2025 - A

//just take the two smallest and two largest as parallel sides. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    vi a(4);
    for(int i = 0; i < 4; i++) cin >> a[i];
    sort(a.begin(), a.end());
    int w = min(a[0], a[1]);
    int h = min(a[2], a[3]);
    cout << (w * h) << "\n";
    
    return 0;
}