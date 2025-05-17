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

//Topcoder - 6179

//implementation practice
//just do subrectangle dp. Need to precompute which folds are valid. 

const int N = 55;
int dp[N][N][N][N];
int vv[N][N][N];    //vv[column][top][bottom] = max fold
int hv[N][N][N];    //hv[row][left][right] = max fold

class MapFolder {
public:
    int solve(vector<string>& g, int r1, int c1, int r2, int c2) {
        if(r1 == r2 && c1 == c2) return 0;  //yay
        if(dp[r1 / 2][c1 / 2][r2 / 2][c2 / 2] != 0) return dp[r1 / 2][c1 / 2][r2 / 2][c2 / 2];
        int ans = 1e9;
        //fold horizontally
        for(int i = r1 + 1; i < r2; i += 2){
            int ssz = min(i - r1, r2 - i);
            if(hv[i][c1][c2] >= ssz) {
                if(i - r1 >= r2 - i) {  //fold bottom to top
                    ans = min(ans, solve(g, r1, c1, i - 1, c2) + 1);
                }
                else {  //fold top to bottom
                    ans = min(ans, solve(g, i + 1, c1, r2, c2) + 1);
                }
            }
        }
        //fold vertically
        for(int i = c1 + 1; i < c2; i += 2){
            int ssz = min(i - c1, c2 - i);
            if(vv[i][r1][r2] >= ssz) {
                if(i - c1 >= c2 - i){   //fold right to left
                    ans = min(ans, solve(g, r1, c1, r2, i - 1) + 1);
                }
                else {  //fold left to right
                    ans = min(ans, solve(g, r1, i + 1, r2, c2) + 1);
                }
            }
        }
        dp[r1 / 2][c1 / 2][r2 / 2][c2 / 2] = ans;
        return ans;
    }

    int minFolds(vector<string> themap) {
        //make map nicer
        int n = themap.size(), m = themap[0].size() * 2 + 1;
        vector<string> g(n, string(m, ' '));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < themap[i].size(); j++){
                if(i % 2 == 0) g[i][j * 2 + 1] = themap[i][j];
                else g[i][j * 2] = themap[i][j];
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(i % 2 == 0 && j % 2 == 0) g[i][j] = 'X';
            }
        }
        for(int i1 = 0; i1 < N; i1++){
            for(int i2 = 0; i2 < N; i2++){
                for(int i3 = 0; i3 < N; i3++){
                    vv[i1][i2][i3] = 0;
                    hv[i1][i2][i3] = 0;
                    for(int i4 = 0; i4 < N; i4++){
                        dp[i1][i2][i3][i4] = 0;
                    }
                }
            }
        }
        //precompute which folds are valid
        //horizontal
        for(int i = 1; i < n; i += 2) {
            for(int l = 0; l < m; l += 2){
                for(int r = l; r < m; r += 2){
                    //everything needs to be the same 
                    bool is_valid = true;
                    for(int j = l + 2; j <= r; j += 2){
                        if(g[i][j] != g[i][j - 2]) is_valid = false;
                    }
                    if(!is_valid) continue;
                    //check to make sure that everything is opposite
                    for(int j = 1; j <= min(i, n - i - 1); j++) {
                        for(int k = l; k <= r; k++){
                            if(g[i + j][k] != 'u' && g[i + j][k] != 'd') continue;
                            if(g[i + j][k] == g[i - j][k]) is_valid = false;
                        }
                        if(!is_valid) break;
                        hv[i][l][r] = j;
                    }
                }
            }
        }
        //vertical
        for(int i = 1; i < m; i += 2) {
            for(int l = 0; l < n; l += 2){
                for(int r = l; r < n; r += 2){
                    //everything needs to be the same
                    bool is_valid = true;
                    for(int j = l + 2; j <= r; j += 2){
                        if(g[j][i] != g[j - 2][i]) is_valid = false;
                    }
                    if(!is_valid) continue;
                    //check to make sure opposite
                    for(int j = 1; j <= min(i, m - i - 1); j++){
                        for(int k = l; k <= r; k++){
                            if(g[k][i + j] != 'u' && g[k][i + j] != 'd') continue;
                            if(g[k][i + j] == g[k][i - j]) is_valid = false;
                        }
                        if(!is_valid) break;
                        vv[i][l][r] = j;
                    }
                }
            }
        }
        int ans = solve(g, 0, 0, n - 1, m - 1);
        if(ans == 1e9) ans = -1;
        return ans;
    }
};

int main() {
    int n0; cin >> n0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> arg0(n0);
    for (int i=0;i<n0;++i) { getline(cin, arg0[i]); }
    auto c = MapFolder();
    int ret = c.minFolds(arg0);
    cout << ret;
}