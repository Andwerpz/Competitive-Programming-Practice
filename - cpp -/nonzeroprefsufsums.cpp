#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//The 3rd Universal Cup. Stage 18: Southeastern Europe - B

ll mod;

ll binpow(ll a, ll b) {
    ll pow = a, ans = 1;
    while(b != 0){
        if(b % 2) ans = (ans * pow) % mod;
        b /= 2;
        pow = (pow * pow) % mod;
    }
    return ans;
}

ll mod_inv(ll a) {
    return binpow(a, mod - 2);
}

//a / b
ll mod_divide(ll a, ll b) {
    return a * mod_inv(b);
}

vl fac, invfac;
void fac_init(int N) {
    fac = vl(N + 1), invfac = vl(N + 1);
    fac[0] = 1;
    for(int i = 1; i <= N; i++){
        fac[i] = (fac[i - 1] * i) % mod;
    }
    invfac[N] = mod_inv(fac[N]);
    for(int i = N - 1; i >= 0; i--) {
        invfac[i] = (invfac[i + 1] * (i + 1)) % mod;
    }
}

ll nck(ll n, ll k) {
    return ((fac[n] * invfac[k]) % mod * invfac[n - k]) % mod;
}

ll solve(int n, int m) {
    //dp[i][j][k] = number of sorted arrays of length i with sum j with last element k

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    fac_init(1e6);
    int n, m;
    cin >> n >> m >> mod;


    return 0;
}