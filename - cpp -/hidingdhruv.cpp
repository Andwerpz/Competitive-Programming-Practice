#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//ACPC 2024 Spring Contest - H

//first, greedily tile the pattern across the grid. It's guaranteed that you'll have at least X occurrences of 
//the pattern. 

//next, we need to eliminate some patterns because there might be more than X occurrences. We can start from the top left 
//corner, and if we find an occurrence of a pattern, we can toggle it's top left corner to only remove that occurrence. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int r, c, x;
    cin >> r >> c >> x;
    vector<string> p(r);
    for(int i = 0; i < r; i++){
        cin >> p[i];
    }
    vector<string> g(1000, string(1000, '#'));
    for(int i = 0; i < 1000 - r + 1; i += r){
        for(int j = 0; j < 1000 - c + 1; j += c){
            for(int ii = 0; ii < r; ii++){
                for(int jj = 0; jj < c; jj++){
                    g[i + ii][j + jj] = p[ii][jj];
                }
            }
        }
    }
    vector<vector<bool>> cp(1000, vector<bool>(1000, false));
    for(int i = 0; i < 1000 - r + 1; i++){
        for(int j = 0; j < 1000 - c + 1; j++){
            bool is_valid = true;
            for(int ii = 0; ii < r; ii++){
                for(int jj = 0; jj < c; jj++){
                    if(g[i + ii][j + jj] != p[ii][jj]) {
                        is_valid = false;
                    }
                }
            }
            cp[i][j] = is_valid;
            x -= is_valid;
        }
    }
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 1000; j++){
            if(x < 0 && cp[i][j]) {
                g[i][j] = g[i][j] == '#'? '.' : '#';
                x ++;
            }
        }
    }
    cout << "1000 1000\n";
    for(int i = 0; i < 1000; i++){
        cout << g[i] << "\n";
    }
    
    return 0;
}
