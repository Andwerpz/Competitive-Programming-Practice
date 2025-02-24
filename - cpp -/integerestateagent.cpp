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

//2014 NAIPC - G

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n; cin >> n;

    while (n) {

        // if (n == 1) {
        //     cout << 1 << "\n";
        //     cin >> n;
        //     continue;
        // }

        set<pair<double, double>> s;

        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                int j = n / i;
                // try (i, j)
                if (i % 2 == 1) {
                    // odd # of terms -> good
                    if (i < 2 * (j-1)) {
                        // cout << "I : " << i << " J : " << j << endl;
                        s.insert({i, j});
                    }
                }

                // // try (j, i)
                if (j % 2 == 1) {
                    // odd # of terms -> good
                    if (j < 2 * (i-1)) {
                        // cout << "I : " << i << " J : " << j << endl;
                        s.insert({j, i});
                    }
                }
            }
        }

        for (int i = 1; i * i <= 2*n; ++i) {
            if ((2*n) % i == 0) {
                int j = (2*n) / i;

                // (i, j)
                if ((i % 2 == 0) && (j % 2 == 1)) {
                    int x = j / 2;
                    if (i <= 2 * (x-1)) {
                        s.insert({i, x + 0.5});
                        // cerr << "i : " << i << " j : " << j << endl;
                    }
                }

                // // (j, i)
                if ((j % 2 == 0) && (i % 2 == 1)) {
                    int x = i / 2;
                    if (j <= 2 * (x-1)) {
                        s.insert({j, x + 0.5});
                        // cerr << "i : " << i << " j : " << j << endl;
                    }
                }
            }
        }

        cout << s.size() << "\n";

        cin >> n;
    }
    
    return 0;
}