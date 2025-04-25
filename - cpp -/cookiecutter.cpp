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

//2022 ICPC NAC - B

//first, write an efficient square vs line chop area thing. It's very important to be efficient as the TL is kinda tight
//(at least for my templates)

//intuition is that the line has to pass through 2 points. Actually, this intuition is incorrect, there are cases where the 
//line only passes through one point. 

//the idea on the one point case is that you can always rotate the line in some direction until either it intersects a second
//point or you reach a local minimum in terms of area. If it intersects a second point, then we've got that covered. The only
//issue is when it reaches a local minimum, we need to also account for this line. 

//for some point, we can find the polar angle of the line that passes through and minimizes the area of the triangle formed
//by the line and x and y axes as as -atan(y / x). (do some calculus) 

//Then, for each point, we can fix that point as the line passing through it and do polar sweepline. 

const ld pi = acos(-1);
const ld epsilon = 1e-9;
const ld inf = 1e9;

struct vec2 {
    ld x, y;
    vec2(ld _x = 0, ld _y = 0) {x = _x; y = _y;}
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
        return {-1, -1};
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

//given a point inside and outside a circle, find the point along the line that intersects the circle.
vec2 find_circle_intersect(vec2 in, vec2 out, vec2 c_center, ld c_radius) {
    //just binary search :D
    //i think we can reduce this to some sort of quadratic. 
    ld low = 0;
    ld high = 1;
    ld len = (in - out).length();
    vec2 norm = (out - in).get_normal();
    while(abs(high - low) > epsilon) {
        ld mid = (high + low) / 2.0;
        vec2 mid_pt = in + norm * (len * mid);
        ld mid_dist = (mid_pt - c_center).length();
        if(mid_dist < c_radius) {
            low = mid;
        }
        else {
            high = mid;
        }
    }
    return in + norm * (len * low);
}

//returns the area of the polygon. 
//winding direction doesn't matter
//polygon can be self intersecting i think...
ld polygon_area(vector<vec2>& poly, int n) {
    ld area = 0;
    for(int i = 0; i < n; i++){
        area += cross(poly[i], poly[(i + 1) % n]);
    }
    return abs(area / 2.0);
}

//returns negative if pt is to the right, positive if to the left
ld pt_line_side(vec2 linept, vec2 linedir, vec2 pt) {
    return cross(linedir, pt - linept);
}

//to find area of cut square, you can find all the points of the piece left by the cut by adding
// - the intersection of the cut line with the square
// - all the vertices of the square on the same side as the line
//probably the harder part is finding the intersection between the cut line and square
ld sz, sze;
vector<vec2> sq, poly(8), sqdir;
ld right_area(vec2 linept, vec2 linedir) {    
    int polyptr = 0;
    for(int i = 0; i < 4; i++){
        if(pt_line_side(linept, linedir, sq[i]) < 0) poly[polyptr ++] = sq[i];
        vec2 isect = line_lineIntersect(linept, linedir, sq[i], sqdir[i]);
        if(isect.x >= -epsilon && isect.x <= sze && isect.y >= -epsilon && isect.y <= sze) poly[polyptr ++] = isect;
    }
    assert(polyptr >= 3);
    // vec2 center = {sz / 2, sz / 2};
    // sort(poly.begin(), poly.end(), [&center](vec2 a, vec2 b) -> bool {
    //     return (a - center).polar_angle() < (b - center).polar_angle();
    // });
    // cout << "CUT : " << linept << " " << linedir << "\n";
    // for(int i = 0; i < poly.size(); i++) cout << poly[i] << " ";
    // cout << "\n";
    return polygon_area(poly, polyptr);
}

vector<vec2> calc_poly(vec2 linept, vec2 linedir) {
    vector<vec2> ans;
    for(int i = 0; i < 4; i++){
        if(pt_line_side(linept, linedir, sq[i]) < 0) ans.push_back(sq[i]);
        vec2 isect = line_lineIntersect(linept, linedir, sq[i], (sq[(i + 1) % 4] - sq[i]));
        cout << "ISECT : " << isect << "\n";
        if(isect.x >= -epsilon && isect.x <= sz + epsilon && isect.y >= -epsilon && isect.y <= sz + epsilon) ans.push_back(isect);
    }
    return ans;
}

ld calc_angle(vec2 pt) {
    ld ang = 2 * pi - atan(pt.y / pt.x);
    // ang -= pi;
    return ang;
}

//fix intersecting one point, rotate line around point
vector<pair<ld, int>> ev;   //{polar angle, add / remove}
vector<bool> v;
ld solve(int sind, vector<vec2>& a) {
    int evptr = 0;
    for(int i = 0; i < a.size(); i++){
        if(i == sind) continue;
        //at what polar angles should we add and remove this point?
        vec2 diff = a[i] - a[sind];
        diff.normalize();
        ld ang = diff.polar_angle();
        ev[evptr ++] = {ang - epsilon, (i + 1)};
        ev[evptr ++] = {ang + pi, -(i + 1)};
    }
    //add special angles
    // cout << "CALC ANGLE : " << calc_angle(a[sind]) << "\n";
    // cout << "ATAN : " << atan(a[sind].y / a[sind].x) << "\n";
    ev[evptr ++] = {calc_angle(a[sind]), 0};    //bottom left
    {   //bottom right
        ld ang = calc_angle({sz - a[sind].x, a[sind].y});
        ang = 2 * pi - ang;
        ev[evptr ++] = {ang, 0};
    }
    {   //top left
        ld ang = calc_angle({a[sind].x, sz - a[sind].y});
        ang = 2 * pi - ang;
        ang += pi;
        ev[evptr ++] = {ang, 0};
    }
    {   //top right
        ld ang = calc_angle({sz - a[sind].x, sz - a[sind].y});
        ang -= pi;
        ev[evptr ++] = {ang, 0};
    }
    for(int i = 0; i < ev.size(); i++){
        if(ev[i].first > 2 * pi) ev[i].first -= 2 * pi;
        if(ev[i].first < 0) ev[i].first += 2 * pi;
    }
    sort(ev.begin(), ev.end(), [](pair<ld, int>& a, pair<ld, int>& b) -> bool {
        if(a.first == b.first) return a.second > b.second;
        return a.first < b.first;
    });
    int incnt = 1;
    vector<bool> v(a.size(), false);
    for(int i = 0; i < a.size(); i++) v[i] = false;
    for(int i = 0; i < ev.size(); i++){
        if(ev[i].second > 0) {
            //adding pt
            if(!v[ev[i].second - 1]) incnt ++;
            v[ev[i].second - 1] = true;
        }
        else if(ev[i].second < 0) {
            //removing pt
            if(v[-ev[i].second - 1]) incnt --;
            v[-ev[i].second - 1] = false;
        }
    }
    ld ans = 0;
    for(int i = 0; i < ev.size(); i++){
        pair<ld, int> cev = ev[i];
        if(cev.second > 0) {
            //adding pt
            if(!v[cev.second - 1]) incnt ++;
            v[cev.second - 1] = true;
            //consider ans
            vec2 linedir = vec2(1, 0).rotate_CCW(cev.first);
            ld area = right_area(a[sind], linedir);
            ld cans = (ld) (incnt) / (ld) a.size() - area / (sz * sz);
            ans = max(ans, cans);

            // if(cans > 0.5) {
            //     cout << "ANG : " << cev.first << "\n";
            //     cout << "DIR : " << linedir << "\n";
            //     cout << "AREA : " << area << "\n";
            //     vector<vec2> cut = calc_poly(a[sind], linedir);
            //     for(vec2 x : cut) cout << x << " ";
            //     cout << "\n";
            // }
        }
        else if(cev.second < 0) {
            //removing pt
            if(v[-cev.second - 1]) incnt --;
            v[-cev.second - 1] = false;
        }
        else {
            //custom angle
            vec2 linedir = vec2(1, 0).rotate_CCW(cev.first);
            ld area = right_area(a[sind], linedir);
            ld cans = (ld) (incnt) / (ld) a.size() - area / (sz * sz);
            ans = max(ans, cans);

            // cout << "ANG : " << cev.first << "\n";
            // cout << "DIR : " << linedir << "\n";
            // cout << "AREA : " << area << "\n";
            // vector<vec2> cut = calc_poly(a[sind], linedir);
            // for(vec2 x : cut) cout << x << " ";
            // cout << "\n";
        }
    }
    // if(ans > 0.5) cout << "SIND : " << sind << " " << ans << "\n";
    return ans;
}

ld randf() {
    return (rand() % (1 << 16)) / (ld) (1 << 16);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    srand(time(0));
    int n, m;
    cin >> n >> m;
    sz = n, sze = n + epsilon;
    ev = vector<pair<ld, int>>(m * 2 - 2 + 4);
    v = vector<bool>(m, false);
    sq = {{0, 0}, {sz, 0}, {sz, sz}, {0, sz}};
    sqdir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<vec2> a(m);
    for(int i = 0; i < m; i++) cin >> a[i];
    // for(int i = 0; i < m; i++) a[i].x += randf() * epsilon, a[i].y += randf() * epsilon;
    ld ans = 0;
    for(int i = 0; i < m; i++) ans = max(ans, solve(i, a));
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}