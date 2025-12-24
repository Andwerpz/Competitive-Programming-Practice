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

//2025 ICPC Asia Chengdu Regional Contest - B

//we can do dp/matrix expo. 

//the only relevant state we need to store is the set of moves that we used in the previous round. 
//dp[B][S][E] = maximum amount of damage given that
// - we used 2^B rounds
// - we started off on a round with previous round using only moves in set S
// - our last round uses only moves in set E

//we can see that dp[B][S][E] = max(dp[B - 1][S][M] + dp[B - 1][M][E]) over all sets M. 
//to compute dp[0][S][E], we can do a little knapsack dp. 

ll do_dp(vl a, vl c, ll m) {
    assert(a.size() == c.size());
    int n = a.size();
    vl dp(m + 1, -1);
    dp[0] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = m; j >= 0; j--) {
            if(j - c[i] < 0) break;
            if(dp[j - c[i]] == -1) continue;
            dp[j] = max(dp[j], dp[j - c[i]] + a[i]);
        }
    }
    ll ans = 0;
    for(int i = 0; i <= m; i++) ans = max(ans, dp[i]);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        ll n, m, k, r;
        cin >> n >> m >> k >> r;
        vl a(n), c(n);
        for(int i = 0; i < n; i++) cin >> a[i] >> c[i];
        const int B = 31;
        vector<vvl> tmat(B, vvl((1 << n), vl((1 << n), -1e18)));
        //ground matrix
        for(int i = 0; i < (1 << n); i++) {
            for(int j = 0; j < (1 << n); j++) {
                vl ca(0), cc(0);
                for(int b = 0; b < n; b++) {
                    if(!(j & (1 << b))) continue;
                    ca.push_back(a[b]);
                    if(i & (1 << b)) cc.push_back(c[b] + k);
                    else cc.push_back(c[b]);
                }
                ll atk = do_dp(ca, cc, m);
                tmat[0][i][j] = atk;
                // cout << "TRANSITION : " << i << " " << j << " " << atk << "\n";
            }
        }
        //derived matrices
        for(int b = 1; b < B; b++) {
            for(int S = 0; S < (1 << n); S++) {
                for(int E = 0; E < (1 << n); E++) {
                    for(int M = 0; M < (1 << n); M++) {
                        tmat[b][S][E] = max(tmat[b][S][E], tmat[b - 1][S][M] + tmat[b - 1][M][E]);
                    }
                }
            }
        }
        //calc ans
        vvl mat((1 << n), vl((1 << n), 0));
        for(int b = B - 1; b >= 0; b--) {
            if((1 << b) > r) continue;
            r -= (1 << b);
            vvl nmat((1 << n), vl((1 << n), 0));
            for(int S = 0; S < (1 << n); S++) {
                for(int E = 0; E < (1 << n); E++) {
                    for(int M = 0; M < (1 << n); M++) {
                        nmat[S][E] = max(nmat[S][E], mat[S][M] + tmat[b][M][E]);
                    }
                }
            }
            mat = nmat;
        }
        ll ans = 0;
        for(int i = 0; i < (1 << n); i++) {
            ans = max(ans, mat[0][i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}