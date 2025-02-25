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

//Codeforces - 1190E

//binary search + greedy with binary lifting. 

//as with any geometry problem, we can probably binary search for the answer. Obviously if some minimum distance works, then
//any minimum distance less than it will also work, so binary search should work. 

//consider fixing the minimum distance at which the barriers must be placed from the origin, let this distance be r. WLOG, we
//can say that any barrier placed must be tangent to the circle of radius r placed at the origin, as placing it any farther 
//will be strictly worse. Then, the only parameter left that we can adjust when placing the barrier is its angle relative to the 
//origin. 

//Next, consider for a single point, the range of angles that a barrier can be placed such that the barrier protects the point. 
//Now, we just want to place at most m barriers such that all n points are protected. If this problem were presented on a 
//non-circular array, then there's a straightforwards greedy solution: sort all segments by increasing left bound, and string
//as many segments in the front as possible until you can't anymore. 

//We can solve this on a circular array as well, we just need to take some segment as an initial one, then the array becomes
//non-circular and we can apply the above strategy. The problem is that we need to try all n choices of the initial segment so
//it ends up being O(n^2). 

//We can fix this by speeding up trying some initial choice by using binary lifting. First, copy over every segment so now
//we have 2n segments. Then, bli[i][0] = what is the maximum segment that can't be covered when placing a barrier to cover 
//segment i, and bli[i][j] = bli[bli[i][j - 1]][j - 1]. bli[i][0] can be computed in O(n * log(n)) time by observing that 
//bli[i][0] >= bli[i - 1][0], and using 2 pointers. 

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

const int B = 17;
int bli[200005][B];
vector<pair<ld, ld>> seg(200005); //{enter time, exit time}
ld d[200005];
bool is_valid(vector<vec2>& a, int n, int m, ld r) {
    //find segments
    for(int i = 0; i < n; i++){
        ld pa = a[i].polar_angle();
        ld theta = acos(r / d[i]);
        ld l = pa - theta, r = pa + theta;
        while(l > 2 * pi) l -= 2 * pi, r -= 2 * pi;
        while(l < 0) l += 2 * pi, r += 2 * pi;
        seg[i] = {l, r};
    }
    sort(seg.begin(), seg.begin() + n);
    for(int i = 0; i < n; i++) {
        ld l = seg[i].first, r = seg[i].second;
        seg[i + n] = {l + 2 * pi, r + 2 * pi};
    }
    //build binary lifting table
    for(int i = 0; i < B; i++){
        bli[n * 2][i] = n * 2;
    }
    set<ld> rset;
    int rptr = 0;
    for(int i = 0; i < n * 2; i++){
        while(rptr != n * 2) {
            if(rset.size() != 0 && *rset.begin() < seg[rptr].first) break;
            rset.insert(seg[rptr].second);
            rptr ++;
        }
        bli[i][0] = rptr;
        rset.erase(seg[i].second);
    }
    for(int i = 1; i < B; i++){
        for(int j = 0; j < n * 2; j++){
            bli[j][i] = bli[bli[j][i - 1]][i - 1];
        }
    }   
    //check valid
    bool is_valid = false;
    for(int i = 0; i < n; i++){
        int ptr = i;
        for(int j = B - 1; j >= 0; j--){
            if(m & (1 << j)) ptr = bli[ptr][j];
        }
        is_valid |= (ptr - i) >= n;
    }
    return is_valid;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    set<pii> as;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        as.insert({x, y});
    }
    n = as.size();
    vector<vec2> a;
    for(auto i = as.begin(); i != as.end(); i++) a.push_back({i->first, i->second});
    for(int i = 0; i < n; i++) d[i] = a[i].length();
    ld low = 0, high = 1e18;
    for(int i = 0; i < n; i++) high = min(high, a[i].length());
    while(high - low > 1e-7) {
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