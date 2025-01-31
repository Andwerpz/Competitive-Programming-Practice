#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Codeforces - 1157G

//if we can sort the matrix, then we can get from the sorted matrix to the original matrix as well. 
//is there any unique state that we can easily convert any matrix into to check if the two are mutually
//reachable from eachother?

//turns out there is. First, we can toggle the rows such that the first element in each row is '0'. 
//Next, toggle the columns to minimize the amount of '1's in each column. If there is a tie, toggle the 
//column such that the first element in the column is '0'.

//This procedure essentially reduces the degrees of freedom of such an arrangement to 0, therefore from any
//starting matrix, this result is guaranteed to be unique. 

//Finally, how do we check from the result whether or not a sorted matrix is reachable. Well, the procedure was 
//specifically chosen to make this easy. At the end of the procedure if a sorted matrix is reachable, then there
//can be at most 1 row with '1' elements, and the '1' elements must be a contiguous suffix of the row. Then to 
//transform it into the sorted matrix, we just have to toggle all rows below the row with the '1' elements. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi g(n, vi(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) cin >> g[i][j];
    }
    vi ansr(n, 0), ansc(m, 0);
    //make it so that the first element in every row is off
    for(int i = 0; i < n; i++){
        if(g[i][0]) {
            for(int j = 0; j < m; j++) g[i][j] ^= 1;
            ansr[i] ^= 1;
        }
    }
    //make it so that the maximum number of elements in each column are off
    //tiebreak by turning the first element in the column off
    for(int i = 0; i < m; i++){
        int ocnt = 0;
        for(int j = 0; j < n; j++) ocnt += g[j][i];
        if(n - ocnt < ocnt || (n - ocnt == ocnt && g[0][i])) {
            for(int j = 0; j < n; j++) g[j][i] ^= 1;
            ansc[i] ^= 1;
        }
    }
    //if there are any 1s, they should be isolated to one row, and compose the suffix of it
    //otherwise, it's impossible
    bool is_valid = true;
    int row = -1;
    for(int i = 0; i < n; i++){
        bool found_one = false;
        for(int j = 0; j < m; j++){
            if(found_one) {
                if(g[i][j] == 0) is_valid = false;
            }
            else {
                if(g[i][j] == 1) found_one = true;
            }
        }
        if(found_one) {
            if(row != -1) is_valid = false;
            else row = i;
        }
    }
    if(!is_valid) {
        cout << "NO\n";
        return 0;
    }
    for(int i = row + 1; i < n; i++){
        ansr[i] ^= 1;
    }
    cout << "YES\n";
    for(int i = 0; i < n; i++) cout << ansr[i];
    cout << "\n";
    for(int i = 0; i < m; i++) cout << ansc[i];
    cout << "\n";
    
    return 0;
}