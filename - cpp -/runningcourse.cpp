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

//Baekjoon - 1310

//rotating calipers technique tester. 

ld pi = acos(-1);
ld epsilon = 1e-9;

struct vec2 {
    ll x, y;
    vec2(ll _x = 0, ll _y = 0) {x = _x; y = _y;}
    vec2(const vec2& other) {x = other.x; y = other.y;}
    vec2(const vec2& a, const vec2& b) {x = b.x - a.x; y = b.y - a.y;}  //creates A to B
    vec2& operator=(const vec2& other) {x = other.x; y = other.y; return *this;}
    vec2 operator-() const {return vec2(-x, -y);}
    vec2 operator+(const vec2& other) const {return vec2(x + other.x, y + other.y);}
    vec2& operator+=(const vec2& other) {*this = *this + other; return *this;}
    vec2 operator-(const vec2& other) const {return vec2(x - other.x, y - other.y);}
    vec2& operator-=(const vec2& other) {*this = *this - other; return *this;}
    vec2 operator*(ll other) const {return vec2(x * other, y * other);}
    vec2& operator*=(ll other) {*this = *this * other; return *this;}
    vec2 operator/(ll other) const {return vec2(x / other, y / other);}
    vec2& operator/=(ll other) {*this = *this / other; return *this;}

    ll lengthSq() const {return x * x + y * y;}
    ll length() const {return sqrt(lengthSq());}
    vec2 get_normal() const {return *this / length();}
    void normalize() {*this /= length();}   //actually normalizes this vector
    ll distSq(const vec2& other) const {return vec2(*this, other).lengthSq();}
    ll dist(const vec2& other) const {return sqrt(distSq(other));}

    ll dot(const vec2& other) const {return x * other.x + y * other.y;}
    ll cross(const vec2& other) const {return x * other.y - y * other.x;}
    ll angle_to(const vec2& other) const {return acos(dot(other) / length() / other.length());}
    vec2 rotate_CCW(ll theta) const {return vec2(x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta));}

    //angle from x axis in range (-pi, pi)
    ll polar_angle() {return atan2(y, x);}  

    //projection of other onto this
    vec2 project(const vec2& other) {return *this * (other.dot(*this) / dot(*this));}

    friend std::ostream& operator<<(std::ostream& os, const vec2& v) {os << "[" << v.x << ", " << v.y << "]"; return os;}
    friend std::istream& operator>>(std::istream& is, vec2& v) {is >> v.x >> v.y; return is;}
};
vec2 operator*(ll a, const vec2& b) {return vec2(a * b.x, a * b.y);}

ll cross(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}

ll dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

ll lerp(ll t0, ll t1, ll x0, ll x1, ll t) {
    ll slope = (x1 - x0) / (t1 - t0);
    return x0 + slope * (t - t0);
}

//returns convex hull in CCW order
//make sure that there aren't any duplicate points. This algorithm really doesn't like that. 
vector<vec2> convex_hull(vector<vec2>& a, bool include_collinear = false) {
    function<int(vec2, vec2, vec2)> orientation = [](vec2 a, vec2 b, vec2 c) -> int {
        ll v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
        if (v < 0) return -1; // clockwise
        if (v > 0) return +1; // counter-clockwise
        return 0;
    };
    function<bool(vec2, vec2, vec2)> collinear = [&orientation](vec2 a, vec2 b, vec2 c) -> bool {
        return orientation(a, b, c) == 0;
    };
    function<bool(vec2, vec2, vec2, bool)> cw = [&orientation](vec2 a, vec2 b, vec2 c, bool include_collinear) -> bool {
        int o = orientation(a, b, c);
        return o < 0 || (include_collinear && o == 0);
    };
    vec2 p0 = *min_element(a.begin(), a.end(), [](vec2 a, vec2 b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0, &orientation](const vec2& a, const vec2& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y) < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }
    vector<vec2> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }
    //make sure there are no duplicate vertices
    vector<vec2> ans(0);
    for(int i = 0; i < st.size(); i++){
        vec2 v0 = st[i];
        vec2 v1 = st[(i + 1) % st.size()];
        if(v0.x == v1.x && v0.y == v1.y) {
            continue;
        }
        ans.push_back(st[i]);
    }
    //reverse to make winding CCW
    reverse(ans.begin(), ans.end());
    return ans;
}

//finds all pairs of points that are 'directly across' from each other on a convex hull
//don't include collinear points in the hull
//https://codeforces.com/blog/entry/133763
vector<pii> all_anti_podal(vector<vec2> &p) {
    int n = p.size();
    //degenerate hull
    if(n == 1) return {{0, 0}};
    if(n == 2) return {{0, 1}};

    int p1 = 0, p2 = 0; // two "pointers"
    vector<pii> result;

    // parallel edges should't be visited twice
    vector<bool> vis(n, false);

    function<int(int)> nx = [&n](int i) -> int {return (i + 1) % n;};
    function<int(int)> pv = [&n](int i) -> int {return (i - 1 + n) % n;};
    function<int(ll)> sign = [](ll x) -> int {return x == 0? 0 : (x < 0? -1 : 1);};

    for (;p1<n;p1++) {
        // the edge that we are going to consider in this iteration
        // the datatype is Point, but it acts as a vector
        vec2 base = p[nx(p1)] - p[p1];

        // the last condition makes sure that the cross products don't have the same sign
        while (p2 == p1 || p2 == nx(p1) || sign(cross(base, p[nx(p2)] - p[p2])) == sign(cross(base, p[p2] - p[pv(p2)]))) {
            p2 = nx(p2);
        }

        if (vis[p1]) continue;
        vis[p1] = true;

        result.push_back({p1, p2});
        result.push_back({nx(p1), p2});
        
        // if both edges from p1 and p2 are parallel to each other
        if (cross(base, p[nx(p2)] - p[p2]) == 0) {
            result.push_back({p1, nx(p2)});
            result.push_back({nx(p1), nx(p2)});
            vis[p2] = true;
        }
    }

    return result;
}

ll solve(vector<vec2> a) {
    int n = a.size();
    if(n == 1) return 0;
    if(n == 2) return (a[0] - a[1]).lengthSq();
    vector<vec2> hull = convex_hull(a, false);
    // cout << "HULL : " << "\n";
    // for(int i = 0; i < hull.size(); i++){
    //     cout << hull[i] << endl;
    // }
    vector<pii> p = all_anti_podal(hull);
    // cout << "PAIRS : " << "\n";
    // for(int i = 0; i < p.size(); i++){
    //     cout << p[i].first << " " << p[i].second << "\n";
    // }
    ll ans = 0;
    for(pii x : p) ans = max(ans, (hull[x.first] - hull[x.second]).lengthSq());
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    set<pii> s;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        s.insert({x, y});
    }
    vector<vec2> a(0);
    for(auto i = s.begin(); i != s.end(); i++){
        a.push_back({i->first, i->second});
    }
    // vector<vec2> a(n);
    // for(int i = 0; i < n; i++){
    //     cin >> a[i];
    // }
    cout << solve(a) << "\n";
    
    return 0;
}