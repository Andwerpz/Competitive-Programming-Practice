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

//Codeforces - 1997B

//if a cell is open, and has three adjacent open cells, and two diagonally adjacent closed cells, then filling this cell
//will split it into 3 regions. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<string> g(2);
        cin >> g[0] >> g[1];
        int ans = 0;
        for(int i = 1; i < n - 1; i++){
            for(int j = 0; j < 2; j++){
                if(g[j][i] == '.' && g[j][i + 1] == '.' && g[j][i - 1] == '.' && g[j ^ 1][i] == '.' && g[j ^ 1][i - 1] == 'x' && g[j ^ 1][i + 1] == 'x') {
                    ans ++;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}