#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - board

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++){
        cin >> g[i];
    }
    while(true) {
        bool change = false;
        for(int i = 0; i <= n - 3; i++){
            for(int j = 0; j <= m - 3; j++){
                char stamp = ' ';
                bool valid = true;
                for(int ii = 0; ii < 3; ii++){
                    for(int jj = 0; jj < 3; jj++){
                        char cur = g[i + ii][j + jj];
                        if(cur == 'W') {
                            valid = false;
                        }
                        if(stamp == ' ') {
                            if(cur != ' ') {
                                stamp = cur;
                            }
                        }
                        else {
                            if(cur != ' ' && cur != stamp) {
                                valid = false;
                            }
                        }
                    }
                }
                if(!valid || stamp == ' ') {
                    continue;
                }
                change = true;
                for(int ii = 0; ii < 3; ii++){
                    for(int jj = 0; jj < 3; jj++){
                        g[i + ii][j + jj] = ' ';
                    }
                }
            }
        }
        if(!change) {
            break;
        }
    }
    bool valid = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j] != 'W' && g[i][j] != ' '){
                valid = false;
            }
        }
    }
    cout << (valid? "YES" : "NO") << "\n";
    
    return 0;
}
