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

//Codeforces - 1580B

//dp[i][j][k] = number of permutations of length i with exactly j numbers s.t. among all
//subsegments containing it, there are exactly k unique maxima. 
//consider fixing the position of the maximum element. Then, any number that wants to satisfy the condition
//from the left has 1 increased unique maximum, same from the right. 

//Special case is if k == 1, in which only the maximum can satisfy that, so dp[i][j][1] = [j == 1] * fac[i]

//the total complexity of this solution is around n^5, so we need lots of constant factor optimizations. 
//iterative is not going to work, as there are too many states to go through. 
//instead, use a recursive approach, to prune out states that are not relevant to the answer. 

const int N = 101;
ll dp[N][N][N];
ll nck[N][N];
ll fac[N];
int n, m, _k, p;

ll solve(int i, int j, int k){
    if(dp[i][j][k] != -1){
        return dp[i][j][k];
    }
    if(k == 1){
        if(j == 1){
            //any permutation satisfies this
            dp[i][j][k] = fac[i];
        }
        else {
            //no permutation satisfies this
            dp[i][j][k] = 0;
        }
        return dp[i][j][k];
    }
    //iterate the max position
    ll ans = 0;
    for(int ptr = 0; ptr < i; ptr++){
        int l = ptr;
        int r = i - ptr - 1;
        //distribute elements among halves
        ll sum = 0;
        for(int f = 0; f <= j; f++){
            if(f > l || j - f > r) continue;
            sum = (sum + solve(l, f, k - 1) * solve(r, j - f, k - 1)) % p;
        }
        ans = (ans + sum * nck[i - 1][l]) % p;
    }
    dp[i][j][k] = ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n >> _k >> m >> p;
    fac[0] = 1;
    for(int i = 1; i < N; i++){
        fac[i] = (fac[i - 1] * i) % p;
    }
    nck[0][0] = 1;
    for(int i = 1; i < N; i++){
        for(int j = 0; j <= i; j++){
            nck[i][j] = nck[i - 1][j];
            if(j != 0) nck[i][j] = (nck[i][j] + nck[i - 1][j - 1]) % p;
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                dp[i][j][k] = -1;
            }
        }
    }
    for(int i = 0; i <= _k; i++){
        dp[0][0][i] = 1;
    }
    for(int i = 0; i <= n; i++){
        for(int j = i + 1; j <= _k; j++){
            dp[i][0][j] = fac[i];
        }
    }
    cout << solve(n, m, _k) << "\n";
    
    return 0;
}