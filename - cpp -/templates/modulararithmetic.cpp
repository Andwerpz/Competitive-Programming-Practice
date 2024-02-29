#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct mint;
vector<mint> fac;
map<pair<mint, mint>, mint> nckdp;

//modular int
struct mint {
    ll val, mod;
    mint(ll _val = 0, ll _mod = 1e9 + 7) {val = _val; mod = _mod;}
    mint(const mint& other) {val = other.val;}
    bool operator ==(const mint& other) const {return val == other.val;}
    bool operator ==(ll other) const {return val == other;}
    bool operator !=(const mint& other) const {return val != other.val;}
    bool operator !=(ll other) const {return val != other;}
    mint& operator =(const mint& other) {val = other.val; return *this;}
    mint& operator =(ll other) {val = other; return *this;}
    mint operator +(const mint& other) const {ll ret = val + other.val; while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint operator +(ll other) const {ll ret = val + other; while(ret >= mod) {ret -= mod;} return mint(ret);}
    mint& operator +=(const mint& other) {*this = *this + other; return *this;}
    mint& operator +=(ll other) {*this = *this + other; return *this;}
    mint operator -(const mint& other) const {ll ret = val - other.val; while(ret < 0) {ret += mod;} return mint(ret);}
    mint operator -(ll other) const {ll ret = val - other; while(ret < 0) {ret += mod;} return mint(ret);}
    mint& operator -=(const mint& other) {*this = *this - other; return *this;}
    mint& operator -=(ll other) {*this = *this - other; return *this;}
    mint operator *(const mint& other) const {return mint((val * other.val) % mod);}
    mint operator *(ll other) const {return mint((val * other) % mod);}
    mint& operator *=(const mint& other) {*this = *this * other; return *this;}
    mint& operator *=(ll other) {*this = *this * other; return *this;}
    mint operator /(const mint& other) const {return mint((val / other.val) % mod);}
    mint operator /(ll other) const {return mint((val / other) % mod);}
    mint& operator /=(const mint& other) {*this = *this / other; return *this;}
    mint& operator /=(ll other) {*this = *this / other; return *this;}
    mint operator %(const mint& other) const {return mint(val % other.val);}
    mint operator %(ll other) const {return mint(val % other);}
    mint& operator %=(const mint& other) {*this = *this % other; return *this;}
    mint& operator %=(ll other) {*this = *this % other; return *this;}
    
    mint pow(const mint& other) const {
        mint ans(1), p(val);
        ll b = other.val;
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }
    mint pow(ll other) const {
        mint ans(1), p(val);
        ll b = other;
        while(b != 0) {if(b % 2 == 1) {ans *= p;} p *= p; b /= 2;}
        return ans;
    }

    //returns X such that A = (B * X) % mod
    mint inv_divide(const mint& other) const {
        return *this * other.pow(mod - 2);
    }

    friend std::ostream& operator<<(std::ostream& os, const mint& m) {os << m.val; return os;}
    friend std::istream& operator>>(std::istream& is, mint& m) {is >> m.val; return is;}
    operator size_t() const {return val;}
};
bool operator ==(ll a, const mint& b) {return a == b.val;}
bool operator !=(ll a, const mint& b) {return a != b.val;}
mint operator +(ll a, const mint& b) {ll ret = a + b.val; while(ret >= b.mod) {ret -= b.mod;} return mint(ret);}
mint operator -(ll a, const mint& b) {ll ret = a - b.val; while(ret < 0) {ret += b.mod;} return mint(ret);}
mint operator *(ll a, const mint& b) {return mint((a * b.val) % b.mod);}
mint operator /(ll a, const mint& b) {return mint((a / b.val) % b.mod);}
mint operator %(ll a, const mint& b) {return mint(a % b.val);}

mint gcd(mint a, mint b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

void fac_init(int N) {
    fac = vector<mint>(N);
    for(int i = 2; i < N; i++){
        fac[i] = fac[i - 1] * i;
    }
}

//n >= k
mint nck(mint n, mint k) {
    if(nckdp.find({n, k}) != nckdp.end()) {
        return nckdp.find({n, k}) -> second;
    }
    mint ans = fac[n].inv_divide(fac[k] * fac[n - k]);
    nckdp.insert({{n, k}, ans});
    return ans;
}

//true if odd, false if even. 
bool nck_parity(mint n, mint k) {   
    return (n & (n - k)) == 0;
}

mint catalan(mint n){
    return nck(2 * n, n) - nck(2 * n, n + 1);
}

//cantor pairing function, uniquely maps a pair of integers back to the set of integers. 
mint cantor(mint a, mint b) {
    return ((a + b) * (a + b + 1) / 2 + b);
}

mint extended_euclidean(mint a, mint b, mint& x, mint& y) {
    x = 1, y = 0;
    mint x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        mint q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

//modular inverse of a for any mod m. 
//if -1 is returned, then there is no solution. 
mint mod_inv(mint a, mint m) {
    mint x, y;
    mint g = extended_euclidean(a, m, x, y);
    if (g != 1) {
        return -1;
    }
    else {
        x = (x % m + m) % m;
        return x;
    }
}

//only works when all modulo is coprime. 
//if you want to do this with non-coprime modulos, then you need to factor all of the modulos, 
//and resolve the factors independently; converting them back to coprime. 
//it is not guaranteed that there is a solution if the modulos are not coprime. 
mint chinese_remainder_theorem(vector<mint>& modulo, vector<mint>& remainder) {
    if(modulo.size() != remainder.size()) {
        return -1;
    }
    mint M = 1;
    for(int i = 0; i < modulo.size(); i++){
        M *= modulo[i];
    }
    mint solution = 0;
    for(int i = 0; i < modulo.size(); i++){
        mint a_i = remainder[i];
        mint M_i = M / modulo[i];
        mint N_i = mod_inv(M_i, modulo[i]);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}

//sum of elements in arithmetic sequence from start to start + (nr_elem - 1) * inc
mint arith_sum(mint start, mint nr_elem, mint inc) {
    mint ans = start * nr_elem;
    ans += inc * nr_elem * (nr_elem - 1) / 2;
    return ans;
}