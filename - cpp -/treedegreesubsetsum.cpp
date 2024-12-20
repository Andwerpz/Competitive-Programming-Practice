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

//AtCoder - ARC125F

//let d_i = (degree of vertex i) - 1. 
//let m(s) be the minimum number of d_i to choose to make sum s, and M(s) be the maximum number.
//The editorial claims that if you want to choose x elements in d to create s, then it will work
//iff m(s) <= x <= M(s). So the problem reduces to just computing m(s) and M(s) for all s. 
//look for the editorial for the proof of this fact, I'm just going to focus on how to compute m and M. 

//first note that d_i can have at most around sqrt(n) unique values. If we can process each unique value in 
//faster than O(v) time (where v is the number of values in d that take on that value). 

//it turns out that we can. If we have v of the same value, we can present log(v) options such that
//we can represent any amount in [0, v] using some combination of the choices. Just give the bits
//less than v, and the remainder. 

//final complexity is O(n * sqrt(n) * log(n)). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n, 0), f(n, 0);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        a[u] ++, a[v] ++;
    }
    for(int x : a) f[x - 1] ++;
    vi m(n * 2 + 1, 1e9), M(n * 2 + 1, -1e9);
    m[0] = 0, M[0] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= f[i]; f[i] -= j, j *= 2){
            for(int k = m.size() - 1; k >= i * j; k--){
                m[k] = min(m[k], m[k - i * j] + j);
                M[k] = max(M[k], M[k - i * j] + j);
            }
        }
        if(f[i]) {
            for(int k = m.size() - 1; k >= i * f[i]; k--){
                m[k] = min(m[k], m[k - i * f[i]] + f[i]);
                M[k] = max(M[k], M[k - i * f[i]] + f[i]);
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < m.size(); i++) {
        if(M[i] < 0) continue;
        ans += M[i] - m[i] + 1;
    }
    cout << ans << "\n";
    
    return 0;
}