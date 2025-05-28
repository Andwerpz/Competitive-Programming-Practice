#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;
// typedef __float128 ld;

//2021 CCPC Guilin Onsite - F

//we can compute the probability for each side of the smaller convex hull to be lit up, and then add all the probabilities
//multiplied by their respective lengths together to get the total expected value. 

//to find the probability for each side, we just need to get the total side length of the larger hull that the halfplane 
//contains. We can do sliding window over the larger hull boundary. 

//here, i learned to never normalize your vectors as it gives a large precision hit if you do so. 

ld pi = acos(-1);
ld epsilon = 1e-6;
ld inf = 1e11;

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
    if(cross(v1, v2) == 0) return {inf, inf};
    ld s = cross(p2 - p1, v2) / cross(v1, v2);
    return p1 + v1 * s;
}

vec2 line_linesegIntersect(vec2 s1, vec2 e1, vec2 s2, vec2 e2) {
    vec2 isect = line_lineIntersect(s1, e1 - s1, s2, e2 - s2);
    ld xmin = min(s2.x, e2.x), xmax = max(s2.x, e2.x);
    ld ymin = min(s2.y, e2.y), ymax = max(s2.y, e2.y);
    // ld eps = max(xmax - xmin, ymax - ymin) / 1e10;
    ld eps = epsilon;
    xmin -= eps, xmax += eps;
    ymin -= eps, ymax += eps;
    if(isect.x < xmin || isect.x > xmax || isect.y < ymin || isect.y > ymax) {
        // cout << "NOTIN SEG " << fixed << setprecision(10) << isect.x << " " << xmax << "\n";
        return {inf, inf};
    }
    return isect;
}

int sgn(ld x) {
    if (x < 0) return -1;
    else if(x > 0) return 1;
    else return 0;
}

//is c to the left or right of the line defined by a -> b?
int sideof(vec2 a, vec2 b, vec2 c) {
    return sgn(cross(b - a, c - a));
}

signed main() {

    int n, m;
    cin >> n >> m;
    vector<vec2> a(n), b(m);
    for(int i = 0; i < n; i++){
        ld x, y;
        cin >> x >> y;
        a[i] = {x, y};
        // a[i] *= 1e9;
    }
    for(int i = 0; i < m; i++){
        ld x, y;
        cin >> x >> y;
        b[i] = {x, y};
        // b[i] *= 1e9;
    }
    vector<ld> aslen(n);
    for(int i = 0; i < n; i++) aslen[i] = (a[(i + 1) % n] - a[i]).length();
    // for(int i = 0; i < n; i++) cout << aslen[i] << " ";
    // cout << "\n";
    vector<ld> aspfx(n + 1, 0);
    for(int i = 1; i <= n; i++) aspfx[i] = aspfx[i - 1] + aslen[i - 1];
    //consider b[0] -> b[1] first
    int lptr = 0, rptr = 0;
    ld ans = 0;
    for(int i = 0; i < m; i++){
        vec2 bl = b[i], br = b[(i + 1) % m];
        int cntr = 0;
        while(true) {
            cntr ++;
            assert(cntr < 2 * n);
            // cout << "TEST LPTR : " << lptr << endl;
            vec2 isect = line_linesegIntersect(bl, br, a[lptr], a[(lptr + 1) % n]);
            int side = sideof(bl, br, a[(lptr + 1) % n]);
            // cout << isect.x << " " << isect.y << " " << side << "\n";
            if(isect == vec2(inf, inf) || side >= 0) {
                lptr = (lptr + 1) % n;
                continue;
            }
            break;
        }
        while(true) {
            cntr ++;
            assert(cntr < 3 * n);
            // cout << "TEST RPTR : " << rptr << endl;
            vec2 isect = line_linesegIntersect(bl, br, a[rptr], a[(rptr + 1) % n]);
            int side = sideof(bl, br, a[(rptr + 1) % n]);
            // cout << isect.x << " " << isect.y << " " << side << "\n";
            if(isect == vec2(inf, inf) || side <= 0) {
                rptr = (rptr + 1) % n;
                continue;
            }
            break;
        }
        assert(lptr != rptr);
        vec2 li = line_linesegIntersect(bl, br, a[lptr], a[(lptr + 1) % n]);
        vec2 ri = line_linesegIntersect(bl, br, a[rptr], a[(rptr + 1) % n]);
        // cout << "I : " << i << " " << lptr << " " << rptr << "\n";
        // cout << "BLINE : " << bl.x << " " << bl.y << " " << br.x << " " << br.y << "\n";
        // cout << "LI RI : " << li.x << " " << li.y << " " << ri.x << " " << ri.y << "\n";
        // cout << "LRPTR : " << lptr << " " << rptr << "\n";
        ld clen = 0;
        int l = (lptr + 1) % n, r = rptr;
        if(l <= r) clen += aspfx[r] - aspfx[l];
        else {
            clen += aspfx[n] - aspfx[l];
            clen += aspfx[r];
        }
        // cout << "ADD MID : " << l << " " << r << " " << clen << "\n";
        // cout << "ANS : " << ans << "\n";
        clen += (li - a[(lptr + 1) % n]).length();
        clen += (ri - a[rptr]).length();
        ans += (bl - br).length() * clen;
    }
    ans /= aspfx[n];
    // cout << "SUM : " << ans << "\n";
    // cout << "ASPFX : " << aspfx[n] << "\n";
    // ans /= aspfx[n];
    cout << fixed << setprecision(15) << ans << "\n";

    return 0;
}