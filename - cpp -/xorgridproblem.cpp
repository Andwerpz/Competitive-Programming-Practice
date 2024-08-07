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

//Codeforces - 1993E

//let's consider only row operations for now. If we choose some row i to do the operation on, 
//then we effectively replace it with the XOR sum of all the rows. But notice that the new XOR sum of all
//the rows is actually equal to the row we removed. Since doing an operation on a row effectively 
//swaps the XOR sum and the row we chose, it's as if we have some auxillary row that is initially the
//XOR sum of all rows that we're swapping out with every time we do an operation. 

//Similar argument for operations on columns. Therefore, we can expand the matrix by 1 row and 1 column, and this
//extra row and col will be our 'auxillary' row and column described above. They should be initialized to the
//XOR sum of their respective row or column. Now, all an operation does is swap an arbitrary row or column with
//the corresponding auxillary row or column. This means that we can arbitrarily permute the rows and columns. 
//note that the beauty of our new array is just the beauty of the array after we remove the auxillary row and col. 

//the final observation is that we can consider permuting the rows and columns seperately. Since we have to lose 
//exactly 1 row and column, we need to compute for both rows and columns, the minimum difference sum given that 
//we've removed row i and column j, for all pairs (i, j). 

//We can do this in n^3 * 2^n using dp. I'll consider permuting the rows here, but the columns are very similar. 
//dp[i][bits][j] = min difference sum given that
//i = which column is removed
//bits = bitset of rows already placed
//j = last row placed

//we shouldn't place all rows, that way we can consider removing any row given some column i being removed. 

//solve the problem given that column miss is missing. 
void solve_miss(vvi& a, int miss, vvi& res) {
    int n = a.size();
    int m = a[0].size();
    //precompute differences between rows
    vvi diff(n, vi(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < m; k++){
                if(k == miss){
                    continue;
                }
                diff[i][j] += abs(a[i][k] - a[j][k]);
            }
        }
    }
    //do dp
    vvi dp((1 << n), vi(n, 2e9));
    for(int i = 1; i < dp.size() - 1; i++){
        int oncnt = 0;
        int pon = -1;
        for(int j = 0; j < n; j++){
            if((i >> j) & 1) {
                oncnt ++;
                pon = j;
            }
        }
        if(oncnt == 1){
            dp[i][pon] = 0;
        }
        if(oncnt == n - 1) {
            //figure out which row is missing
            int missing = -1;
            for(int j = 0; j < n; j++){
                if(!((i >> j) & 1)){
                    missing = j;
                    break;
                }
            }
            for(int j = 0; j < n; j++){
                if((i >> j) & 1) {
                    res[missing][miss] = min(res[missing][miss], dp[i][j]);
                }
            }
            continue;
        }
        for(int j = 0; j < n; j++){
            if(!((i >> j) & 1)){
                continue;   //doesn't have
            }
            for(int k = 0; k < n; k++){
                if((i >> k) & 1) {
                    continue;   //already has
                }
                //prev row was j, we're adding on row k
                int nbits = i + (1 << k);
                dp[nbits][k] = min(dp[nbits][k], dp[i][j] + diff[j][k]);
            }
        }
    }
}

//solve for minimum difference between rows
vvi solve(vvi a){
    int n = a.size();
    int m = a[0].size();
    vvi res(n, vi(m, 2e9));
    for(int i = 0; i < m; i++){
        solve_miss(a, i, res);
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vvi a(n + 1, vi(m + 1, 0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> a[i][j];
                a[i][m] ^= a[i][j];
                a[n][j] ^= a[i][j];
                a[n][m] ^= a[i][j];
            }
        }
        n ++;
        m ++;
        //transpose
        vvi at(m, vi(n));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                at[j][i] = a[i][j];
            }
        }
        vvi lut1 = solve(a), lut2 = solve(at);
        int ans = 1e9;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                ans = min(ans, lut1[i][j] + lut2[j][i]);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}