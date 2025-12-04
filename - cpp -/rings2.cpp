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

//Kattis - rings

//beware of the edge case where a ring entirely contains another ring. 

//can just do union find or BFS across all the rings. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    while(n != -1) {
        vector<vec2> a(n);
        vd r(n);
        for(int i = 0; i < n; i++) cin >> a[i] >> r[i];
        vb v(n, false);
        int ans = 0;
        for(int i = 0; i < n; i++){
            if(v[i]) continue;
            // cout << "I : " << i << "\n";
            int cans = 0;
            queue<int> q;
            q.push(i);
            v[i] = true;
            while(q.size() != 0){
                int cur = q.front();
                // cout << "CUR : " << cur << "\n";
                q.pop();
                cans ++;
                for(int j = 0; j < n; j++){
                    if(v[j]) continue;
                    // cout << "COMP : " << j << " " << (a[cur] - a[j]).length() << " " << r[cur] + r[j] << "\n";
                    // cout << "cur, j : " << a[cur] << " " << a[j] << "\n";
                    ld dist = (a[cur] - a[j]).length();
                    ld r1 = max(r[cur], r[j]), r2 = min(r[cur], r[j]);
                    if(r1 >= r2 + dist) continue;
                    if((a[cur] - a[j]).length() <= r[cur] + r[j]) v[j] = true, q.push(j);
                }
            }
            ans = max(ans, cans);
        }
        if(ans > 1) cout << "The largest component contains " << ans << " rings.\n";
        else cout << "The largest component contains 1 ring.\n";
        cin >> n;
    }
    
    return 0;
}