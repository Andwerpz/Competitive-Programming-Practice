#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1938B

//define the elementary operation as selecting some subrectangle of width and height 2, and adding 1 to the tl and br 
//corners, and 2 to the tr and bl corners. Note that by performing the elementary operation on the same location twice,
//you'll get the other orientation:

//0 0   1 2   2 1   0 0
//0 0   2 1   1 2   0 0

//this also tells us that performing the elementary operation on the same location 3 times is identical to not 
//performing it at all. 

//next, observe that any operation with width or height greater than 2 can be broken down into multiple applications of
//the elementary operation. For example:

//0 0    1 2    1 2
//0 0 -> 2 1 -> 0 0
//0 0    0 0    2 1

//this tells us that if there is a solution, it is sufficient to select each location that we can perform an elementary
//operation, and perform it 0, 1, or 2 times. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m)), b(n, vector<int>(m));
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            for(int j = 0; j < m; j++){
                a[i][j] = s[j] - '0';
            }
        }
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            for(int j = 0; j < m; j++){
                b[i][j] = s[j] - '0';
            }
        }
        for(int i = 0; i < n - 1; i++){
            for(int j = 0; j < m - 1; j++){
                while(a[i][j] != b[i][j]) {
                    a[i][j] = (a[i][j] + 1) % 3;
                    a[i + 1][j + 1] = (a[i + 1][j + 1] + 1) % 3;
                    a[i + 1][j] = (a[i + 1][j] + 2) % 3;
                    a[i][j + 1] = (a[i][j + 1] + 2) % 3;
                }
            }
        }
        bool is_valid = true;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(a[i][j] != b[i][j]) {
                    is_valid = false;
                }
            }
        }
        cout << (is_valid? "YES" : "NO") << "\n";
    }
    
    return 0;
}