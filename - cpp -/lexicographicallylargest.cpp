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
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] = a[i] + i + 1;
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        for(int i = 1; i < n; i++){
            a[i] = min(a[i - 1] - 1, a[i]);
        }
        for(int i = 0; i < n; i++){
            cout << a[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}