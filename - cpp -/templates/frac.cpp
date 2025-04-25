#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//prolly should also implement some bigint to go along with this

struct frac {
    ll num, denom;
    frac(ll _num = 0, ll _denom = 1) {num = _num, denom = _denom; reduce();}
    frac(const frac& other) {num = other.num, denom = other.denom;}
    void reduce() {ll g = gcd(num, denom); if(g != 0) {num /= g, denom /= g;}}
    frac& operator =(const frac& other) {num = other.num, denom = other.denom; return *this;}
    frac& operator +=(const frac& other) {
        ll lcm = abs(denom * other.denom) / gcd(denom, other.denom);
        num = num * (lcm / denom) + other.num * (lcm / other.denom);
        denom = lcm;
        reduce();
        return *this;
    }
    frac& operator -=(const frac& other) {*this += frac(-other.num, other.denom); return *this;}
    frac& operator *=(const frac& other) {num *= other.num, denom *= other.denom; reduce(); return *this;}
    frac& operator /=(const frac& other) {num *= other.denom, denom *= other.num; reduce(); return *this;}
    
    frac operator +(const frac& other) {return frac(*this) += other;}
    frac operator -(const frac& other) {return frac(*this) -= other;}
    frac operator *(const frac& other) {return frac(*this) *= other;}
    frac operator /(const frac& other) {return frac(*this) /= other;}

    friend std::ostream& operator<<(std::ostream& os, const frac& m) {os << m.num << "/" << m.denom; return os;}
};
frac operator +(ll a, const frac& b) {return frac(a) + b;}
frac operator -(ll a, const frac& b) {return frac(a) - b;}
frac operator *(ll a, const frac& b) {return frac(a) * b;}
frac operator /(ll a, const frac& b) {return frac(a) / b;}