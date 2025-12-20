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

//CSES - 1640

//sorting + 2ptr faster than hash map slightly

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, x;
    cin >> n >> x;
    map<int, int> m;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if(m.count(x - a)) {
            cout << (i + 1) << " " << (m[x - a] + 1) << "\n";
            return 0;
        }
        m[a] = i;
    }
    cout << "IMPOSSIBLE\n";
    
    // int n, x;
    // cin >> n >> x;
    // vector<pii> a(n);
    // for(int i = 0; i < n; i++) {
    //     cin >> a[i].first;
    //     a[i].second = i;
    // }
    // sort(a.begin(), a.end());
    // int r = n - 1;
    // for(int i = 0; i < n; i++) {
    //     while(r != 0 && a[r].first + a[i].first > x) r --;
    //     if(r <= i) break;
    //     if(a[r].first + a[i].first == x) {
    //         cout << (a[r].second + 1) << " " << (a[i].second + 1) << "\n";
    //         return 0;
    //     }
    // }
    // cout << "IMPOSSIBLE\n";
    
    return 0;
}