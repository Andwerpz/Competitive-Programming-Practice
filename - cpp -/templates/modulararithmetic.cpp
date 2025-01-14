#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 1e9 + 7;
struct mint {
    ll val; //this should always be in range [0, mod)
    mint(ll _val = 0) {val = _val; if(val < 0) val = mod + (val % mod);}
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
    mint operator /(const mint& other) const {return mint((val / other.val) % mod);}
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

    //returns X such that A = (B * X) % mod
    mint inv_divide(const mint& other) const {
        return *this * other.pow(mod - 2);
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

vector<mint> fac;
void fac_init(int N) {
    fac = vector<mint>(N);
    fac[0] = 1;
    for(int i = 1; i < N; i++){
        fac[i] = fac[i - 1] * i;
    }
}

//n >= k
map<pair<mint, mint>, mint> nckdp;
mint nck(mint n, mint k) {
    if(nckdp.find({n, k}) != nckdp.end()) {
        return nckdp.find({n, k}) -> second;
    }
    mint ans = fac[n].inv_divide(fac[k] * fac[n - k]);
    nckdp.insert({{n, k}, ans});
    return ans;
}

mint stars_bars(ll stars, ll bars, bool allow_zero = false) {
    if(allow_zero) {
        //zero group is group with nothing inside
        return stars_bars(stars + bars + 1, bars, false);
    }
    return nck(stars - 1, bars);
}

//given that we choose n / 2 left brackets and n / 2 right brackets, 
//nck(n, n / 2) is the total amount of bracket sequences, and nck(n, n / 2 + 1) is the amount of bad sequences.
mint nr_rbs(int n){
    if(n == 0){
        return 1;
    }
    if(n % 2){
        return 0;
    }
    return nck(n, n / 2) - nck(n, n / 2 + 1);
}

//true if odd, false if even. 
bool nck_parity(mint n, mint k) {   
    return (k & (n - k)) == 0;
}

//gives the nth catalan number. 
//c_n = \sum_{i = 1}^{n} c_{i - 1} c{n - i}, c_0 = 1
//c_n = number of regular bracket sequences of size 2n (n pairs of brackets)
mint catalan(mint n){
    return nck(2 * n, n) - nck(2 * n, n + 1);
}

//cantor pairing function, uniquely maps a pair of integers back to the set of integers. 
mint cantor(mint a, mint b) {
    return ((a + b) * (a + b + 1) / 2 + b);
}

//sum of elements in arithmetic sequence from start to start + (nr_elem - 1) * inc
mint arith_sum(mint start, mint nr_elem, mint inc) {
    mint ans = start * nr_elem;
    ans += inc * nr_elem * (nr_elem - 1) / 2;
    return ans;
}

//number of labelled forests on n vertices with k connected components
//roots of each component are 1, 2, ..., k
mint cayley(ll n, ll k) {
    return mint(k) * mint(n).pow(n - k - 1);
}

//a derangement is a permutation with no fixed points
//d[n][k] = number of derangements of size n with exactly k cycles
//d[n][k] = (n - 1) (d[n - 2][k - 1] + d[n - 1][k])
vvm d;
void init_d(int N) {
    d = vvm(N, vm(N, 0));
    d[0][0] = 1;
    for(int n = 2; n < d.size(); n++){
        for(int k = 1; k <= n / 2; k++){
            d[n][k] = mint(n - 1) * (d[n - 2][k - 1] + d[n - 1][k]);
        }
    }
}

//computes the number of derangements of size n using PIE
//condition e_i is p[i] = i, or p[i] is a fixed point
mint calc_d(int n) {
    mint ans = 0;
    for(int i = 0; i <= n; i++){
        ans += nck(n, i) * fac[n - i] * (i % 2? -1 : 1);
    }
    return ans;
}

//stirling number of the first kind (unsigned)
//s1[n][k] = number of permutations of length n with exactly k cycles
//s1[n + 1][k] = n * s1[n][k] + s1[n][k - 1]
vvm s1;
void init_s1(int N) {
    s1 = vvm(N + 1, vm(N + 1, 0));
    s1[1][1] = 1;
    for(int n = 2; n <= N; n++){
        for(int k = 1; k <= n; k++){
            if(k != 1) s1[n][k] += s1[n - 1][k - 1];
            s1[n][k] += (n - 1) * s1[n - 1][k];
        }
    }
}