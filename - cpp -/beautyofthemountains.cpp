#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1982D

//denote a as the sum of type '0' mountains, and b as the sum of type '1' mountains. Our goal is to make a = b.

//In one operation, we can add some constant c to any k by k submatrix of the grid. Notice that the choice of c
//actually does not matter, as if we wanted to do c = 10 for example, then we could just do the operation with
//c = 1, 10 times. So for now on, i'll just set c = 1 or -1 for all operations. (-1 because we can't just
//do the operation negative times)

//What actually does matter is the difference between the number of '0' and '1' mountains in some k by k submatrix.
//For example, if there are 3 '0' mountains, and 1 '1' mountain, then applying the operation will raise a by 3,
//and raise b by 1, which equivalently increases or decreases the difference (depending on the initial values
//of a and b) by 2

//Since we want to make the difference equal to 0, the difference needs to be able to be expressed as a linear
//combination of all the differences of the possible operations that we can do. To check if some value d can
//be expressed as a linear combination of x and y, it's only possible if d is a multiple of gcd(x, y). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        vector<vector<ll>> a(n, vector<ll>(m));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> a[i][j];
            }
        }
        ll diff = 0;
        vector<vector<int>> pfx(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; i++){
            string s;
            cin >> s;
            for(int j = 1; j <= m; j++){
                pfx[i][j] = s[j - 1] - '0';
                if(pfx[i][j] == 0){
                    pfx[i][j] = -1;
                }
                pfx[i][j] += -pfx[i - 1][j - 1] + pfx[i - 1][j] + pfx[i][j - 1];
                if(s[j - 1] == '0') {
                    diff -= a[i - 1][j - 1];
                }
                else {
                    diff += a[i - 1][j - 1];
                }
            }
        }
        // for(int i = 0; i <= n; i++){
        //     for(int j = 0; j <= m; j++){
        //         cout << pfx[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        diff = abs(diff);
        ll g = 0;
        for(int i = 0; i <= n - k; i++){
            for(int j = 0; j <= m - k; j++){
                ll sum = pfx[i + k][j + k] - pfx[i + k][j] - pfx[i][j + k] + pfx[i][j];
                sum = abs(sum);
                // cout << "SUM : " << sum << "\n";
                g = gcd(g, sum);
            }
        }
        // cout << "G : " << g << "\n";
        // cout << "DIFF : " << diff << "\n";
        if(g == 0){
            cout << (diff == 0? "YES" : "NO") << "\n";
            continue;
        }
        if(diff % g == 0){
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
    
    return 0;
}