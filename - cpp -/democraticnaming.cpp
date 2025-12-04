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

// BAPC 2023 - D

//implementation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi f(m, vi(26, 0));
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < m; j++) f[j][s[j] - 'a'] ++;
    }
    for(int i = 0; i < m; i++) {
        char ans = '.';
        int mx = -1;
        for(int j = 0; j < 26; j++) {
            if(f[i][j] > mx) {
                mx = f[i][j];
                ans = 'a' + j;
            }
        }
        cout << ans;
    }
    cout << "\n";
    
    return 0;
}