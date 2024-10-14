#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

struct Quaternion;
typedef vector<Quaternion> vq;
typedef vector<vector<Quaternion>> vvq;
typedef pair<Quaternion, Quaternion> pqq;

struct Quaternion {
    ld r, i, j, k;
    Quaternion(ld _r = 0, ld _i = 0, ld _j = 0, ld _k = 0) {r = _r, i = _i, j = _j, k = _k;}
    bool operator ==(const Quaternion& other) const {return r == other.r && i == other.i && j == other.j && k == other.k;}
    bool operator !=(const Quaternion& other) const {return r != other.r || i != other.i || j != other.j || k != other.k;}
    Quaternion& operator =(const Quaternion& other) {r = other.r, i = other.i, j = other.j, k = other.k; return *this;}
    Quaternion& operator =(ld other) {r = other, i = 0, j = 0, k = 0; return *this;}
    Quaternion operator +(const Quaternion& other) const {return {r + other.r, i + other.i, j + other.j, k + other.k};}
    Quaternion operator +(ld other) const {return {r + other, i, j, k};}
    Quaternion& operator +=(const Quaternion& other) {*this = *this + other; return *this;}
    Quaternion& operator +=(ld other) {*this = *this + other; return *this;}
    Quaternion operator -(const Quaternion& other) const {return {r - other.r, i - other.i, j - other.j, k - other.k};}
    Quaternion operator -(ld other) const {return {r - other, i, j, k};}
    Quaternion& operator -=(const Quaternion& other) {*this = *this - other; return *this;}
    Quaternion& operator -=(ld other) {*this = *this - other; return *this;}
    Quaternion operator *(const Quaternion& other) const {
        ld nr = r * other.r - i * other.i - j * other.j - k * other.k;
        ld ni = i * other.r + r * other.i - k * other.j + j * other.k;
        ld nj = j * other.r + k * other.i + r * other.j - i * other.k;
        ld nk = k * other.r - j * other.i + i * other.j + r * other.k;
        return {nr, ni, nj, nk};
    }
    Quaternion operator *(ld other) const {return {r * other, i * other, j * other, k * other};}
    Quaternion& operator *=(const Quaternion& other) {*this = *this * other; return *this;}
    Quaternion& operator *=(ld other) {*this = *this * other; return *this;}
    Quaternion operator /(const Quaternion& other) const {return *this * other.inv();}
    Quaternion operator /(ld other) const {return {r / other, i / other, j / other, k / other};}
    Quaternion& operator /=(const Quaternion& other) {*this = *this / other; return *this;}
    Quaternion& operator /=(ld other) {*this = *this / other; return *this;}

    ld lengthSq() const {return r * r + i * i + j * j + k * k;}
    ld length() const {return sqrt(lengthSq());}
    Quaternion conj() const {return {r, -i, -j, -k};}
    Quaternion inv() const {return conj() / lengthSq();}

    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q) {os << q.r << " " << q.i << " " << q.j << " " << q.k; return os;}
    friend std::istream& operator>>(std::istream& is, Quaternion& q) {is >> q.r >> q.i >> q.j >> q.k; return is;}
};
bool operator ==(ld a, const Quaternion& b) {return Quaternion(a) == b;}
bool operator !=(ld a, const Quaternion& b) {return Quaternion(a) != b;}
Quaternion operator +(ld a, const Quaternion& b) {return Quaternion(a) + b;}
Quaternion operator -(ld a, const Quaternion& b) {return Quaternion(a) - b;}
Quaternion operator *(ld a, const Quaternion& b) {return Quaternion(a) * b;}
Quaternion operator /(ld a, const Quaternion& b) {return Quaternion(a) / b;}