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

//2024 ICPC Polish Collegiate Programming Contest - I

//observe that to maximize the imbalance, we always want to assign the k worst players to one team, and the k best players
//to the other team. So the only leeway we get is the best players on the worst team, and the worst players on the best team.

//there are two cases: the middle players are the same value or different. 

//if they're different, just multiply the ways to pick for each team. 

//if they're same, first choose the players you're going to pick, then divvy them up between the teams. Special case is if
//all the players are the same strength, then you have to divide your answer by 2. 

const ll mod = 1e9 + 7;

ll binpow(ll a, ll b) {
    ll pow = a, ans = 1;
    while(b != 0){
        if(b % 2) ans = (ans * pow) % mod;
        pow = (pow * pow) % mod;
        b /= 2;
    }
    return ans;
}

ll modinv(ll a) {
    return binpow(a, mod - 2);
}

vl fac, invfac;
void fac_init(int N) {
    fac = vl(N + 1), invfac = vl(N + 1);
    fac[0] = 1;
    for(int i = 1; i <= N; i++) fac[i] = (fac[i - 1] * i) % mod;
    invfac[N] = modinv(fac[N]);
    for(int i = N; i > 0; i--) invfac[i - 1] = (invfac[i] * i) % mod;
}

ll binom(ll n, ll k) {
    return ((fac[n] * invfac[k]) % mod * invfac[n - k]) % mod;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    fac_init(1e6);
    int n, k;
    cin >> n >> k;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    int minv = a[k - 1], maxv = a[n - k];
    ll ans = 1;
    if(minv == maxv) {
        int f = 0, mint = 0, maxt = 0;
        for(int i = 0; i < n; i++){
            f += a[i] == minv;
        }
        for(int i = 0; i < k; i++){
            mint += a[i] == minv;
            maxt += a[n - 1 - i] == maxv;
        }
        // ans = (ans * binom(f, mint + maxt));
        // ans = (ans * binom(mint + maxt, mint));
        ans = (ans * binom(f, mint)) % mod;
        ans = (ans * binom(f - mint, maxt)) % mod;
        // cout << binom(f, mint + maxt) << " " << binom(mint + maxt, mint) << "\n";
        if(f == n) ans = (ans * modinv(2)) % mod;
    }
    else {
        int minf = 0, maxf = 0;
        for(int i = 0; i < n; i++) {
            minf += a[i] == minv;
            maxf += a[i] == maxv;
        }
        int mint = 0, maxt = 0;
        for(int i = 0; i < k; i++){
            mint += a[i] == minv;
            maxt += a[n - 1 - i] == maxv;
        }
        ans = (ans * binom(minf, mint)) % mod;
        ans = (ans * binom(maxf, maxt)) % mod;
    }
    ll maxd = 0;
    for(int i = 0; i < k; i++) maxd += a[n - 1 - i] - a[i];
    cout << maxd << " " << ans << "\n";

    return 0;
}