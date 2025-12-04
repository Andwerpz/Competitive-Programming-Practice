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

//Codeforces - 2122A

//wlog, n <= m. 
//if you only have one row, you don't make any decisions
//if you have two rows, then if you have 3 columns, you can do something like this:

//0 1 1000
//2 0 0

//if the grid is any bigger, you can just place this in the top left corner. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        if(max(n, m) >= 3 && min(n, m) >= 2) {
            cout << "YES\n";
        }
        else cout << "NO\n";
    }
    
    return 0;
}