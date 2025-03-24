#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
typedef pair<int, int> pii;

ld pi = acos(-1);
ld epsilon = 1e-9;
ld inf = 1e9;

struct vec3 {
    ld x, y, z;
    vec3() {x = 0, y = 0, z = 0;}
    vec3(ld _x, ld _y, ld _z) {x = _x, y = _y, z = _z;}
    vec3(const vec3& other) {x = other.x, y = other.y, z = other.z;}
    vec3(const vec3& a, const vec3& b) {x = b.x - a.x, y = b.y - a.y, z = b.z - a.z;}
    vec3& operator+=(const vec3& other) {x += other.x, y += other.y, z += other.z; return *this;}
    vec3& operator-=(const vec3& other) {x -= other.x, y -= other.y, z -= other.z; return *this;}
    vec3 operator+(const vec3& other) {return vec3(*this) += other;}
    vec3 operator-(const vec3& other) {return vec3(*this) -= other;}

    vec3& operator*=(const ld s) {x *= s, y *= s, z *= s; return *this;}
    vec3 operator*(const ld s) {return vec3(*this) *= s;}

    ld lengthSq() {return x * x + y * y + z * z;}
    ld length() {return sqrt(lengthSq());}
    ld dist(const vec3& other) {return vec3(*this, other).length();}
};