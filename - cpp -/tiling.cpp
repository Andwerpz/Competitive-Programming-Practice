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

//AtCoder - AGC21C

//holy implementation practice. actually not that bad, was mostly straightforwards, even for
//the odd-odd case. 

//I'll rename A to H and B to V. First, we can see that if N * M < 2H + 2V, then there is simply
//not enough space for all the tiles, and we can just say no. From here on, we'll assume that 
//there is at least enough space to potentially fit in all the tiles.

//Otherwise, we can subdivide the solution into a few cases. For each case we can just test a 
//few small cases and draw some conclusions. 

// - Both N, M, are even
// It's optimal in this case to put down pairs of horizontal and vertical tiles in 2x2 blocks.
// The only situation where this case doesn't work is if the grid is supposed to be full, and 
// H and V are odd (this means that we have to put a horizontal and vertical tile in the same
// 2x2 block, which isn't going to work)

// - One of N, M, are even
// After filling in the extra row or column, then this case actually reduces down to the N, M
// both even case. 

// - Both N, M, are odd
// The most interesting case. Since N * M is odd, we're guaranteed to have at least one tile
// be empty. After some testing, I claim that any combination of H and V work, as long as 
// H <= N * (M - 1) / 2 and V <= M * (N - 1) / 2. To make it fit, we place either a 1x1
// or 3x3 square in the top left corner, pad the top row and left column, and then 2x2
// tile the remaining area. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, h, v;
    cin >> n >> m >> h >> v;
    if(2 * h + 2 * v > n * m) {
        cout << "NO\n";
        return 0;
    }
    vector<string> g(n, string(m, '.'));
    if(n % 2 == 0 && m % 2 == 0){   //both even
        if(2 * h + 2 * v == n * m && (h % 2 || v % 2)) {    
            //doesn't work if is full and one is odd count
            cout << "NO\n";
            return 0;
        }
        for(int i = 0; i < n; i += 2){
            for(int j = 0; j < m; j += 2){
                if(h != 0){
                    g[i + 0][j + 0] = '<';
                    g[i + 0][j + 1] = '>';
                    h --;
                    if(h != 0) {
                        g[i + 1][j + 0] = '<';
                        g[i + 1][j + 1] = '>';
                        h --;
                    }
                }
                else if(v != 0){
                    g[i + 0][j + 0] = '^';
                    g[i + 1][j + 0] = 'v';
                    v --;
                    if(v != 0){
                        g[i + 0][j + 1] = '^';
                        g[i + 1][j + 1] = 'v';
                        v --;
                    }
                }
            }
        }
    }
    else if(n % 2 && m % 2) {   //both odd
        if(h > n * (m - 1) / 2 || v > m * (n - 1) / 2) {    
            //if we just put h or v, then there's not enough space
            cout << "NO\n";
            return 0;
        }
        //put some odd square at the corner, only need to try sizes 1 and 3. 
        int sz = -1;
        for(int i = 1; i <= 3; i += 2){
            int H = h, V = v;
            //reserve for square
            H -= (i * i - 1) / 4, V -= (i * i - 1) / 4;
            if(H < 0 || V < 0) continue;
            //reserve for padding
            H -= (m - i) / 2, V -= (n - i) / 2;
            //check if remaining 2x2 tiles can fit everything
            H = max(H, 0), V = max(V, 0);
            int tile = ((n - 1) * (m - 1) - (i - 1) * (i - 1)) / 4;
            tile -= (H + 1) / 2 + (V + 1) / 2;
            if(tile >= 0) {
                sz = i;
                break;
            }
        }
        //create odd square
        for(int i = 1; i <= sz / 2; i++){ 
            int r = (sz / 2) - i, c = (sz / 2) - i;
            for(int j = 0; j < i; j++){
                g[r][c ++] = '<';
                g[r][c ++] = '>';
                h --;
            }
            for(int j = 0; j < i; j++){
                g[r ++][c] = '^';
                g[r ++][c] = 'v';
                v --;
            }
            for(int j = 0; j < i; j++){
                g[r][c --] = '>';
                g[r][c --] = '<';
                h --;
            }
            for(int j = 0; j < i; j++){
                g[r --][c] = 'v';
                g[r --][c] = '^';
                v --;
            }
        }
        //rest of padding
        for(int i = sz; i < m && h != 0; i += 2){
            g[0][i + 0] = '<';
            g[0][i + 1] = '>';
            h --;
        }
        for(int i = sz; i < n && v != 0; i += 2){
            g[i + 0][0] = '^';
            g[i + 1][0] = 'v';
            v --;
        }
        //2x2 tiles
        for(int i = 1; i < n; i += 2){
            for(int j = 1; j < m; j += 2){
                if(i < sz && j < sz) continue;
                if(h != 0){
                    g[i + 0][j + 0] = '<';
                    g[i + 0][j + 1] = '>';
                    h --;
                    if(h != 0) {
                        g[i + 1][j + 0] = '<';
                        g[i + 1][j + 1] = '>';
                        h --;
                    }
                }
                else if(v != 0){
                    g[i + 0][j + 0] = '^';
                    g[i + 1][j + 0] = 'v';
                    v --;
                    if(v != 0){
                        g[i + 0][j + 1] = '^';
                        g[i + 1][j + 1] = 'v';
                        v --;
                    }
                }
            }
        }
    }
    else {  //one odd
        //reduces to both even with one dedicated row or col
        int pn = n, pm = m;
        if(n % 2) {
            for(int i = 0; i < m && h != 0; i += 2){
                g[n - 1][i + 0] = '<';
                g[n - 1][i + 1] = '>';
                h --;
            }
            n --;
        }
        else {  //m % 2
            for(int i = 0; i < n && v != 0; i += 2) {
                g[i + 0][m - 1] = '^';
                g[i + 1][m - 1] = 'v';
                v --;
            }
            m --;
        }
        if(2 * h + 2 * v > n * m || 2 * h + 2 * v == n * m && (h % 2 || v % 2)) { 
            cout << "NO\n";
            return 0;
        }
        for(int i = 0; i < n; i += 2){
            for(int j = 0; j < m; j += 2){
                if(h != 0){
                    g[i + 0][j + 0] = '<';
                    g[i + 0][j + 1] = '>';
                    h --;
                    if(h != 0) {
                        g[i + 1][j + 0] = '<';
                        g[i + 1][j + 1] = '>';
                        h --;
                    }
                }
                else if(v != 0){
                    g[i + 0][j + 0] = '^';
                    g[i + 1][j + 0] = 'v';
                    v --;
                    if(v != 0){
                        g[i + 0][j + 1] = '^';
                        g[i + 1][j + 1] = 'v';
                        v --;
                    }
                }
            }
        }
        n = pn, m = pm;
    }
    cout << "YES\n";
    for(int i = 0; i < n; i++) cout << g[i] << "\n";
    
    return 0;
}