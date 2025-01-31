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

//2022 ICPC NAC - F

//each team can be in one of 2^n states (what problems they have considered)
//for each state, keep track of the percentage of teams in that state at any moment in time

//state transition will be picking a problem to read, reading it, either realizing they can't solve it, 
//or solving it (which takes more time). 

//at every moment in time, we'll have to determine some amount of solves on each problem. 
//We'll keep a running total.

//dp[i][j] = at time t, what percentage of teams already considered bitmask j 
//sol[t][i] = at time t, what percentage of teams solved problem i?

//to get this to not TLE, have to do some constant factor optimizations. Seems like the most important one is
//to skip processing a dp state if the percentage of teams there is 0

const int N = 17, T = 100;
int r[N], c[N];
ld p[N], dp[T + 1][(1 << N)], sol[T + 1][N];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, t;
    cin >> n >> t;
    for(int i = 0; i < n; i++) cin >> r[i] >> c[i] >> p[i];
    dp[0][0] = 1;
    for(int i = 0; i < t; i++){
        for(int j = 0; j < (1 << n); j++){
            if(dp[i][j] == 0) continue; //lil optimization
            ld sum = 0;
            int cnt = 0;
            for(int k = 0; k < n; k++){
                if(!(j & (1 << k))) sum += sol[i][k], cnt ++;
            }
            if(cnt == 0) {
                //do nothing
                dp[i + 1][j] += dp[i][j];
                continue;
            }
            for(int k = 0; k < n; k++){
                if(j & (1 << k)) continue;
                ld read_prob = (ld) 1.0 / (ld) cnt;
                if(sum != 0) read_prob = sol[i][k] / sum;
                //people who read but can't solve
                dp[min(t, i + r[k])][j ^ (1 << k)] += dp[i][j] * read_prob * (1.0 - p[k]);
                //people who read and solve
                dp[min(t, i + r[k] + c[k])][j ^ (1 << k)] += dp[i][j] * read_prob * p[k];
                //if we can solve in time, add to percentage teams solving
                if(i + r[k] + c[k] <= t) sol[i + r[k] + c[k]][k] += dp[i][j] * read_prob * p[k];
            }
        }
        for(int j = 0; j < n; j++){
            sol[i + 1][j] += sol[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        cout << fixed << setprecision(10) << sol[t][i] << "\n";
    }
    
    return 0;
}