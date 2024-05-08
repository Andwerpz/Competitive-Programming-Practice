#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC 04-05-2023 - H

//use DSU to keep track of when to merge two sections. Keep a running answer. 

struct DSU {
    int N;
    vector<int> dsu;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    void dsu_init() {
        for(int i = 0; i < N; i++){
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        dsu[rb] = ra;
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<char>> g(n, vector<char>(m, '.'));
    DSU dsu(n * m);
    int ans = 0;
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    for(int i = 0; i < n * m; i++){
        int r, c;
        cin >> r >> c;
        r --;
        c --;
        ans ++;
        char type;
        cin >> type;
        g[r][c] = type;
        for(int j = 0; j < 4; j++){
            int nr = r + dr[j];
            int nc = c + dc[j];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                continue;
            }   
            if(g[nr][nc] == type) {
                ans -= dsu.unify(r * m + c, nr * m + nc);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
