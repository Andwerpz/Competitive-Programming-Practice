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

//Baekjoon - 15421

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

//checks if the area of the triangle is the same as the three triangle areas formed by drawing lines from pt to the vertices. 
//i don't think triangle winding order matters
bool point_inside_triangle(vec2 pt, vec2 t0, vec2 t1, vec2 t2) {
    ld a1 = abs(cross(t1 - t0, t2 - t0));
    ld a2 = abs(cross(t0 - pt, t1 - pt)) + abs(cross(t1 - pt, t2 - pt)) + abs(cross(t2 - pt, t0 - pt));
    return abs(a1 - a2) < epsilon;
}

//runs in O(n * log(n)) time. 
//has to do O(n * log(n)) preprocessing, but after preprocessing can answer queries online in O(log(n))
vector<bool> points_inside_convex_hull(vector<vec2> pts, vector<vec2>& hull) {
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
    // cout << "PIVOT : " << pivot << "\n";
    // for(int i = 0; i < h_pts.size(); i++) cout << h_pts[i] << " ";
    // cout << "\n";
    //for each point we want to check, compute it's polar angle, then binary search for the sector that should contain it
    for(int i = 0; i < pts.size(); i++){
        vec2 pt = pts[i];
        ld pt_ang = (pt - pivot).polar_angle();
        // cout << "PT ANG : " << pt_ang << "\n";
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
        // cout << "TRI IND : " << tri_ind << " " << h_pts[tri_ind] << "\n";
        // cout << point_inside_triangle(pt, pivot, h_pts[tri_ind], h_pts[tri_ind + 1]) << "\n";
        ans[i] = point_inside_triangle(pt, pivot, h_pts[tri_ind], h_pts[tri_ind + 1]);
    }
    return ans;
}

//p1 + v1 * s = p2 + v2 * t
vec2 line_lineIntersect(vec2 p1, vec2 v1, vec2 p2, vec2 v2) {
    if(cross(v1, v2) == 0){
        return {inf, inf};
    }
    ld s = cross(p2 - p1, v2) / cross(v1, v2);
    ld t = cross(p1 - p2, v1) / cross(v2, v1);
    return p1 + v1 * s;
}

vector<vector<vec2>> cut_hull(vector<vec2> hull, vec2 ca, vec2 cb){
    // cout << "CUT HULL : " << ca << " " << cb << endl;
    // for(int i = 0; i < hull.size(); i++) cout << hull[i] << " ";
    // cout << "\n";
    //find cuts if they exist. There should be exactly 2
    vi cuts(0);
    vector<vec2> cutpt(0);
    for(int i = 0; i < hull.size(); i++){
        vec2 a = hull[i], b = hull[(i + 1) % hull.size()];
        b = b - a;
        b.normalize();
        vec2 isect = line_lineIntersect(a, b, ca, cb);
        if(isect == vec2(inf, inf)) continue;   //parallel
        // cout << "DOT : " << dot(b, isect - a) << "\n";
        if(dot(b, isect - a) < epsilon || dot(b, isect - a) > (hull[i] - hull[(i + 1) % hull.size()]).length() - epsilon) continue;    //intersection point is outside of line segment
        cuts.push_back(i);
        cutpt.push_back(isect);
        if(cuts.size() == 2) break;
        // cout << "FOUND CUT : " << i << " " << isect << endl;
    }
    // assert(cuts.size() == 0 || cuts.size() == 2);
    // cout << "CUTS FOUND : " << cuts.size() << endl;
    if(cuts.size() != 2) return {hull};
    vector<vec2> h1(0), h2(0);
    h1.push_back(cutpt[0]);
    for(int i = cuts[0] + 1; i <= cuts[1]; i++){
        h1.push_back(hull[i]);
    }
    h1.push_back(cutpt[1]);
    h2.push_back(cutpt[1]);
    for(int i = cuts[1] + 1; i <= cuts[0] + hull.size(); i++){
        h2.push_back(hull[i % hull.size()]);
    }
    h2.push_back(cutpt[0]);
    return {h1, h2};
}

//returns true if the union between the hull and circle is non-empty
bool hull_circle_intersect(vector<vec2>& hull, vec2 center, ld radius) {
    //check if circle contains any hull vertices
    for(int i = 0; i < hull.size(); i++){
        if((hull[i] - center).length() < radius + epsilon) {
            return true;
        }
    }
    //check if circle center is inside hull
    if(points_inside_convex_hull({center}, hull)[0]) return true;
    //otherwise, center has to be outside of hull, and none of hull points are inside of circle.
    //then, the only case where the union is still non-zero is if circle intersects an edge of the hull
    for(int i = 0; i < hull.size(); i++){
        vec2 a = hull[i], b = hull[(i + 1) % hull.size()];
        vec2 ab = b - a;
        vec2 proj = ab.project(center - a) + a;
        //see if proj is on the line segment
        ab.normalize();
        if(dot(ab, (proj - a)) < 0 || dot(ab, (proj - a)) > (b - a).length()) continue;
        //see if proj is close enough
        if((center - proj).length() < radius + epsilon) return true;
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, r;
    cin >> n >> m >> r;
    vector<vector<vec2>> a;
    vector<vec2> b(n);
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    a.push_back({{r, r}, {-r, r}, {-r, -r}, {r, -r}});
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<long double> dis(0.0, 2 * pi);
    ld randrot = dis(gen);
    for(int i = 0; i < a[0].size(); i++){
        a[0][i] = a[0][i].rotate_CCW(randrot);
    }
    for(int i = 0; i < m; i++){
        vec2 ca, cb;
        {
            ld _a, _b, _c;
            cin >> _a >> _b >> _c;
            if(_b == 0) {
                //ax + c = 0
                //x = -c / a
                ca = {-_c / _a, 0};
                cb = {-_c / _a, 1};
            }
            else {
                //ax + by + c = 0
                //y = -(ax + c) / b
                ca = {0, -_c / _b};
                cb = {1, -(_a + _c) / _b};
            }
            cb = cb - ca;
            cb.normalize();
        }
        //cut hulls
        vector<vector<vec2>> na(0);
        for(int j = 0; j < a.size(); j++){
            vector<vector<vec2>> cut = cut_hull(a[j], ca, cb);
            for(auto x : cut) if(hull_circle_intersect(x, {0, 0}, r)) na.push_back(x);
        }
        a = na;
    }
    // cout << "HULLS : " << "\n";
    // for(int i = 0; i < a.size(); i++){
    //     cout << "[";
    //     for(int j = 0; j < a[i].size(); j++){
    //         cout << a[i][j] << ", ";
    //     }
    //     cout << "],\n";
    // }
    bool is_valid = a.size() == n;
    if(a.size() == n){
        for(int i = 0; i < a.size(); i++){
            vb res = points_inside_convex_hull(b, a[i]);
            int cnt = 0;
            for(int j = 0; j < res.size(); j++) cnt += res[j]? 1 : 0;
            // cout << "CNT : " << cnt << "\n";
            // for(int j = 0; j < res.size(); j++) cout << res[j] << " ";
            // cout << "\n";
            if(cnt != 1) is_valid = false;
        }
    }
    cout << (is_valid? "yes" : "no") << "\n";
    
    return 0;
}