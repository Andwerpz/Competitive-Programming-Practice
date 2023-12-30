#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1917E

//if k % 2 == 1, then it's impossible to make.
//if k % 4 == 0, then it's always possible; just use square blocks of 4 1s to tile the matrix. 
//otherwise, k % 4 == 2. We need to do some casework. 

//first, we can see that if n^2 - k < k, we can just set k := n^2 - k, and instead of placing 1s on a grid
//of 0s, we are placing 0s on a grid of 1s. We can place 1s like normal, and invert our answer at the end. 
//so now, k <= n^2 / 2. 

//if k >= 2 * n - 2, then we can fill up the sides like so:
//0 0 0 1   and 4 tile the remaining 1s. Note that for all n >= 4, this will work, and if n == 2, then 
//0 0 0 1   we have other cases covering them. 
//0 0 0 1
//1 1 1 0

//else if k >= n, then we will place 1s along the diagonal of the matrix. But we may have some extra 1s, so we'll
//make a curvy diagonal to compensate. 
// 0 0 0 0 0 1
// 0 0 0 0 0 1
// 0 0 0 0 0 1  Note that the most extreme form of this 'curvy diagonal' is just the case mentioned above. 
// 0 0 0 0 1 0
// 0 0 0 1 0 0
// 1 1 1 0 0 0

//else if k >= 6, then, we can use a pattern of 6 1s that has a row and column xor of 0, then 4 tile the rest:
// 1 0 1 0 0 0
// 0 1 1 0 0 0
// 1 1 0 0 0 0
// 0 0 0 0 0 0
// 1 1 1 1 0 0
// 1 1 1 1 0 0
//this is the only really tricky case, as it's unintuitive that you can have less than n 1s but still make the row
//and col xor all equal. 

//otherwise, it's impossible. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<vector<int>> mat(n, vector<int>(n, 0));
        if(k % 2 == 1){
            //can never make? 
            cout << "No\n";
            continue;
        }
        if(k % 4 == 0){
            //can always make
            for(int i = 0; i < n / 2 && k != 0; i++){
                for(int j = 0; j < n / 2 && k != 0; j++){
                    mat[i * 2 + 0][j * 2 + 0] = 1;
                    mat[i * 2 + 0][j * 2 + 1] = 1;
                    mat[i * 2 + 1][j * 2 + 0] = 1;
                    mat[i * 2 + 1][j * 2 + 1] = 1;
                    k -= 4;
                }
            }
        }
        else {
            //k % 4 == 2
            //can sometimes make?
            bool inv = false;
            if(k > n * n - k) {
                inv = true;
                k = n * n - k;
            }
            if(k == 2 && n != 2) {
                //can never make
                cout << "No\n";
                continue;
            }
            //can always make
            if(k < n){
                //put 6 pattern, and 4 tile the rest
                mat[0][0] = 1;
                mat[0][1] = 1;
                mat[1][1] = 1;
                mat[1][2] = 1;
                mat[2][2] = 1;
                mat[2][0] = 1;
                k -= 6;
                for(int i = 0; i < n / 2 && k != 0; i++){
                    for(int j = 0; j < n / 2 && k != 0; j++){
                        if(i < 2 && j < 2){
                            continue;
                        }
                        mat[i * 2 + 0][j * 2 + 0] = 1;
                        mat[i * 2 + 0][j * 2 + 1] = 1;
                        mat[i * 2 + 1][j * 2 + 0] = 1;
                        mat[i * 2 + 1][j * 2 + 1] = 1;
                        k -= 4;
                    }
                }
            }
            else if(k <= 2 * n - 2) {
                //weird diag
                int s = k - n;
                for(int i = 0; i < s; i++){
                    mat[n - 1][i] = 1;
                    mat[i][n - 1] = 1;
                }
                int d = n - s;
                int r = n - 1;
                int c = s;
                for(int i = 0; i < d; i++){
                    mat[r--][c++] = 1;
                }
            }
            else {
                //fill part two sides, and 4 block the rest
                k -= 2 * n - 2;
                for(int i = 0; i < n - 1; i++){
                    mat[n - 1][i] = 1;
                    mat[i][n - 1] = 1;
                }
                for(int i = 0; i < n / 2 - 1 && k != 0; i++){
                    for(int j = 0; j < n / 2 - 1 && k != 0; j++){
                        mat[i * 2 + 0][j * 2 + 0] = 1;
                        mat[i * 2 + 0][j * 2 + 1] = 1;
                        mat[i * 2 + 1][j * 2 + 0] = 1;
                        mat[i * 2 + 1][j * 2 + 1] = 1;
                        k -= 4;
                    }
                }
            }
            if(inv) {
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        mat[i][j] = mat[i][j] ^ 1;
                    }
                }
            }
        }
        cout << "Yes\n";
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << mat[i][j] << " \n"[j == n - 1];
            }
        }
    }
    
    return 0;
}
