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

//Codeforces - 1497 E1, E2

//for the easy version, a greedy solution is sufficient. Since the first element must be part of a segment, 
//might as well extend it as far as you can. Then, the next element can be extended and so on. 

//to efficiently extend the segments, observe that two numbers will only make a perfect square when 
//multiplied together iff their odd prime powers match. Define id(x) as the product of odd prime powers of x. 
//so when we add on another element to the segment x, we just want to see if some number y that is already 
//in the segment satisfies id(y) == id(x), in which case we need to start a new segment. 

//for the hard version, we can pick up to k elements and arbitrarily set their id, so the greedy solution
//doesn't work. Instead, let's use dp: 
//dp[i][j] = minimum segments needed to partition first i elements given j operations used
//transitions will be adding another segment given some amount of operations from 0 to k. 

//to help with transitions, let's precompute another array, ext:
//ext[i][j] = max segment ending point starting at i given you made j operations within segment 
//ext can be precomputed in O(n * k) time, and the dp can be computed in O(n * k^2) time. 

//note that this solution takes some constant factor optimization to not TLE. There exists a way to
//optimize the dp down to O(n * k), but I'm lazy. 

const int pN = 1e7 + 100;
int pr_cnt = 0;
int lp[pN], pr[pN], f[pN];
void prime_sieve() {
    for(ll i = 2; i < pN; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr[pr_cnt ++] = i;
        }
        for (ll j = 0; i * pr[j] < pN; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

const int N = 2e5 + 5;
const int K = 20;
int a[N], ext[N][K + 1], dp[N][K + 1];
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve();
    int t;
    cin >> t;
    while(t--){
        int n, _k;
        cin >> n >> _k;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            int id = 1;
            while(a[i] != 1) {
                int p = lp[a[i]];
                if(id % p == 0) id /= p;
                else id *= p;
                a[i] /= p;
            }
            a[i] = id;
        }
        //ext[i][j] = max segment ending point starting at i given you made j operations within segment 
        for(int ops = 0; ops <= _k; ops++){
            int r = 0, cnt = 0;
            for(int i = 0; i < n; i++){
                while(r != n && (f[a[r]] != 0) + cnt <= ops) {
                    cnt += (f[a[r]] != 0);
                    f[a[r]] ++;
                    r ++;
                }
                ext[i][ops] = r;
                f[a[i]] --;
                cnt -= f[a[i]] != 0;
            }
        }
        //dp[i][j] = minimum segments needed to partition first i elements given j operations
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= _k; j++){
                dp[i][j] = 1e9;
            }
        }
        dp[0][0] = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= _k; j++){
                for(int k = 0; j + k <= _k; k++){
                    dp[ext[i][k]][j + k] = min(dp[ext[i][k]][j + k], dp[i][j] + 1);
                }
            }
        }
        int ans = 1e9;
        for(int i = 0; i <= _k; i++){
            ans = min(ans, dp[n][i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}