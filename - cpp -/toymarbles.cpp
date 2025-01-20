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

//M(IT)^2 Winter 2025 Advanced Round 2 - P1

//we can interpret the initial marble positions as a functional graph. I claim that the minimum amount of operations is
//n - (num loops). 

void dfs(int cur, vi& a, vvi& c, vb& isl) {
    cout << "2 " << a[cur] + 1 << " " << cur + 1 << "\n";
    for(int x : c[cur]) if(!isl[x]) dfs(x, a, c, isl);
}   

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) a[i] --;
    vvi buck(n);
    for(int i = 0; i < n; i++) buck[a[i]].push_back(i);
    vvi loop;
    vvi c(n);
    for(int i = 0; i < n; i++){
        c[a[i]].push_back(i);
    }
    vb v(n, false);
    for(int i = 0; i < n; i++){
        if(v[i]) continue;
        vi path;
        int ptr = i;
        while(!v[ptr]) path.push_back(ptr), v[ptr] = true, ptr = a[ptr];
        int end = ptr;
        reverse(path.begin(), path.end());
        vi cloop;
        bool is_loop = false;
        for(int i = 0; i < path.size(); i++){
            cloop.push_back(path[i]);
            if(path[i] == end) {
                is_loop = true;
                break;
            }
        }
        reverse(cloop.begin(), cloop.end());
        if(is_loop) loop.push_back(cloop);
    }
    cout << n - loop.size() << "\n";
    vb isl(n, false);
    vi pv(n, -1);
    for(int i = 0; i < loop.size(); i++){
        for(int j = 0; j < loop[i].size(); j++){
            pv[loop[i][(j + 1) % loop[i].size()]] = loop[i][j];
            isl[loop[i][j]] = true;
            // cout << "LOOP : " << i << " " << loop[i][j] << "\n";
        }
    }
    for(int i = 0; i < loop.size(); i++){
        for(int j = (int) loop[i].size() - 2; j >= 0; j--){
            cout << "1 " << loop[i][j] + 1 << " " << loop[i][j + 1] + 1 << "\n";
        }
    }
    for(int i = 0; i < n; i++){
        if(isl[i]) for(int x : c[i]) if(!isl[x]) dfs(x, a, c, isl);
        // if(isl[i]) for(int x : c[i]) if(!isl[x]) cout << "X : " << x << "\n";
    }
    
    return 0;
}