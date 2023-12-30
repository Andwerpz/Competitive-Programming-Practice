#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2020 - F

//there must exist an optimal line where exactly two points lie on the boundary. 

//we can set one point, and do sweepline to test all the other points, given that one point is locked to the boundary. 

ld pi = acos(-1);
ld epsilon = 1e-10;

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

vec2 mul(vec2 a, ld s) {
    a.x *= s;
    a.y *= s;
    return a;
}

vec2 normalize(vec2 a){
    ld len = length(a);
    vec2 ret;
    ret.x = a.x / len;
    ret.y = a.y / len;
    return ret;
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

int solve(vector<vec2>& p, int ind, ld width) {
    vector<pair<ld, pair<int, int>>> events(0); //angle, {event type, index}
    int ans = 1;
    for(int i = 0; i < p.size(); i++){
        if(i == ind) {
            continue;
        }
        vec2 pt = sub(p[i], p[ind]);
        if(length(pt) <= width + epsilon) {
            ld angle = atan2(pt.y, pt.x);
            //enter event
            events.push_back({angle, {1, i}});
            //exit event
            events.push_back({angle + pi + epsilon, {-1, i}});
            //cout << "ENTER ANGLE : " << angle << " " << i << "\n";
        } 
        else {
            ld angle = atan2(pt.y, pt.x);
            //cout << "ENTER ANGLE : " << angle << " " << i << "\n";
            //enter event
            events.push_back({angle, {1, i}});
            //exit event
            ld h = length(pt);
            ld phi = asin(width / h);
            events.push_back({phi + angle + epsilon, {-1, i}});

            //enter event
            events.push_back({angle + pi - phi, {1, i}});
            //exit event
            events.push_back({angle + pi + epsilon, {-1, i}});
            //cout << "PHI : " << phi << "\n";

            //cout << angle << " " << phi + angle + epsilon << " " << angle + pi - phi << " " << angle + pi + epsilon << "\n";
        }
    }
    for(int i = 0; i < events.size(); i++){
        if(events[i].first < 0) {
            events[i].first += 2.0 * pi;
        }
        while(events[i].first > 2.0 * pi) {
            events[i].first -= 2.0 * pi;
        }
    }
    sort(events.begin(), events.end());
    set<int> in;
    //cout << "TESTING : " << ind << endl;
    for(int i = 0; i < events.size() * 2; i++){
        int ind = events[i % events.size()].second.second;
        bool enter = events[i % events.size()].second.first == 1;
        //cout << events[i].first << " " << ind << " " << enter << "\n";
        if(enter) {
            in.insert(ind);
        }
        else {
            in.erase(ind);
        }
        //cout << in.size() << "\n";
        ans = max(ans, 1 + (int) in.size());
    }
    //cout << "ANSWER : " << ans << "\n";
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ld t;
    cin >> n >> t;
    vector<vec2> p(0);
    for(int i = 0; i < n; i++){
        vec2 v;
        cin >> v.x >> v.y;
        p.push_back(v);
    }
    if(t == 0){
        cout << "2\n";
        return 0;
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans = max(ans, solve(p, i, t));
    }
    cout << ans << "\n";
    
    return 0;
}
