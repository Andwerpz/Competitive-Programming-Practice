#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1986B

//notice that during the course of applying operations, any number that is not initially greater than all of its 
//neighbors will not become greater than all of it's neighbors. This makes is so that you can just do
//one pass and apply all the operations to the elements that initially are greater than all of their
//neighbors. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> a[i][j];
            }
        }
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int ajmax = 0;
                for(int k = 0; k < 4; k++){
                    int nr = i + dr[k];
                    int nc = j + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                        continue;
                    }
                    ajmax = max(ajmax, a[nr][nc]);
                }
                a[i][j] = min(a[i][j], ajmax);
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}