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

//2014 NAIPC - E

//brute force. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n; cin >> n;
    // while (n) {

        vector<int> a(n);
        for (auto& x : a)
            cin >> x;
        
        int cnt = 0;

        for (int i = 1; i <= 100; ++i) {
            
            int g = -1;
            for (int j = 0; j < n; ++j) {
                if (a[j] % i == 0) {
                    if (g == -1) {
                        g = a[j];
                    } else {
                        g = gcd(g, a[j]);
                    }
                } else {
                    g = -1;
                }
                if (g == i) {
                    cnt++;
                    break;
                }
            }
            
        }

        cout << cnt << "\n";

    //     cin >> n;
    // }
    
    return 0;
}