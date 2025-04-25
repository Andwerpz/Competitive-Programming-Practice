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

//3rd Universal Cup, Stage 13 Sendai - K

//let's find some formula for the answer in terms of N, M, and then see if we can simplify it later. 
//i'll just find the formula for the sum of mex over all sequences, can just divide by number of sequences to
//find the expected value. 

//The sum of all mex over all sequences is given by 0 * (nr mex = 0) + 1 * (nr mex = 1) + ... + M * (nr mex = M). 
//this is equivalent to (nr mex >= 1) + (nr mex >= 2) + ... + (nr mex >= M)
//how to find the number of sequences such that mex >= x? We can use PIE. For some sequence to have mex >= x, 
//it has to have the values 0 to x - 1. So a sequence can be bad in x ways. The number of sequences that don't have 
//some values A_1, A_2, ..., A_n is just (M - n)^N. So putting this in PIE, the number of sequences with mex >= x is
//\sum_{i = 0}^{x} (-1)^i \binom{x}{i} (M - i)^N

//then, we can just sum x from 1 to M to find the answer, so 
//f(N, M) = \sum_{x = 1}^{M} \sum_{i = 0}^{x} (-1)^i \binom{x}{i} (M - i)^N

//this is way too slow to compute, so let's try to simplify it some more. We can rearrange the summations, include
//x = 0 in the summation, and apply the hockey stick identity to get
//f(N, M) = (\sum_{i = 0}^{M} (-1)^i (M - i)^N \binom{M + 1}{i + 1}) - M^N

//from here, we can use the stirling number of the second kind identity:
//s2[n][k] = \frac{1}{k!} \sum_{i = 0}^{k} (-1)^{k - i} \binom{k}{i} i^n
//we can get \sum_{i = 0}^{M} (-1)^i (M - i)^N \binom{M + 1}{i + 1} into the form
//(M + 1)^N - \sum_{k = 0}^{M + 1} (-1)^k k^N \binom{M + 1}{k}, and then apply the identity so
//f(N, M) = (M + 1)^N - (M + 1)! s2[N][M + 1] - M^N

//since N, M, are relatively small, we can just compute all 8000^2 stirling numbers using the recurrence relation. 
//then, answering queries is O(1), which is enough to not TLE. 

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 998244353;
struct mint {
    ll val; //this should always be in range [0, mod)
    mint(ll _val = 0) {val = _val; if(val < 0) val = mod + (val % mod); val %= mod;}
    mint(const mint& other) {val = other.val;}
    bool operator ==(const mint& other) const {return val == other.val;}
    bool operator ==(ll other) const {return val == other;}
    bool operator !=(const mint& other) const {return val != other.val;}
    bool operator !=(ll other) const {return val != other;}
    bool operator >(const mint& other) const {return val > other.val;}
    bool operator >(ll other) const {return val > other;}
    bool operator <(const mint& other) const {return val < other.val;}
    bool operator <(ll other) const {return val < other;}
    mint& operator =(const mint& other) {val = other.val; return *this;}
    mint& operator =(ll other) {val = other; return *this;}
    mint operator +(const mint& other) const {ll ret = val + other.val; while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint operator +(ll other) const {return *this + mint(other);}
    mint& operator +=(const mint& other) {*this = *this + other; return *this;}
    mint& operator +=(ll other) {*this = *this + other; return *this;}
    mint operator -(const mint& other) const {ll ret = val - other.val; while(ret < 0) {ret += mod;} return mint(ret);}
    mint operator -(ll other) const {return *this - mint(other);}
    mint& operator -=(const mint& other) {*this = *this - other; return *this;}
    mint& operator -=(ll other) {*this = *this - other; return *this;}
    mint operator *(const mint& other) const {return mint((val * other.val) % mod);}
    mint operator *(ll other) const {return *this * mint(other);}
    mint& operator *=(const mint& other) {*this = *this * other; return *this;}
    mint& operator *=(ll other) {*this = *this * other; return *this;}
    mint operator /(const mint& other) const {return *this * other.pow(mod - 2);}
    mint operator /(ll other) const {return *this / mint(other);}
    mint& operator /=(const mint& other) {*this = *this / other; return *this;}
    mint& operator /=(ll other) {*this = *this / other; return *this;}
    mint operator %(const mint& other) const {return mint(val % other.val);}
    mint operator %(ll other) const {return *this % mint(other);}
    mint& operator %=(const mint& other) {*this = *this % other; return *this;}
    mint& operator %=(ll other) {*this = *this % other; return *this;}

    //don't forget about fermat's little theorem, 
    //a^(m-1) % m = 1. This means that a^(p % m) % m != a^(p) % m, rather a^(p % (m-1)) % m = a^(p) % m. 
    mint pow(const mint& other) const {
        mint ans(1), p(val);
        ll b = other.val;
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }
    mint pow(ll other) const {return this->pow(mint(other));}

    friend std::ostream& operator<<(std::ostream& os, const mint& m) {os << m.val; return os;}
    friend std::istream& operator>>(std::istream& is, mint& m) {is >> m.val; return is;}
    operator size_t() const {return val;}
};
bool operator ==(ll a, const mint& b) {return mint(a) == b;}
bool operator !=(ll a, const mint& b) {return mint(a) != b;}
bool operator >(ll a, const mint& b) {return mint(a) > b;}
bool operator <(ll a, const mint& b) {return mint(a) < b;}
mint operator +(ll a, const mint& b) {return mint(a) + b;}
mint operator -(ll a, const mint& b) {return mint(a) - b;}
mint operator *(ll a, const mint& b) {return mint(a) * b;}
mint operator /(ll a, const mint& b) {return mint(a) / b;}
mint operator %(ll a, const mint& b) {return mint(a) % b;}

mint gcd(mint a, mint b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

vm fac, invfac;
void fac_init(int N) {
    fac = vm(N + 1), invfac = vm(N + 1);
    fac[0] = 1;
    for(int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
    invfac[N] = mint(1) / fac[N];
    for(int i = N; i > 0; i--) invfac[i - 1] = invfac[i] * i;
}

//n >= k
mint nck(mint n, mint k) {
    return fac[n] * invfac[k] * invfac[n - k];
}

//stirling number of the second kind (unsigned)
//s2[n][k] = number of ways to partition a set of n labelled objects into k nonempty unlabelled bins
//s2[n][k] = \frac{1}{k!} \sum_{i = 0}^{k} (-1)^{k - i} \binom{k}{i} i^n
vvm s2;
void init_s2(int N) {
    s2 = vvm(N + 1, vm(N + 1, 0));
    s2[0][0] = 1;
    for(int n = 1; n <= N; n++){
        for(int k = 1; k <= n; k++){
            s2[n][k] = k * s2[n - 1][k] + s2[n - 1][k - 1];
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(1e5);
    init_s2(8001);
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        // mint ans = 0;
        // for(int x = 1; x <= m; x++){
        //     mint ccnt = 0;
        //     for(int i = 0; i <= x; i++){
        //         ccnt += mint(-1).pow(i) * nck(x, i) * mint(m - i).pow(n);
        //     }
        //     // cout << "CCNT : " << x << " " << ccnt << "\n";
        //     ans += ccnt;
        // }
        // mint ans = 0;
        // for(int i = 0; i <= m; i++) {
        //     ans += mint(-1).pow(i) * mint(m - i).pow(n) * nck(m + 1, i + 1);
        // }
        // mint ans = 0;
        // for(int k = 0; k <= m + 1; k++){
        //     ans += mint(-1).pow(k) * mint(k).pow(n) * nck(m + 1, k);
        // }
        mint ans = s2[n][m + 1];
        ans *= fac[m + 1];
        ans *= -1;
        ans += mint(m + 1).pow(n);
        ans -= mint(m).pow(n);
        ans /= mint(m).pow(n);
        cout << ans << "\n";
    }
    
    return 0;
}