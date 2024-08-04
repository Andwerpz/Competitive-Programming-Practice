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

//Codeforces - 1669C

//just need to make sure all values of a group are all even or all odd. 

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
        }
        bool odd = true, even = true;
        for(int i = 0; i < n; i += 2){
            odd = odd && (a[i] % 2 == 1);
            even = even && (a[i] % 2 == 0);
        }
        if(!odd && !even) {
            cout << "NO\n";
            continue;
        }
        odd = true, even = true;
        for(int i = 1; i < n; i += 2){
            odd = odd && (a[i] % 2 == 1);
            even = even && (a[i] % 2 == 0);
        }
        if(!odd && !even) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
    
    return 0;
}