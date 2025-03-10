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

//Topcoder - 14199

//can compute stirling numbers of the first kind by just expanding the polynomial identity.

struct mint;
typedef vector<mint> vm;
typedef vector<vector<mint>> vvm;
typedef pair<mint, mint> pmm;

const ll mod = 1e9 + 7;
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

namespace fft {
    const double PI = acos(-1);

    void fft(vector<complex<double>>& a) {
        int n = a.size(), L = 31 - __builtin_clz(n);
        static vector<complex<long double>> R(2, 1);
        static vector<complex<double>> rt(2, 1);  // (^ 10% faster if double)
        for (static int k = 2; k < n; k *= 2) {
            R.resize(n);
            rt.resize(n);
            auto x = polar(1.0L, acos(-1.0L) / k);
            for (int i = k; i < 2 * k; i++) 
                rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
        }
        vector<int> rev(n);
        for (int i = 0; i < n; i++) 
            rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        for (int i = 0; i < n; i++) 
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2) 
            for (int i = 0; i < n; i += 2 * k) 
                for (int j = 0; j < k; j++) {
                    // complex<double> z = rt[j + k] * a[i + j + k]; // (25% faster if hand-rolled)  /// include-line
                    auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];  /// exclude-line
                    complex<double> z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);  /// exclude-line
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
    }

    vector<double> conv(const vector<double>& a, const vector<double>& b) {
        if (a.empty() || b.empty()) return {};
        vector<double> res(a.size() + b.size() - 1);
        int L = 32 - __builtin_clz(res.size()), n = 1 << L;
        vector<complex<double>> in(n), out(n);
        copy(a.begin(), a.end(), in.begin());
        for (int i = 0; i < b.size(); i++) 
            in[i].imag(b[i]);
        fft(in);
        for (complex<double>& x : in) 
            x *= x;
        for (int i = 0; i < n; i++) 
            out[i] = in[-i & (n - 1)] - conj(in[i]);
        fft(out);
        for (int i = 0; i < res.size(); i++) 
            res[i] = imag(out[i]) / (4 * n);
        return res;
    }

    template<int M> vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
        if (a.empty() || b.empty()) return {};
        vector<ll> res(a.size() + b.size() - 1);
        int B = 32 - __builtin_clz(res.size()), n = 1 << B, cut = int(sqrt(M));
        vector<complex<double>> L(n), R(n), outs(n), outl(n);
        for (int i = 0; i < a.size(); i++) 
            L[i] = complex<double>((int)a[i] / cut, (int)a[i] % cut);
        for (int i = 0; i < b.size(); i++) 
            R[i] = complex<double>((int)b[i] / cut, (int)b[i] % cut);
        fft(L), fft(R);
        for (int i = 0; i < n; i++) {
            int j = -i & (n - 1);
            outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
            outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
        }
        fft(outl), fft(outs);
        for (int i = 0; i < res.size(); i++) {
            ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
            ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
            res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
        }
        return res;
    }
}

//polynomial with mint coefficients
//p(x) = a[0] x^0 + a[1] x^1 + ...
struct poly {
    vector<mint> a; 
    poly() {}
    poly(vector<mint> _a) {a = vector<mint>(_a); normalize();}
    poly(initializer_list<mint> _a) : a(_a) { normalize(); }
    poly(const poly& other) {a = other.a;}

    // get rid of leading zeroes
    void normalize() { 
        while(!a.empty() && a.back() == mint(0)) {
            a.pop_back();
        }
    }

    int deg() const {
        return (int) a.size() - 1;
    }

    mint& coeff(int idx) {
        return a[idx];
    }

    poly& operator +=(const poly &t) {
        a.resize(max(a.size(), t.a.size()));
        for(int i = 0; i < t.a.size(); i++) a[i] += t.a[i];
        normalize();
        return *this;
    }
    poly operator +(const poly &t) const {return poly(*this) += t;}

    poly& operator -=(const poly &t) {
        a.resize(max(a.size(), t.a.size()));
        for(int i = 0; i < t.a.size(); i++) a[i] -= t.a[i];
        normalize();
        return *this;
    }
    poly operator -(const poly &t) const {return poly(*this) -= t;}

    //TODO figure out how NTT works
    //idea: instead of directly computing p(x) * q(x), split p and q into
    //p(x) = p1(x) + p2(x) * C
    //q(x) = q1(x) + q2(x) * C
    //for some C ~ sqrt(mod). Then, we can do normal floating point FFT, and it should be
    //precise enough to contain the results. 
    poly& operator *=(const poly &t) {
        vector<ll> p(deg() + 1), q(t.deg() + 1);
        for(int i = 0; i <= deg(); i++) p[i] = a[i].val;
        for(int i = 0; i <= t.deg(); i++) q[i] = t.a[i].val;
        vector<ll> res = fft::convMod<mod>(p, q);
        a.resize(res.size());
        for(int i = 0; i < res.size(); i++) a[i].val = res[i];
        normalize();
        return *this;
    }
    poly operator *(const poly &t) const {return poly(*this) *= t;}

    //a^k *= k!
    poly invborel() const { 
        auto res = *this;
        for(int i = 0; i <= deg(); i++) {
            res.coeff(i) *= fac[i];
        }
        return res;
    }
    
    //a^k /= k!
    poly borel() const { 
        auto res = *this;
        for(int i = 0; i <= deg(); i++) {
            res.coeff(i) *= invfac[i];
        }
        return res;
    }

    // computes x^n A(x^{-1})
    poly reverse(size_t n) const { 
        auto res = a;
        res.resize(max(n, res.size()));
        return vector<mint>(res.rbegin(), res.rbegin() + n);
    }
    
    poly reverse() const {
        return reverse(deg() + 1);
    }

    //P(sx)
    poly mulx(mint s){
        mint cur = 1;
        poly res(*this);
        for(int i = 0; i <= deg(); i++) {
            res.coeff(i) *= cur;
            cur *= s;
        }
        return res;
    }

    // multiply by x^k
    poly mul_xk(size_t k) const { 
        vector<mint> res = a;
        res.insert(begin(res), k, 0);
        return poly(res);
    }
    
    // drop first k coefficients
    poly div_xk(size_t k) const { 
        return vector<mint>(begin(a) + min(k, a.size()), end(a));
    }

    //P(x + s)
    //essentially, take the taylor expansion at x = -s and then plug in x + s
    poly shift(mint s) {
        return (expx(deg() + 1).mulx(s).reverse() * invborel()).div_xk(deg()).borel();
    }

    mint eval(mint x) {
        mint ans = 0, pow = 1;
        for(int i = 0; i < a.size(); i++) {
            ans += a[i] * pow;
            pow *= x;
        }
        return ans;
    }

    // P(x) = 1 + x + ... + x^{n-1} 
    static poly ones(int n) { 
        return vector<mint>(n, 1);
    }

    // P(x) = e^x (mod x^n)
    static poly expx(int n) { 
        return ones(n).borel();
    }

    static poly xk(int k) {
        return poly({1}).mul_xk(k);
    }

    friend std::ostream& operator<<(std::ostream& os, const poly& p) {
        for(int i = p.deg(); i >= 0; i--){
            cout << p.a[i];
            if(i != 0) cout << "x^" << i << " + ";
        }
        return os;
    }
};

//unsigned stirling numbers of the first kind, compute all of them for fixed n
//essentially expanding the polynomial x(x + 1)(x + 2)...(x + n - 1) 
poly stirling(int n) {
    if(n == 0) {
        return poly({1});
    }
    auto res = stirling(n / 2);
    res *= res.shift(n / 2);
    if(n & 1) {
        res *= poly({n - 1, 1});
    }
    return res;
}

class CyclesNumber {
public:
    vector<int> getExpectation(vector<int> a, vector<int> b) {
        fac_init(1e6);
        int n = a.size();
        vi ans(n);
        for(int i = 0; i < n; i++){
            poly s = stirling(a[i]);
            mint cans = 0;
            for(int j = 1; j <= a[i]; j++){
                cans += mint(j).pow(b[i]) * s.coeff(j);
            }
            ans[i] = cans.val;
        }
        return ans;
    }
};

int main() {
    int n0; cin >> n0;
    vector<int> arg0(n0);
    for (int i=0;i<n0;++i) { cin >> arg0[i]; }
    int n1; cin >> n1;
    vector<int> arg1(n1);
    for (int i=0;i<n1;++i) { cin >> arg1[i]; }
    auto c = CyclesNumber();
    vector<int> ret = c.getExpectation(arg0, arg1);
    for (auto& item : ret) { cout << item << "\n"; }
}