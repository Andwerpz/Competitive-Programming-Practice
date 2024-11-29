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

//UTPC Contest 11-20-24 Div1 - I

//wlog, we can see that any optimal circle placement has to have at least 2 people on the boundary. 

//so, we can iterate over everyone, and put the boundary of the circle on the current person. Next, we can
//just rotate the circle around the current person using sweepline over polar angles to figure out the maximum 
//answer given the circle boundary is on the current person. 

ld pi = acos(-1);
ld epsilon = 1e-12;

struct vec2 {
    ld x, y;
    vec2(ld _x = 0, ld _y = 0) {x = _x; y = _y;}
    vec2(const vec2& other) {x = other.x; y = other.y;}
    vec2(const vec2& a, const vec2& b) {x = b.x - a.x; y = b.y - a.y;}  //creates A to B
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

int circle_around(vector<vec2>& a, int ind, ld r){
    vector<pair<ld, int>> ev(0);
    for(int i = 0; i < a.size(); i++){
        if(i == ind){
            continue;
        }
        ld d = a[ind].dist(a[i]);
        if(d > r * 2.0) {
            continue;
        }
        ld ang = (a[i] - a[ind]).polar_angle();
        ld off = acos((d / 2.0) / r);
        ev.push_back({ang - off - epsilon, (i + 1)});
        ev.push_back({ang + off + epsilon, -(i + 1)});
    }
    for(int i = 0; i < ev.size(); i++){
        ld ang = ev[i].first;
        while(ang < -pi){
            ang += 2.0 * pi;
        }
        while(ang > pi){
            ang -= 2.0 * pi;
        }
        ev[i].first = ang;
    }
    sort(ev.begin(), ev.end());
    int n = a.size();
    vb s(n, false);
    int cnt = 0;
    int ans = 0;
    for(int i = 0; i < ev.size() * 2; i++){
        int cur = abs(ev[i % ev.size()].second);
        if(ev[i % ev.size()].second < 0){
            cnt -= s[cur];
            s[cur] = false;
        }
        else {
            s[cur] = true;
            cnt += s[cur];
        }
        ans = max(ans, cnt);
    }
    return ans + 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    ld r;
    cin >> n >> r;
    vector<vec2> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans = max(ans, circle_around(a, i, r));
    }
    cout << ans << "\n";
    
    return 0;
}