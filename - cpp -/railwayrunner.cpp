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

//Kattis - railwayrunner

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> g(n);
    for(int i = 0; i < n; i++) cin >> g[i];
    //construct graph
    vvi id(n, vi(3));
    int idptr = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 3; j++) id[i][j] = idptr ++;
    }
    vvi c(idptr);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 3; j++){
            if(j != 2 && g[i][j] == '.' && g[i][j + 1] == '.') c[id[i][j]].push_back(id[i][j + 1]);
            if(j != 0 && g[i][j] == '.' && g[i][j - 1] == '.') c[id[i][j]].push_back(id[i][j - 1]);
            if(j != 2 && g[i][j] == '*' && g[i][j + 1] == '*') c[id[i][j]].push_back(id[i][j + 1]);
            if(j != 0 && g[i][j] == '*' && g[i][j - 1] == '*') c[id[i][j]].push_back(id[i][j - 1]);
            if(i != n - 1) {
                bool down = false;
                down |= g[i][j] == '*' && (g[i + 1][j] == '.' || g[i + 1][j] == '*');
                down |= g[i][j] == '/' && g[i + 1][j] == '*';
                down |= g[i][j] == '.' && (g[i + 1][j] == '.' || g[i + 1][j] == '/');
                if(down) c[id[i][j]].push_back(id[i + 1][j]);
            }
        }
    }
    //traverse graph
    vb v(idptr, false);
    queue<int> q;
    for(int i = 0; i < 3; i++){
        if(g[0][i] != '.') continue;
        v[id[0][i]] = true;
        q.push(id[0][i]);
    }
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int x : c[cur]) if(!v[x]) v[x] = true, q.push(x);
    }
    bool ans = v[id[n - 1][0]] | v[id[n - 1][1]] | v[id[n - 1][2]];
    cout << (ans? "YES" : "NO") << "\n";
    
    return 0;
}