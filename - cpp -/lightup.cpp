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

//2024 ICPC NAQ - I

//josh did this one. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n; cin >> n;
    vector<string> m(n);
    for(auto &x : m) cin >> x;

    int ok = 1;

    vector<vector<int>> cnts(n,vector<int>(n));

    for(int i = 0; i < n; i++) {
        int active = 0;
        for(int j = 0; j < n; j++) {
            if(m[i][j] == '?') {
                if(active) {
                    // cout << "notok 1\n";
                    ok = 0;
                }
                if(j) {
                    cnts[i][j-1]++;
                }
                if(j != n - 1) {
                    cnts[i][j+1]++;
                }
                active = 1;
            } else if(m[i][j] != '.') {
                active = 0;
            }
        }
    }

    for(int j = 0; j < n; j++) {
        int active = 0;
        for(int i = 0; i < n; i++) {
            if(m[i][j] == '?') {
                if(active) {
                    // cout << "notok 2\n";
                    ok = 0;
                }
                if(i) {
                    cnts[i-1][j]++;
                }
                if(i != n - 1) {
                    cnts[i+1][j]++;
                }
                active = 1;
            } else if(m[i][j] != '.') {
                active = 0;
            }
        }
    }

    // for(auto x : cnts) {
    //     for(auto y : x) {
    //         cout << y;
    //     }
    //     cout << '\n';
    // }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(m[i][j] != '.' && m[i][j] != '?' && m[i][j] != 'X') {
                if(cnts[i][j] != m[i][j] - '0') {
                    // cout << (int) cnts[i][j] << " comp with : " << (int) (m[i][j] - '0') << '\n';
                    // cout << "m[i][j] : " << m[i][j] << '\n';
                    // cout << "notok 3\n";
                    ok = 0;
                }
            }
        }
    }

    vector<vector<int>> litup(n,vector<int>(n));

    for(int i = 0; i < n; i++) {
        int active = 0;
        for(int j = 0; j < n; j++) {
            if(m[i][j] == '?') {
                active = 1;
            } else if(m[i][j] != '.') {
                active = 0;
            }

            if(active) {
                litup[i][j] = 1;
            }
        }
    }

        for(int i = 0; i < n; i++) {
        int active = 0;
        for(int j = n - 1; j >= 0; j--) {
            if(m[i][j] == '?') {
                active = 1;
            } else if(m[i][j] != '.') {
                active = 0;
            }

            if(active) {
                litup[i][j] = 1;
            }
        }
    }

        for(int j = 0; j < n; j++) {
        int active = 0;
        for(int i = 0; i < n; i++) {
            if(m[i][j] == '?') {
                active = 1;
            } else if(m[i][j] != '.') {
                active = 0;
            }

            if(active) {
                litup[i][j] = 1;
            }
        }
    }

        for(int j = 0; j < n; j++) {
        int active = 0;
        for(int i = n - 1; i >= 0; i--) {
            if(m[i][j] == '?') {
                active = 1;
            } else if(m[i][j] != '.') {
                active = 0;
            }

            if(active) {
                litup[i][j] = 1;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(m[i][j] == '.') {
                if(litup[i][j] == 0) {
                    ok = 0;
                }
            }
        }
    }

    cout << ok << '\n';
    
    return 0;
}