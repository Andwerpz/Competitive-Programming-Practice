#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

//NCPC 2025 - B

//trolled hard on this one :/
//make sure to read the problem, it isn't guaranteed that a book can be placed both
//upright and stacked. 
//also, books in the stack have to be sorted by height

//we can do dp: dp[i][w][h] = minimum width of upright books given
// i := number of books we've used so far
// w := width of stack
// h := height of stack

//we'll have to maintain a backtracking array, and make sure the final state has at
//least one upright and stacked book. 

const int MAXN = 101;
const int MAXH = 351;
const int MAXW = 901;
int dp[MAXN][MAXW][MAXH];
bool pv[MAXN][MAXW][MAXH];
short pvd[MAXN][MAXW][MAXH][2];
short h[MAXN], t[MAXN];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int N, H, W;
    cin >> N >> H >> W;
    for(int i = 0; i < N; i++) cin >> h[i] >> t[i];
    //dp[i][w][h] = minimum upright width given 
    // we've used i books
    // stack is width w
    // stack is height h
    for(int i = 0; i <= N; i++) {
        for(int j = 0; j <= W; j++) {
            for(int k = 0; k <= H; k++) {
                dp[i][j][k] = W + 1;
            }
        }
    }
    dp[0][0][0] = 0;
    for(int i = 0; i < N; i++) {
        for(short j = 0; j <= W; j++) {
            for(int k = 0; k <= H; k++) {
                for(int f = 0; f < 2; f++){
                    if(dp[i][j][k] == W + 1) continue;
                    //add as upright
                    if(dp[i][j][k] + t[i] <= W && h[i] <= H) {
                        int nval = dp[i][j][k] + t[i];
                        if(nval < dp[i + 1][j][k]) {
                            pv[i + 1][j][k] = 0;
                            dp[i + 1][j][k] = nval;
                            pvd[i + 1][j][k][0] = j;
                            pvd[i + 1][j][k][1] = k;
                        }
                    }
                    //add on stack
                    if(k + t[i] <= H && h[i] <= W) {
                        int nval = dp[i][j][k];
                        if(nval < dp[i + 1][max(j, h[i])][k + t[i]]) {
                            pv[i + 1][max(j, h[i])][k + t[i]] = 1;
                            dp[i + 1][max(j, h[i])][k + t[i]] = nval;
                            pvd[i + 1][max(j, h[i])][k + t[i]][0] = j;
                            pvd[i + 1][max(j, h[i])][k + t[i]][1] = k;
                        }
                    }
                }
            }
        }
    }
    //find sol
    int solw = -1, solh = -1;
    for(int i = 1; i <= W; i++) {
        for(int j = 1; j <= H; j++) {
            if(dp[N][i][j] != W + 1 && i + dp[N][i][j] <= W && dp[N][i][j] != 0) {
                solw = i, solh = j;
            }
        }
    }
    if(solw == -1) {
        cout << "impossible\n";
        return 0;
    }
    // cout << "WH : " << solw << " " << solh << " " << solf << "\n";
    vi up, st;
    for(int i = N; i >= 1; i--) {
        if(pv[i][solw][solh] == 0) up.push_back(i);
        else st.push_back(i);
        int nw = pvd[i][solw][solh][0];
        int nh = pvd[i][solw][solh][1];
        solw = nw;
        solh = nh;
    }
    sort(st.begin(), st.end(), [](int a, int b) -> bool {
        return h[a - 1] > h[b - 1];
    });
    cout << "upright ";
    for(int x : up) cout << x << " ";
    cout << "\n";
    cout << "stacked ";
    for(int x : st) cout << x << " ";
    cout << "\n";

    return 0;
}