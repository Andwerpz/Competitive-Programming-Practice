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

//Codeforces - 1726E

//guessforces + OEISforces. 

//first, wrote brute force checker. Checking up to n = 9, noticed that the only cycle lengths were 1, 2, 4, and their distribution 
//throughout the permutation seemed arbitrary, that is the number of ways to assign length 1, 2, cycles is invariant under the way
//we fix where length 4 cycles are. Assumed this to be true.

//Suppose that we first fix the number and locations of all the length 4 cycles. Then, we can arbitrarily place the length 2 cycles
//anywhere. So if we have n elements remaining, we need to find the number of ways to assign length 2 cycles. 

//My best way to compute this was O(n^2), so I looked on OEIS and found A000085, and it gave a(n) = a(n - 1) + A013989(n - 2). 
//The recurrence for A013989 was also nice, so now I could compute it in linear time. 

//From here, it's just a little bit of counting to assign each amount of 4 groups. 

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
    mint pow(ll b) const {
        mint ans(1), p(val);
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }

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

vi gen_inv(vi p){
    vi inv(p.size());
    for(int i = 0; i < p.size(); i++) inv[p[i]] = i;
    return inv;
}

//given a bunch of stars, how many ways are there to partition the stars using bars. 
mint stars_bars(ll stars, ll bars, bool allow_zero = false) {
    if(allow_zero) {
        //zero group is group with nothing inside
        return stars_bars(stars + bars + 1, bars, false);
    }
    return nck(stars - 1, bars);
}

void solve_slow(int n) {
    int ans = 0;
    vi p(n);
    for(int i = 0; i < n; i++) p[i] = i;
    do {
        vi inv = gen_inv(p);
        bool is_valid = true;
        for(int i = 0; i < n; i++) if(abs(inv[i] - p[i]) > 1) is_valid = false;
        int diffcnt = 0;
        for(int i = 0; i < n; i++) if(inv[i] != p[i]) diffcnt ++;
        if(is_valid) {
            ans ++;
            if(diffcnt) {
                // cout << "CNT : " << diffcnt << "\n";
                if(diffcnt == 4) {
                    for(int i = 0; i < n; i++) cout << p[i] << " ";
                    cout << "\n";
                    for(int i = 0; i < n; i++) cout << inv[i] << " ";
                    cout << "\n";
                    cout << "\n";
                }
            }
        }
    }
    while(next_permutation(p.begin(), p.end()));
    cout << "ANS SLOW : " << ans << "\n";
}

void solve_slowish(int n) {
    //precompute how many ways there are to match pairs
    vm lut(n + 1, 0);
    for(int i = 0; i < lut.size(); i++) {
        mint mult = 1;
        for(int j = 0; j <= i / 2; j++) {
            if(j != 0) mult *= nck(i - (j - 1) * 2, 2);
            // lut[i] += mult * invfac[j];
            lut[i] += fac[i] * invfac[2].pow(j) * invfac[i - 2 * j] * invfac[j];
            // cout << "SELECT " << j << " FROM " << i << " " << fac[i] * invfac[2].pow(j) * invfac[i - 2 * j] << "\n";
        }
    }
    //iterate over how many ways there are to assign 4-groups
    mint ans = 0;
    for(int i = 0; i <= n / 4; i++) {
        mint mult = stars_bars(i * 2, n - i * 4, true) * fac[i * 2] * invfac[2].pow(i);
        ans += mult * invfac[i] * mint(2).pow(i) * lut[n - i * 4];
        cout << "WAYS : " << i << " " << mult * invfac[i] * mint(2).pow(i) * lut[n - i * 4] << "\n";
    }
    cout << ans << "\n";
}

void solve_fast(int n) {
    //precompute how many ways there are to match pairs
    vm a(n + 1);
    a[0] = 1, a[1] = 2;
    for(int i = 2; i <= n; i++) a[i] = (i + 1) * (a[i - 1] / i + a[i - 2]);
    vm lut(n + 1);
    lut[0] = 1, lut[1] = 1;
    for(int i = 2; i <= n; i++) lut[i] = lut[i - 1] + a[i - 2];
    //iterate over how many ways there are to assign 4-groups
    mint ans = 0;
    for(int i = 0; i <= n / 4; i++) {
        mint mult = stars_bars(i * 2, n - i * 4, true) * fac[i * 2] * invfac[2].pow(i);
        ans += mult * invfac[i] * mint(2).pow(i) * lut[n - i * 4];
    }
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    fac_init(1e6);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        solve_fast(n);
    }
    
    return 0;
}