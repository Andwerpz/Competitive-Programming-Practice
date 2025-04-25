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

//3rd Universal Cup Stage 31 : Wroclaw - H

//this is identical to asking whether or not it's possible to create a valid venn diagram using n circles

//Observe that it's impossible if n >= 4. First, check if every circle is pairwise intersecting. Also check
//if any circle contains another one. If the first is not true, or the second is true, then you've found 
//the missing hue. 

//Otherwise, every circle is pairwise intersecting. Just take the first 4 circles and do some more extensive 
//checks. 

//note that every region has an intersection point on the edge. We can list out all intersection points
//between circles and find all the created hues that way. 

ld pi = acos(-1);
ld epsilon = 1e-11;
ld inf = 1e18;

struct vec2 {
    ld x, y;
    vec2(ld _x = 0, ld _y = 0) {x = _x; y = _y;}
    vec2(pii c) {x = c.first, y = c.second;}
    vec2(const vec2& other) {x = other.x; y = other.y;}
    vec2(const vec2& a, const vec2& b) {x = b.x - a.x; y = b.y - a.y;}  //creates A to B
    bool operator==(const vec2& other) {return x == other.x && y == other.y;}
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

//returns the distance along the ray from ray_a to the nearest point on the circle. 
ld ray_circleIntersect(vec2 ray_a, vec2 ray_b, vec2 center, ld radius) {
    vec2 ray_dir = (ray_b - ray_a).get_normal();
    vec2 to_center = center - ray_a;
    vec2 center_proj = ray_a + ray_dir * dot(ray_dir, to_center);
    ld center_proj_len = (center - center_proj).length();
    //radius^2 = center_proj_len^2 + int_depth^2
    //int_depth = sqrt(radius^2 - center_proj_len^2)
    ld int_depth = sqrt(radius * radius - center_proj_len * center_proj_len);
    return dot(ray_dir, to_center) - int_depth;
}

//sector area of circle 
ld sector_area(ld theta, ld radius) {
    return radius * radius * pi * ((theta) / (2.0 * pi));
}

ld chord_area(ld theta, ld radius) {
    return (radius * radius / 2.0) * (theta - sin(theta));
}

//dist = distance from center
ld chord_area_dist(ld dist, ld radius) {
    ld theta = acos(dist / radius);
    return chord_area(theta * 2, radius);
}

//length of chord
ld chord_area_length(ld length, ld radius) {
    ld theta = asin((length / 2.0) / radius);
    return chord_area(theta * 2, radius);
}

//3 points can uniquely define a circle, just have to find the intersection between the perpendicular
//bisectors between two pairs of points. 
//be careful if the three points are colinear. 
vec2 threept_circle(vec2 a, vec2 b, vec2 c){
    vec2 ab = b - a;
    vec2 ac = c - a;
    vec2 abp = {ab.y, -ab.x};
    vec2 acp = {ac.y, -ac.x};
    return line_lineIntersect(a + ab / 2, abp, a + ac / 2, acp);
}

//if no intersections found, returns {{inf, inf}, {inf, inf}}
//if one circle is contained by other, returns {smaller center, inf}
//otherwise, returns the two intersections
pair<vec2, vec2> circle_circleIntersect(vec2 c1, ld r1, vec2 c2, ld r2) {
    //see if intersection even exists
    if(c1.dist(c2) > r1 + r2) return {{inf, inf}, {inf, inf}};
    //see if c1 contains c2
    if(r1 - c1.dist(c2) > r2) return {c2, {inf, inf}};
    //see if c2 contains c1
    if(r2 - c2.dist(c1) > r1) return {c1, {inf, inf}};
    //proper intersection. Suppose that c1 is at origin, c2 is on x axis
    c2 -= c1;
    ld c2ang = c2.polar_angle();
    ld c2x = c2.length();
    //calc intersection x coordinate. 
    ld intx = (r1 * r1 - r2 * r2 + c2x * c2x) / (2.0 * c2x);
    ld inty = sqrt(r1 * r1 - intx * intx);
    vec2 p1 = {intx, inty}, p2 = {intx, -inty};
    p1 = p1.rotate_CCW(c2ang), p2 = p2.rotate_CCW(c2ang);
    p1 += c1, p2 += c1;
    return {p1, p2};
}

//containing or intersecting
bool cc_areIntersecting(pii c1, int r1, pii c2, int r2) {
    int d2 = (c1.first - c2.first) * (c1.first - c2.first) + (c1.second - c2.second) * (c1.second - c2.second);
    return d2 < (r1 + r2) * (r1 + r2);
}

//does c1 contain c2 (with some leeway for c1)
bool cc_areContaining(vec2 c1, ld r1, vec2 c2, ld r2) {
    return r1 - c1.dist(c2) + epsilon > r2;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // circle_circleIntersect({0, 0}, 1, {1.999, 0}, 1);
    // circle_circleIntersect({0, 0}, 1, {1, 0}, 1);
    // circle_circleIntersect({0, 0}, 1, {1, 0}, 1.9);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pii> c(n);
        vi r(n);
        set<int> s;
        for(int i = 0; i < n; i++) cin >> c[i].first >> c[i].second >> r[i];
        if(n == 1) {
            cout << "YES\n";
            continue;
        }
        //make sure all circles are pairwise intersecting
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                if(!cc_areIntersecting(c[i], r[i], c[j], r[j])) {
                    cout << "NO\n";
                    for(int k = 0; k < n; k++) cout << (k == i || k == j? "1 " : "0 ");
                    cout << "\n";
                    goto end;
                }
                if(cc_areContaining(c[i], r[i], c[j], r[j])) {
                    cout << "NO\n";
                    for(int k = 0; k < n; k++) cout << (k == j? "1 " : "0 ");
                    cout << "\n";
                    goto end;
                }
            }
        }
        //make sure first 4 are good
        for(int i = 0; i < min(n, 4); i++){
            for(int j = i + 1; j < min(n, 4); j++){
                // cout << "IJ : " << i << " " << j << "\n";
                pair<vec2, vec2> ret = circle_circleIntersect(c[i], r[i], c[j], r[j]);
                int i1 = 0, i2 = 0;
                for(int k = 0; k < min(n, 4); k++){
                    if(k == i || k == j) continue;
                    if(ret.first.dist(c[k]) < r[k] + epsilon) i1 += (1 << k);
                    if(ret.second.dist(c[k]) < r[k] + epsilon) i2 += (1 << k);
                }
                s.insert(i1), s.insert(i2);
                s.insert(i1 + (1 << i)), s.insert(i2 + (1 << i));
                s.insert(i1 + (1 << j)), s.insert(i2 + (1 << j));
                s.insert(i1 + (1 << i) + (1 << j)), s.insert(i2 + (1 << i) + (1 << j));
            }   
        }
        if(s.size() != (1 << min(n, 4))) {
            // cout << "MISSING SOMETHING FROM " << (1 << min(n, 4)) << "\n";
            // for(int x : s) cout << x << " ";
            // cout << "\n";
            cout << "NO\n";
            int miss = -1;
            for(int i = 0; i < (1 << min(n, 4)); i++){
                if(!s.count(i)) miss = i;
            }
            for(int i = 0; i < min(n, 4); i++){
                cout << (miss & (1 << i)? "1 " : "0 ");
            }
            for(int i = 4; i < n; i++) cout << "0 ";
            cout << "\n";
            goto end;
        }
        cout << "YES\n";
        end: {}
    }
    
    return 0;
}