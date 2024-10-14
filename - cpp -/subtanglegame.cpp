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

//Codeforces - 2005 E1

//can pretty much simulate it using dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int l, n, m;
        cin >> l >> n >> m;
        vi a(l);
        for(int i = 0; i < l; i++){
            cin >> a[i];
        }
        vvi g(n, vi(m));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> g[i][j];
            }
        }
        for(int i = 0; i < n; i++){
            reverse(g[i].begin(), g[i].end());
        }
        reverse(g.begin(), g.end());
        vvi p_win(n + 1, vi(m + 1, 0));
        for(int i = l - 1; i >= 0; i--){
            vvi np_win(n + 1, vi(m + 1, 0));
            for(int j = 0; j < n; j++){
                for(int k = 0; k < m; k++){
                    if(g[j][k] == a[i] && p_win[j][k] == 0){
                        np_win[j + 1][k + 1] = 1;
                    }
                }
            }
            for(int j = 1; j <= n; j++){
                for(int k = 1; k <= m; k++){
                    np_win[j][k] += np_win[j - 1][k] + np_win[j][k - 1] - np_win[j - 1][k - 1];
                }
            }
            p_win = np_win;
        }
        cout << (p_win[n][m] == 0? "N" : "T") << "\n";
    }
    
    return 0;
}