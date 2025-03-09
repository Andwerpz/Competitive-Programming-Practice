#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

#include "modulararithmetic.cpp";
#include "fft.cpp";

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