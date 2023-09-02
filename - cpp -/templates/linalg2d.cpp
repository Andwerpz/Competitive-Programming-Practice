#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct vec {
    ld x, y;
};

vec add(vec a, vec b){
    vec ret;
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    return ret;
}

vec sub(vec a, vec b) {
    vec ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    return ret;
}

ld cross(vec a, vec b) {
    return a.x * b.y - a.y * b.x;
}

ld dot(vec a, vec b) {
    return a.x * b.x + a.y * b.y;
}

ld length(vec a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

vec mul(vec a, ld s) {
    a.x *= s;
    a.y *= s;
    return a;
}

vec normalize(vec a){
    ld len = length(a);
    vec ret;
    ret.x = a.x / len;
    ret.y = a.y / len;
    return ret;
}

//returns the coefficients s and t, where p1 + v1 * s = p2 + v2 * t
vector<ld> lineLineIntersect(vec p1, vec v1, vec p2, vec v2) {
    if(cross(v1, v2) == 0){
        return {};
    }
    ld s = cross(sub(p2, p1), v2) / cross(v1, v2);
    ld t = cross(sub(p1, p2), v1) / cross(v2, v1);
    return {s, t};
}

//returns the distance along the ray from ray_a to the nearest point on the circle. 
ld rayCircleIntersect(vec ray_a, vec ray_b, vec center, ld radius) {
    vec ray_dir = normalize(sub(ray_b, ray_a));
    vec to_center = sub(center, ray_a);
    vec center_proj = add(ray_a, mul(ray_dir, dot(ray_dir, to_center)));
    ld center_proj_len = length(sub(center, center_proj));
    //radius^2 = center_proj_len^2 + int_depth^2
    //int_depth = sqrt(radius^2 - center_proj_len^2)
    ld int_depth = sqrt(radius * radius - center_proj_len * center_proj_len);
    return dot(ray_dir, to_center) - int_depth;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    
    return 0;
}
