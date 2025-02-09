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

//ICPC NAC 2021 - J

//notice that 4 <= n <= 6
//n cannot be odd, so it's either 4 or 6

//n = 4 makes a rectangle, you can place the camera wherever you want so just print the area of the rectangle.

//n = 6 is the interesting case. It makes a rectangle with a little protrusion. Drawing below:
//------------
//|          |
//|  A    B  |
//|          |
//|      ____|
//|  C  |
//|_____|

//in section A, any location works as it can directly see everything. In sections B and C, they mostly work, except
//for the area near the interior corner. 

//solution is too annoying to explain, go read editorial. It's not too bad to derive tho, so try that first. 

ld pi = acos(-1);
ld epsilon = 1e-7;

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

ld lerp(ld t0, ld t1, ld x0, ld x1, ld t) {
    ld slope = (x1 - x0) / (t1 - t0);
    return x0 + slope * (t - t0);
}

vec2 lerp(ld t0, ld t1, vec2 x0, vec2 x1, ld t) {
    return vec2(lerp(t0, t1, x0.x, x1.x, t), lerp(t0, t1, x0.y, x1.y, t));
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

ld tri_area(vec2 t1, vec2 t2, vec2 t3) {
    vec2 v1 = t1 - t2;
    vec2 v2 = t2 - t3;
    return abs(cross(v1, v2) / 2.0);
}

const int VCNT = 5e5;
ld calc_bad(ld a, ld b, ld h, ld w) {
    vec2 prev = {0, 0};
    vec2 lend = {b, b * a / (2 * (h - b))};
    ld interval = lend.length() / VCNT;
    ld ans = 0;
    for(int _ = 1; _ <= VCNT; _++){
        ld y = (h - a) * (ld) _ / (ld) VCNT;
        ld x = 2.0 * (w - b) / (a * (1.0 / y + 1.0 / (2 * (h - a) - y)));
        x = min(x, b);
        vec2 cur = {x, y};
        ans += tri_area(cur, prev, {b, 0});
        prev = cur;
    }
    ans += tri_area(prev, {b, 0}, {b, h - a});
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pii> pt(n);
    for(int i = 0; i < n; i++){
        cin >> pt[i].first >> pt[i].second;
    }
    if(n == 4) {
        int min_x = pt[0].first, min_y = pt[0].second, max_x = pt[0].first, max_y = pt[0].second;
        for(int i = 0; i < 4; i++){
            min_x = min(min_x, pt[i].first);
            min_y = min(min_y, pt[i].second);
            max_x = max(max_x, pt[i].first);
            max_y = max(max_y, pt[i].second);
        }
        cout << (max_x - min_x) * (max_y - min_y) << "\n";
        return 0;
    }
    vector<pii> diff(n);
    for(int i = 0; i < n; i++){
        pii cur = pt[i], next = pt[(i + 1) % n];
        diff[i] = {next.first - cur.first, next.second - cur.second};
    }
    //max x diff and y diff should both be negative
    int mxydiff_ind = 0, mxxdiff_ind = 0; 
    for(int i = 0; i < n; i++){
        if(abs(diff[i].first) > abs(diff[mxxdiff_ind].first)) mxxdiff_ind = i;  
    }
    if(diff[mxxdiff_ind].first > 0) {
        for(int i = 0; i < n; i++){
            diff[i].first *= -1;
        }
        reverse(diff.begin(), diff.end());
    }
    for(int i = 0; i < n; i++){
        if(abs(diff[i].second) > abs(diff[mxydiff_ind].second)) mxydiff_ind = i;
    }
    if(diff[mxydiff_ind].second > 0) {
        for(int i = 0; i < n; i++){
            diff[i].second *= -1;
        }
        reverse(diff.begin(), diff.end());
    }
    for(int i = 0; i < n; i++){
        if(abs(diff[i].second) > abs(diff[mxydiff_ind].second)) mxydiff_ind = i;
    }
    {
        vector<pii> tmp(n);
        for(int i = 0; i < n; i++){
            tmp[i] = diff[(i + mxydiff_ind) % n];
        }
        diff = tmp;
    }
    ld h = -diff[0].second, w = -diff[5].first;
    ld a = diff[2].second, b = diff[3].first;
    ld ans = h * w - a * b;
    ans -= calc_bad(a, b, h, w);
    ans -= calc_bad(b, a, w, h);
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}