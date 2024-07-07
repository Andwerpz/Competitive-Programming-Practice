#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1369C

//Order the friends in decreasing values of w[i]. Then, iterate through them and give each the maximum value, and w[i] - 1
//of the minimum values. 

//If w[i] = 1, then always put it at the front, since giving it one maximum value will double count it. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        vector<int> w(k);
        for(int i = 0; i < k; i++){
            cin >> w[i];
        }
        sort(w.begin(), w.end());
        for(int i = 0; i < k; i++){
            if(w[i] != 1){
                reverse(w.begin() + i, w.end());
                break;
            }
        }
        int ptr = 0;
        ll ans = 0;
        for(int i = 0; i < k; i++){
            // cout << "W : " << w[i] << "\n";
            if(w[i] == 1){
                ans += a[n - 1 - i] * 2;
            }
            else {
                ans += a[ptr] + a[n - 1 - i];
            }
            ptr += w[i] - 1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}