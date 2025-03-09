#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
typedef pair<int, int> pii;

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

//returns the area of the polygon. 
//winding direction doesn't matter
//polygon can be self intersecting i think...
ld polygon_area(vector<vec2>& poly) {
    ld area = 0;
    for(int i = 0; i < poly.size(); i++){
        vec2 v0 = poly[i];
        vec2 v1 = poly[(i + 1) % poly.size()];
        area += cross(v0, v1);
    }
    return abs(area / 2.0);
}

//assuming that the density of the polygon is uniform, the centroid is the center of mass.
//winding direction matters...
vec2 polygon_centroid(vector<vec2>& poly) {
    vec2 c = vec2();
    for(int i = 0; i < poly.size(); i++){
        vec2 v0 = poly[i];
        vec2 v1 = poly[(i + 1) % poly.size()];
        ld p = cross(v0, v1);
        c.x += (v0.x + v1.x) * p;
        c.y += (v0.y + v1.y) * p;
    }
    ld area = polygon_area(poly);
    c.x /= (6.0 * area);
    c.y /= (6.0 * area);
    return c;
}

//returns convex hull in CCW order
//make sure that there aren't any duplicate points. This algorithm really doesn't like that (tends to infinite loop)
//if you want better convex hull construction, use ll instead of ld.
vector<vec2> convex_hull(vector<vec2> a, bool include_collinear = false) {
    function<int(vec2, vec2, vec2)> orientation = [](vec2 a, vec2 b, vec2 c) -> int {
        ld v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
        if (v < 0) return -1; // clockwise
        if (v > 0) return +1; // counter-clockwise
        return 0;
    };
    function<bool(vec2, vec2, vec2)> collinear = [&orientation](vec2 a, vec2 b, vec2 c) -> bool {
        return orientation(a, b, c) == 0;
    };
    function<bool(vec2, vec2, vec2, bool)> cw = [&orientation](vec2 a, vec2 b, vec2 c, bool include_collinear) -> bool {
        int o = orientation(a, b, c);
        return o < 0 || (include_collinear && o == 0);
    };
    vec2 p0 = *min_element(a.begin(), a.end(), [](vec2 a, vec2 b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0, &orientation](const vec2& a, const vec2& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y) < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }
    vector<vec2> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }
    //make sure there are no duplicate vertices
    vector<vec2> ans(0);
    for(int i = 0; i < st.size(); i++){
        vec2 v0 = st[i];
        vec2 v1 = st[(i + 1) % st.size()];
        if(v0.x == v1.x && v0.y == v1.y) {
            continue;
        }
        ans.push_back(st[i]);
    }
    //reverse to make winding CCW
    reverse(ans.begin(), ans.end());
    return ans;
}

//checks if the area of the triangle is the same as the three triangle areas formed by drawing lines from pt to the vertices. 
//i don't think triangle winding order matters
bool point_inside_triangle(vec2 pt, vec2 t0, vec2 t1, vec2 t2) {
    ld a1 = abs(cross(t1 - t0, t2 - t0));
    ld a2 = abs(cross(t0 - pt, t1 - pt)) + abs(cross(t1 - pt, t2 - pt)) + abs(cross(t2 - pt, t0 - pt));
    return abs(a1 - a2) < epsilon;
}

//runs in O(n * log(n)) time. 
//has to do O(n * log(n)) preprocessing, but after preprocessing can answer queries online in O(log(n))
vector<bool> points_inside_convex_hull(vector<vec2>& pts, vector<vec2>& hull) {
    vector<bool> ans(pts.size(), false);
    //edge case
    if(hull.size() <= 2){
        return ans;
    }
    //find point of hull that has minimum x coordinate
    //if multiple elements have same x, then minimum y. 
    int pivot_ind = 0;
    for(int i = 1; i < hull.size(); i++){
        if(hull[i].x < hull[pivot_ind].x || (hull[i].x == hull[pivot_ind].x && hull[i].y < hull[pivot_ind].y)) {
            pivot_ind = i;
        }
    }
    //sort all the remaining elements according to polar angle to the pivot
    vector<vec2> h_pts(0);
    vec2 pivot = hull[pivot_ind];
    for(int i = 0; i < hull.size(); i++){
        if(i != pivot_ind) {
            h_pts.push_back(hull[i]);
        }
    }
    sort(h_pts.begin(), h_pts.end(), [&pivot](vec2& a, vec2& b) -> bool {
        return (a - pivot).polar_angle() < (b - pivot).polar_angle();
    });
    //for each point we want to check, compute it's polar angle, then binary search for the sector that should contain it
    for(int i = 0; i < pts.size(); i++){
        vec2 pt = pts[i];
        ld pt_ang = (pt - pivot).polar_angle();
        int low = 0;
        int high = h_pts.size() - 2;
        int tri_ind = low;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if((h_pts[mid] - pivot).polar_angle() <= pt_ang) {
                tri_ind = max(tri_ind, mid);
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        ans[i] = point_inside_triangle(pt, pivot, h_pts[tri_ind], h_pts[tri_ind + 1]);
    }
    return ans;
}

//finds all pairs of points that are 'directly across' from each other on a convex hull
//don't include collinear points in the hull
//useful for finding the furthest pair of points in a set of points
//https://codeforces.com/blog/entry/133763
vector<pii> antipodal_pairs(vector<vec2> &p) {
    int n = p.size();
    //degenerate hull
    if(n == 1) return {{0, 0}};
    if(n == 2) return {{0, 1}};

    int p1 = 0, p2 = 0; // two "pointers"
    vector<pii> result;

    // parallel edges should't be visited twice
    vector<bool> vis(n, false);

    function<int(int)> nx = [&n](int i) -> int {return (i + 1) % n;};
    function<int(int)> pv = [&n](int i) -> int {return (i - 1 + n) % n;};
    function<int(ll)> sign = [](ll x) -> int {return x == 0? 0 : (x < 0? -1 : 1);};

    for (;p1<n;p1++) {
        // the edge that we are going to consider in this iteration
        // the datatype is Point, but it acts as a vector
        vec2 base = p[nx(p1)] - p[p1];

        // the last condition makes sure that the cross products don't have the same sign
        while (p2 == p1 || p2 == nx(p1) || sign(cross(base, p[nx(p2)] - p[p2])) == sign(cross(base, p[p2] - p[pv(p2)]))) {
            p2 = nx(p2);
        }

        if (vis[p1]) continue;
        vis[p1] = true;

        result.push_back({p1, p2});
        result.push_back({nx(p1), p2});
        
        // if both edges from p1 and p2 are parallel to each other
        if (cross(base, p[nx(p2)] - p[p2]) == 0) {
            result.push_back({p1, nx(p2)});
            result.push_back({nx(p1), nx(p2)});
            vis[p2] = true;
        }
    }

    return result;
}

struct Halfplane { 
    // 'p' is a passing point of the line and 'pq' is the direction vector of the line.
    vec2 p, pq; 
    // angle is the polar angle of 'pq'
    long double angle;

    Halfplane() {}
    Halfplane(const vec2& a, const vec2& b) : p(a), pq(b - a) {
        angle = atan2l(pq.y, pq.x);    
    }

    // Check if point 'r' is outside this half-plane. 
    // Every half-plane allows the region to the LEFT of its line.
    bool out(const vec2& r) { 
        return cross(pq, r - p) < -epsilon; 
    }

    // Comparator for sorting. 
    bool operator < (const Halfplane& e) const { 
        return angle < e.angle;
    } 

    // Intersection point of the lines of two half-planes. It is assumed they're never parallel.
    friend vec2 inter(const Halfplane& s, const Halfplane& t) {
        long double alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
        return s.p + (s.pq * alpha);
    }
};

//given some halfplanes, return the convex polygon that represents the intersection of all the halfplanes, 
//or an empty list if there is none
//https://cp-algorithms.com/geometry/halfplane-intersection.html
vector<vec2> hp_intersect(vector<Halfplane>& H) { 
    vec2 box[4] = {  // Bounding box in CCW order
        vec2(inf, inf), 
        vec2(-inf, inf), 
        vec2(-inf, -inf), 
        vec2(inf, -inf) 
    };

    for(int i = 0; i<4; i++) { // Add bounding box half-planes.
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }

    // Sort by angle and start algorithm
    sort(H.begin(), H.end());
    deque<Halfplane> dq;
    int len = 0;
    for(int i = 0; i < int(H.size()); i++) {

        // Remove from the back of the deque while last half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
            dq.pop_back();
            --len;
        }

        // Remove from the front of the deque while first half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }

        // Special case check: Parallel half-planes
        if (len > 0 && fabsl(cross(H[i].pq, dq[len-1].pq)) < epsilon) {
            // Opposite parallel half-planes that ended up checked against each other.
            if (dot(H[i].pq, dq[len-1].pq) < 0.0)
                return vector<vec2>();

            // Same direction half-plane: keep only the leftmost half-plane.
            if (H[i].out(dq[len-1].p)) {
                dq.pop_back();
                --len;
            }
            else continue;
        }

        // Add new half-plane
        dq.push_back(H[i]);
        ++len;
    }

    // Final cleanup: Check half-planes at the front against the back and vice-versa
    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
        dq.pop_back();
        --len;
    }

    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
        dq.pop_front();
        --len;
    }

    // Report empty intersection if necessary
    if (len < 3) return vector<vec2>();

    // Reconstruct the convex polygon from the remaining half-planes.
    vector<vec2> ret(len);
    for(int i = 0; i+1 < len; i++) {
        ret[i] = inter(dq[i], dq[i+1]);
    }
    ret.back() = inter(dq[len-1], dq[0]);
    return ret;
}

//returns {center, radius} where radius is minimized and the circle encloses all points in a
//runs in expected linear time using welzl's algorithm
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