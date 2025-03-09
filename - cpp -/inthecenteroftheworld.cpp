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

//Baekjoon - 2389

//minimum enclosing circle template check

ld pi = acos(-1);
ld epsilon = 1e-9;
ld inf = 1e9;

struct vec2 {
    ld x, y;
    vec2(ld _x = 0, ld _y = 0) {x = _x; y = _y;}
    vec2(const vec2& other) {x = other.x; y = other.y;}
    vec2(const vec2& a, const vec2& b) {x = b.x - a.x; y = b.y - a.y;}  //creates A to B
    vec2& operator=(const vec2& other) {x = other.x; y = other.y; return *this;}
    vec2 operator-() const {return vec2(-x, -y);}
    vec2 operator+(const vec2& other) const {return vec2(x + other.x, y + other.y);}
    vec2& operator+=(const vec2& other) {*this = *this + other; return *this;}
    vec2 operator-(const vec2& other) const {return vec2(x - other.x, y - other.y);}
    vec2& operator-=(const vec2& other) {*this = *this - other; return *this;}
    vec2 operator*(ld other) const {return vec2(x * other, y * other);}
    vec2& operator*=(ld other) {*this = *this * other; return *this;}
    vec2 operator/(ld other) const {return vec2(x / other, y / other);}
    vec2& operator/=(ld other) {*this = *this / other; return *this;}

    ld lengthSq() const {return x * x + y * y;}
    ld length() const {return sqrt(lengthSq());}
    vec2 get_normal() const {return *this / length();}
    void normalize() {*this /= length();}   //actually normalizes this vector
    ld distSq(const vec2& other) const {return vec2(*this, other).lengthSq();}
    ld dist(const vec2& other) const {return sqrt(distSq(other));}

    ld dot(const vec2& other) const {return x * other.x + y * other.y;}
    ld cross(const vec2& other) const {return x * other.y - y * other.x;}
    ld angle_to(const vec2& other) const {return acos(dot(other) / length() / other.length());}
    vec2 rotate_CCW(ld theta) const {return vec2(x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta));}

    //angle from x axis in range (-pi, pi)
    ld polar_angle() {return atan2(y, x);}  

    //projection of other onto this
    vec2 project(const vec2& other) {return *this * (other.dot(*this) / dot(*this));}

    friend std::ostream& operator<<(std::ostream& os, const vec2& v) {os << "[" << v.x << ", " << v.y << "]"; return os;}
    friend std::istream& operator>>(std::istream& is, vec2& v) {is >> v.x >> v.y; return is;}
};
vec2 operator*(ld a, const vec2& b) {return vec2(a * b.x, a * b.y);}

ld cross(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}

ld dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

//p1 + v1 * s = p2 + v2 * t
vec2 line_lineIntersect(vec2 p1, vec2 v1, vec2 p2, vec2 v2) {
    if(cross(v1, v2) == 0){
        return {};
    }
    ld s = cross(p2 - p1, v2) / cross(v1, v2);
    ld t = cross(p1 - p2, v1) / cross(v2, v1);
    return p1 + v1 * s;
}

//3 points can uniquely define a circle, just have to find the intersection between the perpendicular
//bisectors between two pairs of points. 
//be careful if the three points are colinear. 
//returns the center, the distance from the center should be the same to each a, b, c.
vec2 threept_circle(vec2 a, vec2 b, vec2 c){
    vec2 ab = b - a;
    vec2 ac = c - a;
    vec2 abp = {ab.y, -ab.x};
    vec2 acp = {ac.y, -ac.x};
    return line_lineIntersect(a + ab / 2, abp, a + ac / 2, acp);
}

//returns {center, radius} where radius is minimized and the circle encloses all points in a
//runs in expected linear time. 
pair<vec2, ld> enclosing_circle(vector<vec2> a){
    //randomly permute a
    random_shuffle(a.begin(), a.end());
    //run welzl's algorithm
    function<pair<vec2, ld>(vector<vec2>)> welzl = [&](vector<vec2> r) -> pair<vec2, ld> {
        if(a.size() == 0 || r.size() == 3) {
            if(r.size() == 0) return {{0, 0}, 0};
            else if(r.size() == 1) return {r[0], epsilon};
            else if(r.size() == 2) return {(r[0] + r[1]) / 2.0, (r[0] - r[1]).length() / 2.0};
            else {
                vec2 center = threept_circle(r[0], r[1], r[2]);
                return {center, (r[0] - center).length()};
            }
        }
        vec2 cur = a.back();
        a.pop_back();
        pair<vec2, ld> ret = welzl(r);
        a.push_back(cur);
        if(ret.second != 0 && (cur - ret.first).length() - epsilon <= ret.second) return ret;
        r.push_back(cur);
        a.pop_back();
        ret = welzl(r);
        a.push_back(cur);
        return ret;
    };
    return welzl({});
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<vec2> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    pair<vec2, ld> ret = enclosing_circle(a);
    cout << fixed << setprecision(10) << ret.first.x << " " << ret.first.y << " " << ret.second << "\n";
    
    return 0;
}