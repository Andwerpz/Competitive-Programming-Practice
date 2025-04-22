#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vl> d0(n, vl(n, 1e18)), d1(n, vl(n, 1e18)), d2(n, vl(n, 1e18));
    for(int i = 0; i < n; i++) d0[i][i] = 0, d1[i][i] = 0, d2[i][i] = 0;
    for(int i = 0; i < m; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a --, b --;
        if(d >= 0) {
            d0[a][b] = min(d0[a][b], (ll) c);
        }
        if(d >= 1) {
            d1[a][b] = min(d1[a][b], (ll) c);
        }
        if(d >= 2) {
            d2[a][b] = min(d2[a][b], (ll) c);
        }
    }
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         if(d2[i][j] == 1e18) cout << -1;
    //         else cout << d2[i][j];
    //         cout << " ";
    //     }
    //     cout << "\n";
    // }

    //0 and 1 suitcase, do floyd warshall normally
    for(int k = 0; k < n; k++) for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        if(d0[i][k] + d0[k][j] < d0[i][j]) d0[i][j] = d0[i][k] + d0[k][j];
        if(d1[i][k] + d1[k][j] < d1[i][j]) d1[i][j] = d1[i][k] + d1[k][j];
    }
    //2 suitcases, have to also account for bringing 1 suitcase 2 times. 
    for(int k = 0; k < n; k++) for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        if(d2[i][k] + d2[k][j] < d2[i][j]) d2[i][j] = d2[i][k] + d2[k][j];
        d2[i][j] = min(d2[i][j], d1[i][j] * 2 + d0[j][i]);
    }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++) {
    //         cout << (d0[i][j] == 1e18? -1 : d0[i][j]) << " ";
    //     }
    //     cout << "\n";
    // }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++) {
    //         cout << (d1[i][j] == 1e18? -1 : d1[i][j]) << " ";
    //     }
    //     cout << "\n";
    // }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(d2[i][j] == 1e18) cout << -1;
            else cout << d2[i][j];
            cout << " ";
        }
        cout << "\n";
    }

    return 0;
}