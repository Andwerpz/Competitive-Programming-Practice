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

//Codeforces - 2096B

//we can construct the worst case. 

//first, for each color of glove, we'll take all of the maximum out of L or R gloves. 

//then, for the first k - 1 gloves with the maximum remaining, we'll take all of them, and then we'll
//take 1 more for the kth pair. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<pll> a(n);
        for(int i = 0; i < n; i++) cin >> a[i].first;
        for(int i = 0; i < n; i++) cin >> a[i].second;
        for(int i = 0; i < n; i++) if(a[i].second > a[i].first) swap(a[i].first, a[i].second);
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        ll ans = 0;
        for(int i = 0; i < n; i++) ans += a[i].first;
        sort(a.begin(), a.end(), [](pll a, pll b) -> bool {
            return a.second > b.second;
        });
        for(int i = 0; i < k - 1; i++) ans += a[i].second;
        ans += 1;
        cout << ans << "\n";
    }
    
    return 0;
}