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

//2024 NA Mid Central Regional - G

//IMPLEMENTATION

//use auxillary nodes to represent the switch states. 

char swap_case(char c) {
    if('A' <= c && c <= 'Z') {
        return c + 'a' - 'A';
    }
    return c + 'A' - 'a';
}

bool is_upper(char c){
    return 'A' <= c && c <= 'Z';
}

bool is_mobst(char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

int mobst_ind(char c) {
    return is_upper(c) ? c - 'A' : c - 'a';
}

int d[(1 << 4)][10][10][10][10];
bool v[(1 << 4)][10][10][10][10];
vector<string> g[(1 << 4)];
int n, m;

void set_v(array<int, 5>& p) {
    v[p[0]][p[1]][p[2]][p[3]][p[4]] = true;
}

bool is_v(array<int, 5>& p){
    return v[p[0]][p[1]][p[2]][p[3]][p[4]];
}

int get_d(array<int, 5>& p){
    return d[p[0]][p[1]][p[2]][p[3]][p[4]];
}

void set_d(array<int, 5>& p, int val) {
    d[p[0]][p[1]][p[2]][p[3]][p[4]] = val;
}

bool is_obst(int bits, int r, int c){
    char ch = g[bits][r][c];
    if(is_mobst(ch)) {
        return is_upper(ch);
    }
    return ch == '#';
}

bool is_pit(int r, int c) {
    if(r < 0 || c < 0 || r >= n || c >= m) return true;
    char ch = g[0][r][c];
    return ch == '*';
}

bool is_switch(int r, int c) {
    char ch = g[0][r][c];
    return '1' <= ch && ch <= '4';
}

int get_switch_ind(int r, int c){
    return g[0][r][c] - '1';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n >> m;
    for(int i = 0; i < (1 << 4); i++){
        g[i] = vector<string>(n);
    }
    for(int i = 0; i < n; i++){
        cin >> g[0][i];
    }
    array<int, 5> spos = {0, -1, -1, -1, -1};
    array<int, 5> epos = {0, -1, -1, -1, -1};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            if(g[0][i][j] != 'S'){
                continue;
            }
            g[0][i][j] = '.';
            if(spos[1] == -1){
                spos[1] = i;
                spos[2] = j;
            }
            else {
                spos[3] = i;
                spos[4] = j;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            if(g[0][i][j] != 'E'){
                continue;
            }
            g[0][i][j] = '.';
            if(epos[1] == -1){
                epos[1] = i;
                epos[2] = j;
            }
            else {
                epos[3] = i;
                epos[4] = j;
            }
        }
    }
    for(int bits = 1; bits < (1 << 4); bits++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                g[bits][i][j] = g[0][i][j];
                if(!is_mobst(g[0][i][j])) {
                    continue;
                }
                if(bits & (1 << mobst_ind(g[0][i][j]))) {
                    g[bits][i][j] = swap_case(g[bits][i][j]);
                }
            }
        }
    }

    // for(int bits = 0; bits < (1 << 4); bits++){
    //     for(int i = 0; i < n; i++){
    //         for(int j = 0; j < m; j++) {
    //             cout << g[bits][i][j] << " ";
    //         }
    //         cout << "\n";
    //     }
    //     cout << "\n";
    // }

    vi dr = {-1, 1, 0, 0};
    vi dc = {0, 0, -1, 1};
    queue<array<int, 5>> q;
    q.push(spos);
    set_v(spos);
    set_d(spos, 0);
    while(q.size() != 0){
        array<int, 5> cur = q.front();
        q.pop();
        int bits = cur[0];
        int r1 = cur[1];
        int c1 = cur[2];
        int r2 = cur[3];
        int c2 = cur[4];
        // cout << "STATE : " << bits << " " << r1 << " " << c1 << " " << r2 << " " << c2 << " " << get_d(cur) << "\n";
        for(int i = 0; i < 4; i++) {
            int nr1 = r1 + dr[i];
            int nc1 = c1 + dc[i];
            int nr2 = r2 + dr[i];
            int nc2 = c2 + dc[i];
            //check if one person stepped into a pit
            if(is_pit(nr1, nc1) || is_pit(nr2, nc2)) {
                continue;
            }
            //see if a person is walking into an obstacle
            if(is_obst(bits, nr1, nc1)) {
                nr1 = r1;
                nc1 = c1;
            }
            if(is_obst(bits, nr2, nc2)) {
                nr2 = r2;
                nc2 = c2;
            }
            //see if both in same position
            if(nr1 == nr2 && nc1 == nc2) {
                continue;
            }
            //see if person is walking into switch (has to not be stationary)
            int nbits = bits;
            if(is_switch(nr1, nc1) && (nr1 != r1 || nc1 != c1)) {
                nbits ^= (1 << get_switch_ind(nr1, nc1));
            }
            if(is_switch(nr2, nc2) && (nr2 != r2 || nc2 != c2)) {
                nbits ^= (1 << get_switch_ind(nr2, nc2));
            }
            //see if switch caused person to be inside obstacle
            if(is_obst(nbits, nr1, nc1) || is_obst(nbits, nr2, nc2)) {
                continue;
            }
            //move to next state
            array<int, 5> next = {nbits, nr1, nc1, nr2, nc2};
            if(!is_v(next)) {
                set_v(next);
                set_d(next, get_d(cur) + 1);
                q.push(next);
            }
        }   
    }
    int ans = 1e9;
    for(int i = 0; i < (1 << 4); i++){
        epos[0] = i;
        if(is_v(epos)) {
            ans = min(ans, get_d(epos));
        }
    }
    swap(epos[1], epos[3]);
    swap(epos[2], epos[4]);
    for(int i = 0; i < (1 << 4); i++){
        epos[0] = i;
        if(is_v(epos)) {
            ans = min(ans, get_d(epos));
        }
    }
    cout << ans << "\n";
    
    return 0;
}