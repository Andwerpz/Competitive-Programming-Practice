#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - starnotatree

//we can use gradient descent to progressively improve our solution. 

//let's create a function f(x, y) that takes in a point, and outputs the amount of cable required given that
//the hub is placed at (x, y). 

//note that the function is just going to be the sum of all distances to (x, y) from each of the computers. 

//now, the tricky part is showing that there are no local minima for our descent to get stuck in. For the sake of 
//intuition, we can look at the 1D analogy to this situation, where we have a bunch of points on the number line, 
//and we take the distance from all of those points. 

//note that the sum of absolute value functions should never have any local minima, and the only flat point
//should occur at the global minimum. 

ld pi = acos(-1);
ld epsilon = 1e-9;

struct vec2 {
    ld x, y;
    vec2() {this->x = 0; this->y = 0;}
    vec2(ld x, ld y) {this->x = x; this->y = y;}
};

vec2 add(vec2 a, vec2 b){
    vec2 ret;
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    return ret;
}

vec2 sub(vec2 a, vec2 b) {
    vec2 ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    return ret;
}

ld cross(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}

ld dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

ld length(vec2 a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

ld lerp(ld t0, ld t1, ld x0, ld x1, ld t) {
    ld slope = (x1 - x0) / (t1 - t0);
    return x0 + slope * (t - t0);
}

vec2 mul(vec2 a, ld s) {
    a.x *= s;
    a.y *= s;
    return a;
}

vec2 normalize(vec2 a){
    ld len = length(a);
    if(len < epsilon) {
        return vec2();
    }
    vec2 ret;
    ret.x = a.x / len;
    ret.y = a.y / len;
    return ret;
}

//project a onto b
vec2 project(vec2 a, vec2 b) {
    b = normalize(b);
    ld proj_mag = dot(a, b);
    return mul(b, proj_mag);
}

vec2 rotateCCW(vec2 a, ld theta) {
    vec2 ret(0, 0);
    ret.x = a.x * cos(theta) - a.y * sin(theta);
    ret.y = a.x * sin(theta) + a.y * cos(theta);
    return ret;
}

//returns the coefficients s and t, where p1 + v1 * s = p2 + v2 * t
vector<ld> lineLineIntersect(vec2 p1, vec2 v1, vec2 p2, vec2 v2) {
    if(cross(v1, v2) == 0){
        return {};
    }
    ld s = cross(sub(p2, p1), v2) / cross(v1, v2);
    ld t = cross(sub(p1, p2), v1) / cross(v2, v1);
    return {s, t};
}

ld tri_area(vec2 t1, vec2 t2, vec2 t3) {
    vec2 v1 = sub(t1, t2);
    vec2 v2 = sub(t2, t3);
    return abs(cross(v1, v2) / 2.0);
}

//returns the distance along the ray from ray_a to the nearest point on the circle. 
ld rayCircleIntersect(vec2 ray_a, vec2 ray_b, vec2 center, ld radius) {
    vec2 ray_dir = normalize(sub(ray_b, ray_a));
    vec2 to_center = sub(center, ray_a);
    vec2 center_proj = add(ray_a, mul(ray_dir, dot(ray_dir, to_center)));
    ld center_proj_len = length(sub(center, center_proj));
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
    ld sector = sector_area(theta, radius);
    ld tri_area = radius * radius * cos(theta) * sin(theta);
    return sector - tri_area;
}

//dist = distance from center
ld chord_area_dist(ld dist, ld radius) {
    ld theta = acos(dist / radius);
    return chord_area(theta, radius);
}

//length of chord
ld chord_area_length(ld length, ld radius) {
    ld theta = asin((length / 2.0) / radius);
    return chord_area(theta, radius);
}

//given a point inside and outside a circle, find the point along the line that intersects the circle.
vec2 find_circle_intersect(vec2 in, vec2 out, vec2 c_center, ld c_radius) {
    //just binary search :D
    ld low = 0;
    ld high = 1;
    ld len = length(sub(in, out));
    vec2 norm = normalize(sub(out, in));
    while(abs(high - low) > epsilon) {
        ld mid = (high + low) / 2.0;
        vec2 mid_pt = add(in, mul(norm, len * mid));
        ld mid_dist = length(sub(mid_pt, c_center));
        if(mid_dist < c_radius) {
            low = mid;
        }
        else {
            high = mid;
        }
    }
    return add(in, mul(norm, len * low));
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
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
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

    return ans;
}

vec2 descend(vec2 guess, ld interval, vector<vec2>& a) {
    vec2 dir;
    for(int i = 0; i < a.size(); i++){
        vec2 n_dir = sub(a[i], guess);
        dir = add(dir, normalize(n_dir));
    }
    return add(guess, mul(dir, interval));
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vec2> a(n);
    vec2 guess;
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
        guess = add(guess, a[i]);
    }
    guess = mul(guess, 1.0 / (ld) n);
    ld interval = 1;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 100000; j++){
            guess = descend(guess, interval, a);
        }
        interval /= 10.0;
    }
    ld ans = 0;
    for(int i = 0; i < n; i++){
        ans += length(sub(guess, a[i]));
    }
    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}
