#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2013 - J

//we can used signed area in order to calculate the area of the polygon, don't try to triangulate. 

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

ld epsilon = 1e-9;

bool calc_intersect(vec2 a1, vec2 a2, vec2 b1, vec2 b2) {
    vector<ld> llersect = lineLineIntersect(a1, sub(a2, a1), b1, sub(b2, b1));
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

vector<vector<vec2>> calc_tri(vector<vec2> a) {
    bool ccw = true;
    vector<vector<vec2>> ret(0);
    while(a.size() > 3) {
        //cout << "FINDING TRIANGLE" << endl;
        for(ll i = 0; i < a.size(); i++){
            //cout << ccw << "\n";
            vec2 t1 = a[(i + 0) % a.size()];
            vec2 t2 = a[(i + 1) % a.size()];
            vec2 t3 = a[(i + 2) % a.size()];
            vec2 v1 = normalize(sub(t2, t1));
            vec2 v2 = normalize(sub(t3, t2));
            //cout << cross(v1, v2) << endl;
            if(!ccw && cross(v1, v2) > epsilon) {
                //cout << "WRONG ANGLE 1" << endl;
                continue;
            }
            if(ccw && cross(v1, v2) < -epsilon) {
                //cout << "WRONG ANGLE 2" << endl;
                continue;
            }
            //might be a valid triangle, go check
            bool isValid = true;
            for(ll j = 0; j < a.size(); j++){
                vec2 l1 = a[(j + 0) % a.size()];
                vec2 l2 = a[(j + 1) % a.size()];
                if(length(sub(l1, t1)) < epsilon || length(sub(l2, t1)) < epsilon || length(sub(l1, t3)) < epsilon || length(sub(l2, t3)) < epsilon) {
                    continue;
                }

                if(calc_intersect(t1, t3, l1, l2)) {
                    isValid = false;
                    break;
                }
            }
            if(isValid) {
                //cout << "FOUND TRIANGLE : " << t1.x << " " << t1.y << " " << t2.x << " " << t2.y << " " << t3.x << " " << t3.y << endl;
                ret.push_back({t1, t2, t3});
                a.erase(a.begin() + ((i + 1) % a.size()));
                break;
            }
        }
    }
    ret.push_back(a);
    return ret;
}

ld pi = 3.1415926535;

ld sector_area(ld theta, ld radius) {
    return radius * radius * pi * ((theta) / (2.0 * pi));
}

// ld chord_area(ld theta, ld radius) {
//     ld sector = sector_area(theta, radius);
//     ld tri_area = radius * radius * cos(theta) * sin(theta);
//     return sector - tri_area;
// }

// //distance from center
// ld chord_area_dist(ld dist, ld radius) {
//     ld theta = acos(dist / radius);
//     return chord_area(theta, radius);
// }

// //length of chord
// ld chord_area_length(ld length, ld radius) {
//     ld theta = asin((length / 2.0) / radius);
//     return chord_area(theta, radius);
// }

vec2 closest_point_along(vec2 a, vec2 b) {
    vec2 to_b = sub(b, a);
    vec2 to_c = sub(vec2(0, 0), a);
    ld dot_p = dot(normalize(to_b), to_c);
    dot_p = max((ld) 0, min(length(to_b), dot_p));
    vec2 close = add(a, mul(normalize(to_b), dot_p));
    return close;
}

vec2 find_circle_intersect(vec2 in, vec2 out, ld c_radius) {
    //just binary search :D
    vec2 c_center = vec2();
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

ld tri_signed_area(vec2 v0, vec2 v1, ld r) {
    if(length(v0) < epsilon || length(v1) < epsilon) {
        return 0;
    }
    bool isNeg = cross(v0, sub(v1, v0)) < 0;
    //cout << v0.x << " " << v0.y << " " << v1.x << " " << v1.y << "\n";
    //cout << "CROSS : " << cross(v0, sub(v1, v0)) << "\n";
    ld cursum = 0;
    ld l0 = length(v0);
    ld l1 = length(v1);
    if(l0 < r && l1 < r) {
        //cout << "BOTH IN\n";
        cursum = tri_area(vec2(), v0, v1);
    }
    else if(l0 < r && l1 > r) {
        //cout << "L0 in, L1 out\n";
        vec2 i0 = find_circle_intersect(v0, v1, r);
        vec2 i1 = find_circle_intersect(vec2(), v1, r);
        ld theta = acos(dot(normalize(i0), normalize(i1)));
        //cout << i0.x << " " << i0.y << " " << i1.x << " " << i1.y << "\n";
        //cout << length(i0) << " " << length(i1) << "\n";
        //cout << "THETA : " << theta << "\n";
        cursum = tri_area(v0, i0, vec2()) + sector_area(theta, r);
    }
    else if(l0 > r && l1 < r) {
        //cout << "L0 out, L1 in\n";
        vec2 i0 = find_circle_intersect(vec2(), v0, r);
        vec2 i1 = find_circle_intersect(v1, v0, r);
        ld theta = acos(dot(normalize(i0), normalize(i1)));
        //cout << i0.x << " " << i0.y << " " << i1.x << " " << i1.y << "\n";
        //cout << length(i0) << " " << length(i1) << "\n";
        //cout << "THETA : " << theta << "\n";
        cursum = tri_area(v1, i1, vec2()) + sector_area(theta, r);
    }
    else if(l0 > r && l1 > r) {
        //cout << "BOTH OUT\n";
        vec2 close = closest_point_along(v0, v1);
        if(length(close) < r) {
            //split the triangle along close, and try again. 
            return tri_signed_area(v0, close, r) + tri_signed_area(close, v1, r);
        }
        //otherwise, it's just the area of the sector
        ld theta = acos(dot(normalize(v0), normalize(v1)));
        //cout << "THETA : " << theta << "\n";
        cursum = sector_area(theta, r);
    }
    if(isNeg) {
        cursum *= -1;
    }
    //cout << cursum << "\n";
    //cout << "\n";
    return cursum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ld r;
    cin >> n >> r;
    vector<vec2> a(n, vec2());
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
    }
    ld sum = 0;
    for(int i = 0; i < n; i++){
        vec2 v0 = a[(i + 0) % n];
        vec2 v1 = a[(i + 1) % n];
        ld next_area = tri_signed_area(v0, v1, r);
        sum += next_area;
    }
    cout << fixed << setprecision(10) << abs(sum) << "\n";
    
    return 0;
}
