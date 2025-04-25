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

//3rd Universal Cup Stage 31 : Wroclaw - K

//first make the observation that either all the even lanterns must be on, or all the odd lanterns
//must be on. If you color the board in a checkerboard fashion, then you'll notice that if both of these
//are not true, then there has to be some white (or black, depends on how you color) tile that isn't lit.

//one way to see this is start with all the lanterns, and then take away one even and one odd lantern. 
//this will always uncover at least 1 tile. 

//Then, we can do bruteforce backtracking using this heuristic, and some more heuristics. My current 
//solution barely passes (1477 / 1500 ms), but you can prolly do better, as I put in some pretty expensive
//checks. 

int ansc = 1e9;
string anss = "";

int cnt = 0;
int n;
vi dr = {-1, -1, -1, 0, 0, 1, 1, 1};
vi dc = {-1, 0, 1, -1, 1, -1, 0, 1};
void solve(int ind, vvi& g, string& s, int miss, int cans, string& canss) {
    // cout << "SOLVE : " << ind << " " << miss << " " << canss << "\n";
    int min_cans = cans;
    for(int i = ind; i < n; i++) min_cans += s[i] == '#';
    if(min_cans >= ansc) return;
    if(ind == g.size()) {
        if(miss == 0 && cans < ansc) {
            ansc = cans, anss = canss;
        }
        return;
    }
    cnt ++;
    //try not placing
    bool haveto = false;
    for(int i = 0; i < ind; i++){
        if(g[i][ind] == 0 || g[ind][i] == 0) haveto = true;
    }
    if(s[ind] != '#' && !haveto) {
        solve(ind + 1, g, s, miss, cans, canss);
    }
    //try placing
    bool need = false;
    int nmiss = miss;
    for(int i = 0; i < 8; i++){
        for(int j = 0; ; j++){
            int nr = ind + dr[i] * j, nc = ind + dc[i] * j;
            if(nr < 0 || nc < 0 || nr >= n || nc >= n) break;
            g[nr][nc] ++;
            if(g[nr][nc] == 1) need = true, nmiss --;
        }
    }
    // cout << "G : \n";
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++) cout << g[i][j] << " ";
    //     cout << "\n";
    // }
    if(need || s[ind] == '#') {
        canss[ind] = '#';
        solve(ind + 1, g, s, nmiss, cans + 1, canss);
        canss[ind] = '.';
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; ; j++){
            int nr = ind + dr[i] * j, nc = ind + dc[i] * j;
            if(nr < 0 || nc < 0 || nr >= n || nc >= n) break;
            g[nr][nc] --;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    n = s.size();
    vvi g(n, vi(n, 0));
    string canss(n, '.');
    string sodd = s, seven = s;
    for(int i = 0; i < n; i++) {
        if(i % 2) sodd[i] = '#';
        else seven[i] = '#';
    }
    solve(0, g, sodd, n * n, 0, canss);
    solve(0, g, seven, n * n, 0, canss);
    // cout << "CNT : " << cnt << "\n";
    cout << ansc << "\n" << anss << "\n";
    
    return 0;
}