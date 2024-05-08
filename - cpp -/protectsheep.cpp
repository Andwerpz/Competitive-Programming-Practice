#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 948A

//just fill every tile with a dog. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++){
        cin >> g[i];
    }
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    bool is_valid = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k < 4; k++){
                int nr = i + dr[k];
                int nc = j + dc[k];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    continue;
                }
                if(g[i][j] == 'S' && g[nr][nc] == 'W') {
                    is_valid = false;
                }
            }
        }
    }
    if(!is_valid) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j] == '.') {
                g[i][j] = 'D';
            }
        }
        cout << g[i] << "\n";
    }
    
    return 0;
}
