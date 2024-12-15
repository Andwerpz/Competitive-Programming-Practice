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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n, 0), f(n, 0);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        a[u] ++, a[v] ++;
    }
    for(int x : a) f[x] ++;
    vi m(n * 2 + 1, 1e9), M(n * 2 + 1, -1e9);
    m[0] = 0, M[0] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= f[i]; f[i] -= j, j *= 2){
            for(int k = m.size() - 1; k >= i * j; k--){
                m[k] = min(m[k], m[k - i * j] + j);
                M[k] = max(M[k], M[k - i * j] + j);
            }
        }
        if(f[i]) {
            for(int k = m.size() - 1; k >= i * f[i]; k--){
                m[k] = min(m[k], m[k - i * f[i]] + f[i]);
                M[k] = max(M[k], M[k - i * f[i]] + f[i]);
            }
        }
        for(int j = 0; j < m.size(); j++){
            cout << m[j] << " ";
        }
        cout << "\n";
        for(int j = 0; j < m.size(); j++){
            cout << M[j] << " ";
        }
        cout << "\n";
    }
    ll ans = 0;
    for(int i = 0; i < m.size(); i++) {
        if(M[i] < 0) continue;
        cout << "m M : " << m[i] << " " << M[i] << " " << i << "\n";
        ans += M[i] - m[i] + 1;
    }
    cout << ans << "\n";
    
    return 0;
}