#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//3rd Universal Cup, Stage 7: Warsaw - H

//a bunch of casework. 

//observe that it's always possible to solve with 4 elbows. Point the elbows connecting directly
//to the inlet and outlet in the +z direction, and then connect the two lines using 2 more elbows. 

//what cases can we do better? read the code to figure that out :P

const ld epsilon = 1e-10;
const ld pi = acos(-1);

struct vec3 {
    ll x, y, z;
    vec3() {x = 0, y = 0, z = 0;}
    vec3(ll _x, ll _y, ll _z) {x = _x, y = _y, z = _z;}
    ld length() {return sqrt(x * x + y * y + z * z);}
};

struct vec3f{
    ld x, y, z;
    vec3f() {x = 0, y = 0, z = 0;}
    vec3f(ld _x, ld _y, ld _z) {x = _x, y = _y, z = _z;}
    vec3f(vec3& a) {x = a.x, y = a.y, z = a.z;}
    ld length() {return sqrt(x * x + y * y + z * z);}
};

vec3 add(vec3 a, vec3 b) {
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec3 sub(vec3 a, vec3 b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

ll dot(vec3 a, vec3 b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

ll dot(vec3 a, vec3 b, vec3 c) {
    return dot(sub(b, a), sub(c, a));
}

vec3f add(vec3f a, vec3f b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

vec3f sub(vec3f a, vec3f b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

ld dot(vec3f a, vec3f b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

ld dot(vec3f a, vec3f b, vec3f c) {
    return dot(sub(b, a), sub(c, a));
}

//computes the angle between b and c from a
ld ang(vec3f a, vec3f b, vec3f c) {
    vec3f ab = sub(b, a), ac = sub(c, a);
    return acos((ld) dot(a, b, c) / (ab.length() * ac.length()));
}

struct vec2 {
    ll x, y;
    vec2() {x = 0, y = 0;}
    vec2(ll _x, ll _y) {x = _x, y = _y;}
};

vec2 add(vec2 a, vec2 b){
    return {a.x + b.x, a.y + b.y};
}

vec2 sub(vec2 a, vec2 b){
    return {a.x - b.x, a.y - b.y};
}

ll dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

ll cross(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}

//equivalent to cross(b - a, c - a)
ll cross(vec2 a, vec2 b, vec2 c){
    return cross(sub(b, a), sub(c, a));
}

pair<ld, ld> line_inter(vec2 p1, vec2 d1, vec2 p2, vec2 d2) {
    vec2 e1 = add(p1, d1), e2 = add(p2, d2);
    if(cross(d1, d2) == 0) {
        //parallel
        assert(false);
    }
    ld d = cross(d1, d2);
    ld p = cross(p2, e1, e2), q = cross(p2, e2, p1);
    ld ansx = (p * p1.x + q * e1.x) / d;
    ld ansy = (p * p1.y + q * e1.y) / d;
    return {ansx, ansy};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        vec3 p1, d1, p2, d2;
        cin >> p1.x >> p1.y >> p1.z >> d1.x >> d1.y;
        cin >> p2.x >> p2.y >> p2.z >> d2.x >> d2.y;
        {
            ll g = gcd(d1.x, d1.y);
            d1.x /= g, d1.y /= g;
            if(d1.x < 0) d1.x *= -1, d1.y *= -1;
            if(d1.x == 0 && d1.y < 0) d1.y *= -1;
        }
        {
            ll g = gcd(d2.x, d2.y);
            d2.x /= g, d2.y /= g;
            if(d2.x < 0) d2.x *= -1, d2.y *= -1;
            if(d2.x == 0 && d2.y < 0) d2.y *= -1;
        }
        int ans = -1;
        // cout << "D : " << d1.x << " " << d1.y << " " << d2.x << " " << d2.y << "\n";
        if(d1.x == d2.x && d1.y == d2.y) {
            //they're parallel. Check if they define the same plane
            ll d = dot(d1, sub(p2, p1));
            // cout << "DOT : " << d << "\n";
            if(dot(d1, sub(p2, p1)) != 0) {
                //don't define the same plane
                ans = 4;
            }
            else {
                //define the same plane
                ans = 2;
            }
        }
        else {  
            //the planes intersect. See where the intersection is, and if the angle is big enough
            pair<ld, ld> isect = line_inter({p1.x, p1.y}, {-d1.y, d1.x}, {p2.x, p2.y}, {-d2.y, d2.x});
            // cout << "ISECT : " << isect.first << " " << isect.second << "\n";
            if((abs(isect.first - p1.x) < epsilon && abs(isect.second - p1.y) < epsilon) || (abs(isect.first - p2.x) < epsilon && abs(isect.second - p2.y) < epsilon)) {
                //intersection goes through one of the points
                // cout << "THRU ISECT\n";
                if((abs(isect.first - p1.x) < epsilon && abs(isect.second - p1.y) < epsilon) && (abs(isect.first - p2.x) < epsilon && abs(isect.second - p2.y) < epsilon)) {
                    //goes through both of the points
                    ans = 2;
                }
                else if(p1.z == p2.z) {
                    //have to add an extra joint 
                    ans = 4;
                }
                else {
                    //go along p1 -> isect -> p2
                    ans = 3;
                }
            }
            else {
                //ternary search for the maximum angle
                ld theta = ang({isect.first, isect.second, p1.z}, p1, p2);
                ld low = min(p1.z, p2.z), high = max(p1.z, p2.z);
                while(high - low > epsilon) {
                    ld m1 = low + (high - low) / 3.0 * 1.0;
                    ld m2 = low + (high - low) / 3.0 * 2.0;
                    ld a1 = ang({isect.first, isect.second, m1}, p1, p2);
                    ld a2 = ang({isect.first, isect.second, m2}, p1, p2);
                    if(a1 < a2) low = m1;
                    else high = m2;
                    // cout << "MID : " << max(a1, a2) << "\n";
                    theta = max(theta, max(a1, a2));
                }
                // cout << "PT : " << isect.first << " " << isect.second << " " << low << "\n";
                // cout << "THETA : " << theta << "\n";
                if(theta + epsilon >= pi / 2.0){
                    //angle is big enough
                    ans = 3;
                } 
                else {
                    //angle is not big enough. 
                    //have to go p1 -> isect (p1.z) -> isect (p2.z) -> p2
                    //is there a more direct route?
                    ans = 4;
                }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}