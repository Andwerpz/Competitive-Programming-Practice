#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//2024 ICPC Polish Collegiate Programming Contest - G

//implementation. 

vi dr = {-1, -1, -1, 0, 0, 1, 1, 1};
vi dc = {-1, 0, 1, -1, 1, -1, 0, 1};

int calc_score(vector<string>& g) {
    int n = g.size();
    int bcnt = 0, acnt = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        if(g[i][j] == 'M' || g[i][j] == 'P' || g[i][j] == 'O') bcnt ++;
        for(int k = 0; k < 8; k++){
            int nr = i + dr[k], nc = j + dc[k];
            if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
            if(g[i][j] == 'M' && g[nr][nc] == 'P') acnt ++;
            if(g[i][j] == 'P' && g[nr][nc] == 'M') acnt ++;
            if(g[i][j] == 'O' && g[nr][nc] == 'O') acnt ++;
        }
    }
    return bcnt + acnt / 2;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;
    vector<string> g(n);
    for(int i = 0; i < n; i++) cin >> g[i];
    int init_score = calc_score(g);
    int score = init_score;
    while(true) {
        int br = -1, bc = -1;
        int bs = -1;
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
            int cs = 0;
            if(g[i][j] == 'm' || g[i][j] == 'p' || g[i][j] == 'o') cs ++;
            for(int k = 0; k < 8; k++){
                int nr = i + dr[k], nc = j + dc[k];
                if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                if(g[i][j] == 'o' && g[nr][nc] == 'O') cs ++;
                if(g[i][j] == 'm' && g[nr][nc] == 'P') cs ++;
                if(g[i][j] == 'p' && g[nr][nc] == 'M') cs ++;
            }
            if(cs > bs) bs = cs, br = i, bc = j;
        }
        // cout << "BS : " << bs << endl;
        if(bs >= 2) {
            score += bs;
            g[br][bc] += 'A' - 'a';
        }
        else break;
    }
    cout << init_score << " " << score << "\n";
    for(int i = 0; i < n; i++) cout << g[i] << "\n";

    return 0;
}