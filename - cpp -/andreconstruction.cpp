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

//Codeforces - 1991B

//just set a[i] to be b[i] | b[i + 1]. This is the minimum amount of bits needed to satisfy b
//constraints on both sides of a[i]. Finally, check through the a array to see if it's actually good.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi b(n - 1);
        for(int i = 0; i < n - 1; i++){
            cin >> b[i];
        }
        vi a(n, 0);
        for(int i = 0; i < n - 1; i++){
            a[i] = a[i] | b[i];
            a[i + 1] = a[i + 1] | b[i];
        }
        bool is_valid = true;
        for(int i = 0; i < n - 1; i++){
            if(b[i] != (a[i] & a[i + 1])) {
                is_valid = false;
            }
        }
        if(!is_valid){
            cout << "-1\n";
            continue;
        }
        for(int i = 0; i < n; i++){
            cout << a[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}