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

//CodeSprint LA 2025 Open - L

//cool randomization solution. not sure if intended 

//dp[i][j][k] = maximum number of players assigned given that we've considered i players, current 
//strength diff is j, and player count diff is k. This works for sure if we set the bounds of j and k
//to 300 * 150 and 150 respectively, however that will TLE. 

//observe that if we lower the bounds of j and k, then we'll find a solution if the people are ordered 
//nicely within the array. Since the ordering of the people doesn't matter, we can rearrange the people 
//however we like before doing the dp. How can we find such a nice ordering? Notice that since the 
//strengths and amount of people on each team need to be the same, if we just randomly shuffle the array
//we should be able to find a solution with high probability.

//another way to look at this is : suppose there exists a solution. This solution must have equal people 
//on both teams. Then, if we shuffle the array, each team will be evenly distributed throughout the 
//array, so when constructing this solution, the difference on the number of people will remain relatively
//small. 

const int N = 300;
const int J = 300 * 10;
const int K = 10;
int dp[N + 1][J * 2 + 1][K * 2 + 1];

int calc_ans(int n, vi& a) {
    random_shuffle(a.begin(), a.end());
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= J * 2; j++){
            for(int k = 0; k <= K * 2; k++){
                dp[i][j][k] = -1;
            }
        }
    }
    dp[0][J][K] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= J * 2; j++){
            for(int k = 0; k <= K * 2; k++){
                if(dp[i][j][k] == -1) continue;
                //do nothing
                dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k]);
                //add to first team
                if(j + a[i] <= J * 2 && k + 1 <= K * 2) {
                    dp[i + 1][j + a[i]][k + 1] = max(dp[i + 1][j + a[i]][k + 1], dp[i][j][k] + 1);
                }
                //add to second team
                if(j - a[i] >= 0 && k - 1 >= 0) {
                    dp[i + 1][j - a[i]][k - 1] = max(dp[i + 1][j - a[i]][k - 1], dp[i][j][k] + 1);
                }
            }
        }
    }
    return dp[n][J][K] / 2;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    int ans = -1;
    for(int i = 0; i < 10; i++){
        ans = max(ans, calc_ans(n, a));
    }
    cout << (ans <= 0? -1 : ans) << "\n";
    
    return 0;
}