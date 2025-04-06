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

//Codeforces - 1811A

//greedily insert. Look from the front, and if inserting the digit there will increase the number, should
//do it as soon as possible. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, d;
        cin >> n >> d;
        string s;
        cin >> s;
        vi a(n);
        for(int i = 0; i < n; i++) a[i] = s[i] - '0';
        vi sfx(n + 1, 0);
        for(int i = n - 1; i >= 0; i--) sfx[i] = max(sfx[i + 1], a[i]);
        bool pl = false;
        for(int i = 0; i < n; i++){
            if(!pl && d > a[i]) {
                cout << d;
                pl = true;
            }
            cout << a[i];
        }
        if(!pl) cout << d;
        cout << "\n";
    }
    
    return 0;
}