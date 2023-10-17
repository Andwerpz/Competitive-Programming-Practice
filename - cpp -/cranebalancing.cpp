#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2014 C

struct vec2 {
    ld x, y;
    vec2() {this->x = 0; this->y = 0;}
    vec2(ld x, ld y) {this->x = x; this->y = y;}
};

vector<vec2> a;

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

//returns the coefficients s and t, where p1 + v1 * s = p2 + v2 * t
vector<ld> lineLinellersect(vec2 p1, vec2 v1, vec2 p2, vec2 v2) {
    if(cross(v1, v2) == 0){
        return {};
    }
    ld s = cross(sub(p2, p1), v2) / cross(v1, v2);
    ld t = cross(sub(p1, p2), v1) / cross(v2, v1);
    return {s, t};
}

ld epsilon = 1e-9;

bool calc_llersect(vec2 a1, vec2 a2, vec2 b1, vec2 b2) {
    vector<ld> llersect = lineLinellersect(a1, sub(a2, a1), b1, sub(b2, b1));
    if(llersect.size() == 0){
        return false;
    }
    ld s = llersect[0];
    ld t = llersect[1];
    if(-epsilon <= s && s <= 1 + epsilon && -epsilon <= t && t <= 1 + epsilon) {
        //cout << "IS llERSECTING" << endl;
        return true;
    }
    return false;
}

bool isCCW(vector<vec2>& a){
    ld sum = 0;
    for(ll i = 0; i < a.size(); i++){
        vec2 t1 = a[(i + 0) % a.size()];
        vec2 t2 = a[(i + 1) % a.size()];
        vec2 t3 = a[(i + 2) % a.size()];
        vec2 v1 = sub(t2, t1);
        vec2 v2 = sub(t3, t2);
        v1 = normalize(v1);
        v2 = normalize(v2);
        sum += asin(cross(v1, v2));
        //cout << asin(cross(v1, v2)) << "\n";
    }
    //cout << sum << endl;
    return sum > 0;
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

ld calc_torque(vector<vec2>& poly, ld pivot) {

    ld mass = polygon_area(poly);
    vec2 center_mass = polygon_centroid(poly);

    //cout << "CENTER  MASS : " << center_mass.x << " " << center_mass.y << "\n";
    if(center_mass.y < 0){
        center_mass.x = abs(center_mass.x);
    }

    return (pivot - center_mass.x) * mass;

    // vec2 ab = sub(tri[0], tri[1]);
    // vec2 ac = sub(tri[0], tri[2]);
    // ld area = abs(cross(ab, ac)) / 2;
    // vec2 centroid = add(tri[0], add(tri[1], tri[2]));
    // centroid = mul(centroid, 1.0 / 3.0);
    // vec2 to_pivot = sub(pivot, centroid);
    // vec2 gravity = mul(vec2(0, -1), area);
    // return cross(to_pivot, gravity);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n;
    cin >> n;
    a = vector<vec2>(n, vec2());
    ld min_x = 1e9;
    ld max_x = -1e9;
    for(ll i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
        if(a[i].y == 0){
            min_x = min(min_x, a[i].x);
            max_x = max(max_x, a[i].x);
        }
    }
    ld left_torque = calc_torque(a, min_x);
    ld right_torque = calc_torque(a, max_x);
    //cout << left_torque << " " << right_torque << "\n";
    vec2 weight_pos = a[0];
    bool inf = true; 
    bool unstable = false;
    ld min_weight = 0;
    ld max_weight = 1e30;
    {
        //left side
        ld r = min_x - weight_pos.x;
        if(r > 0 && left_torque > 0){
            unstable = true;
        }
        if(r < 0 && left_torque > 0){
            min_weight = max(min_weight, abs(left_torque / r));
        }
        if(r > 0 && left_torque < 0){
            max_weight = min(max_weight, abs(left_torque / r));
        }
        if(r < 0 && left_torque < 0){
            //do nothing
        }
        if(r == 0 && left_torque > 0){
            unstable = true;
        }
    }
    {
        //right side
        ld r = max_x - weight_pos.x;
        if(r > 0 && right_torque > 0){
            //do nothing
        }
        if(r < 0 && right_torque > 0){
            max_weight = min(max_weight, abs(right_torque / r));
        }
        if(r > 0 && right_torque < 0){
            min_weight = max(min_weight, abs(right_torque / r));
        }
        if(r < 0 && right_torque < 0){
            unstable = true;
        }
        if(r == 0 && right_torque < 0){
            unstable = true;
        }
    }
    if(unstable) {
        cout << "unstable\n";
        return 0;
    }
    if(max_weight == 1e30) {
        cout << ((ll) floor(min_weight)) << " .. " << "inf" << "\n";
        return 0;
    }
    cout << ((ll) floor(min_weight)) << " .. " << ((ll) ceil(max_weight - 1e-9)) << "\n";
    
    return 0;
}
