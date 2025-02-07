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

ld pi = acos(-1);
ld epsilon = 1e-11;

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

bool is_valid(vector<vec2>& a, int n, int m, ld r) {
    vector<pair<ld, pii>> ev;   //{time, {exit? 0 : 1, ind}}
    for(int i = 0; i < n; i++){
        ld d = a[i].length();
        ld pa = a[i].polar_angle();
        ld theta = acos(r / d);
        ld indoff = i * 1e-13;  //make it so that every point has unique enter and exit (hopefully)
        ev.push_back({pa - theta + indoff, {0, i}});
        ev.push_back({pa + theta + indoff, {1, i}});
    }
    for(int i = 0; i < ev.size(); i++){
        ld ang = ev[i].first;
        while(ang > 2 * pi) ang -= 2 * pi;
        while(ang < 0) ang += 2 * pi;
        ev[i].first = ang;
    }
    sort(ev.begin(), ev.end());
    cout << "EV : " << "\n";
    for(pair<ld, pii> x : ev) {
        if(x.second)
        cout << x.first << " " << x.second.first << " " << x.second.second << "\n";
    }
    vi mext(n, -1);
    set<int> s;
    int mrec_enter = -1;
    for(int i = 0; i < ev.size() * 2; i ++){
        int exit = ev[i % ev.size()].second.first, ind = ev[i % ev.size()].second.second;
        if(exit) s.erase(ind);
        else s.insert(ind), mrec_enter = ind;
        if(i >= ev.size()) {
            if(exit) mext[ind] = mrec_enter;
        }   
        if(s.size() == n) return true;
    }
    vi dp(n + 1, -1), endpt(n, -1);
    dp[n] = 0;
    for(int i = n - 1; i >= 0; i--){
        int stop = mext[i];
        while(stop < i) stop += n;
        stop = min(stop + 1, n);
        dp[i] = dp[stop] + 1;
        endpt[i] = stop == n? i : endpt[stop];
    }
    cout << "SOLVE : " << r << "\n";
    cout << "DP : ";
    for(int x : dp) cout << x << " ";
    cout << "\n";
    cout << "MEXT : " << "\n";
    for(int x : mext) cout << x << " ";
    cout << "\n";
    int min_bar = 1e9;
    for(int i = 0; i < n; i++){
        int end = endpt[i];
        int stop = mext[end];
        stop += 1;
        if(stop > i && stop <= end) min_bar = min(min_bar, dp[i]);
    }
    return min_bar <= m;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    map<pii, int> as;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        int g = gcd(abs(x), abs(y));
        if(g == 0) g = 1;
        x /= g, y /= g;
        if(!as.count({x, y})) as[{x, y}] = 1e9;
        as[{x, y}] = min(as[{x, y}], g);
    }
    n = as.size();
    vector<vec2> a;
    for(auto i = as.begin(); i != as.end(); i++) a.push_back({i->first.first * i->second, i->first.second * i->second});
    ld low = 0, high = 1e18;
    for(int i = 0; i < n; i++) high = min(high, a[i].length());
    sort(a.begin(), a.end(), [](vec2& a, vec2& b) -> bool {
        return a.polar_angle() < b.polar_angle();
    });
    while(high - low > epsilon) {
        ld mid = low + (high - low) / 2;
        if(is_valid(a, n, m, mid)) low = mid;
        else high = mid;
    }
    cout << fixed << setprecision(10) << low << "\n";
    
    return 0;
}

/*
13 2
27 2
-1 15
-4 -13
9 17
-22 -2
4 -10
-15 -29
27 -24
23 23
5 30
14 29
-3 24
-9 2

6.6100037948
*/