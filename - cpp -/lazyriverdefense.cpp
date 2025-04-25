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

//Calgary Collegiate Programming Contest 2025 - C

//didn't submit this yet, not on open.kattis D:

//for each person, just determine when tom enters and exits their radius. This can be done by 
//tracing tom's path and doing some circle intersection stuff. 

ld pi = acos(-1);
ld epsilon = 1e-9;
ld inf = 1e9;

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

//returns the first point in which the ray intersects the sphere
//0 if no intersect, 1 if entering, 2 if exiting
int ray_circle_intersect(vec2 origin, vec2 dir, vec2 center, ld r, vec2& out, ld& _dist) {
    dir.normalize();
    vec2 off = origin - center;
    ld a = dot(dir, dir);
    ld b = 2.0 * dot(dir, off);
    ld c = dot(off, off) - r * r;
    ld d = b * b - 4.0 * a * c;
    if(d >= 0) {
        ld dist = (-b - sqrt(d)) / (2.0 * a);
        if(dist > epsilon) {
            //entry 
            out = origin + dir * dist;
            _dist = dist;
            return 1;
        }
        else {
            dist = (-b + sqrt(d)) / (2.0 * a);
            if(dist > epsilon) {
                //exit
                out = origin + dir * dist;
                _dist = dist;
                return 2;
            }
        }
    }
    return 0;   //no intersect
}   

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<vec2> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    int m, b;
    cin >> m >> b;
    vector<vec2> p(m);
    vd r(m), iv(m);
    for(int i = 0; i < m; i++) cin >> p[i] >> r[i] >> iv[i];
    ld plen = 0;
    for(int i = 0; i < n; i++) plen += (a[i] - a[(i + 1) % n]).length();
    for(int i = 0; i < m; i++) iv[i] -= epsilon;    //some extra padding
    bool safe = true;
    //see if some people are already in
    vb in(m, false);
    for(int i = 0; i < m; i++){
        if((p[i] - a[i]).length() <= r[i]) in[i] = true, safe = false;
    }
    //for each person, compute the entrance and exit times of the path
    vector<pair<ld, pair<int, int>>> ev(0); //{time, {which person, enter or exit}}
    for(int i = 0; i < m; i++){
        ld tptr = 0;
        for(int j = 0; j < n; j++){
            vec2 origin = a[j], dir = (a[(j + 1) % n] - a[j]);
            ld amt = dir.length();
            dir.normalize();
            while(true) {   //slowly advance origin
                vec2 isect;
                ld d;
                int ty = ray_circle_intersect(origin, dir, p[i], r[i], isect, d);
                if(ty == 0) break;  //no intersection
                if(d > amt) break;  //intersection is too far along ray
                amt -= d;
                tptr += d;
                origin = isect + dir * epsilon;
                ev.push_back({tptr, {i, ty}});
            }
            tptr += amt;
        }
    }
    if(ev.size() != 0) safe = false;
    cout << fixed << setprecision(10);
    // cout << "EV SIZE : " << ev.size() << endl;
    // for(int i = 0; i < ev.size(); i++) cout << ev[i].first << " " << ev[i].second.first << " " << ev[i].second.second << endl;
    if(safe) {
        cout << "safe\n";
        return 0;
    }
    // cout << "PLEN : " << plen << "\n";
    ev.push_back({0, {-1, -1}});
    sort(ev.begin(), ev.end());
    //for each person, we're going to keep track of what's the next time they can throw a baloon. 
    //we'll also keep track of who is currently in range
    vd nt(m, -epsilon);
    ld ans = -1;
    int rcnt = 0;
    for(int i = 0; b != 0; i++){
        if(i == ev.size()) {
            i = 0;
            rcnt ++;
        }
        ld t = ev[i].first + rcnt * plen;
        int ind = ev[i].second.first;
        int ty = ev[i].second.second;
        //see if someone can throw a baloon before t. If so, just let them throw it
        int min_ti = -1;
        for(int j = 0; j < m; j++){
            if(in[j] && nt[j] < t && (min_ti == -1 || nt[j] < nt[min_ti])) {
                min_ti = j;
            }
        }
        if(min_ti != -1) {
            // cout << "THROW BALOON : " << nt[min_ti] << " " << min_ti << "\n";
            b --;
            ans = nt[min_ti];
            nt[min_ti] += iv[min_ti];
            continue;   
        }
        //otherwise, process the event
        if(ty == 1) {
            //entering throw radius. 
            in[ind] = true;
            nt[ind] = max(nt[ind], t);
        }
        else if(ty == 2){
            //exiting throw radius
            in[ind] = false;
        }
        else {
            //dummy event
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}