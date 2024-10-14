#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

struct Complex;
typedef vector<Complex> vc;
typedef vector<vector<Complex>> vvc;
typedef pair<Complex, Complex> pcc;

struct Complex {
    ld r, i;
    Complex(ld _r = 0, ld _i = 0) {r = _r, i = _i;}
    bool operator ==(const Complex& other) const {return r == other.r && i == other.i;}
    bool operator ==(ld other) const {return r == other && i == 0;}
    bool operator !=(const Complex& other) const {return r != other.r || i != other.i;}
    bool operator !=(ld other) const {return r != other || i != 0;}
    Complex& operator =(const Complex& other) {r = other.r, i = other.i; return *this;}
    Complex& operator =(ld other) {r = other, i = 0; return *this;}
    Complex operator +(const Complex& other) const {return {r + other.r, i + other.i};}
    Complex operator +(ld other) const {return {r + other, i};}
    Complex& operator +=(const Complex& other) {*this = *this + other; return *this;}
    Complex& operator +=(ld other) {*this = *this + other; return *this;}
    Complex operator -(const Complex& other) const {return {r - other.r, i - other.i};}
    Complex operator -(ld other) const {return {r - other, i};}
    Complex& operator -=(const Complex& other) {*this = *this - other; return *this;}
    Complex& operator -=(ld other) {*this = *this - other; return *this;}
    Complex operator *(const Complex& other) const {return {r * other.r - i * other.i, r * other.i + i * other.r};}
    Complex operator *(ld other) const {return {r * other, i * other};}
    Complex& operator *=(const Complex& other) {*this = *this * other; return *this;}
    Complex& operator *=(ld other) {*this = *this * other; return *this;}
    Complex operator /(const Complex& other) const {return *this * other.inv();}
    Complex operator /(ld other) const {return {r / other, i / other};}
    Complex& operator /=(const Complex& other) {*this = *this / other; return *this;}
    Complex& operator /=(ld other) {*this = *this / other; return *this;}

    ld lengthSq() const {return r * r + i * i;}
    ld length() const {return sqrt(lengthSq());}
    Complex conj() const {return {r, -i};}
    Complex inv() const {return conj() / lengthSq();}

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {os << c.r << " " << c.i; return os;}
    friend std::istream& operator>>(std::istream& is, Complex& c) {is >> c.r >> c.i; return is;}
};
bool operator ==(ld a, const Complex& b) {return Complex(a, 0) == b;}
bool operator !=(ld a, const Complex& b) {return Complex(a, 0) != b;}
Complex operator +(ld a, const Complex& b) {return Complex(a, 0) + b;}
Complex operator -(ld a, const Complex& b) {return Complex(a, 0) - b;}
Complex operator *(ld a, const Complex& b) {return Complex(a, 0) * b;}
Complex operator /(ld a, const Complex& b) {return Complex(a, 0) / b;}