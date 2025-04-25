#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
// typedef __float128 ld;
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

ld pi = acos(-1);
ld epsilon = 1e-11;
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

    // angle from x axis in range (-pi, pi)
    ld polar_angle() {return atan2(y, x);}  

    // projection of other onto this
    vec2 project(const vec2& other) {return *this * (other.dot(*this) / dot(*this));}

    friend std::ostream& operator<<(std::ostream& os, const vec2& v) {os << "[" << v.x << ", " << v.y << "]"; return os;}
    friend std::istream& operator>>(std::istream& is, vec2& v) {
        long double _x, _y;
        is >> _x >> _y;
        v.x = _x, v.y = _y;
        return is;
    }
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

struct arc {
    int id, istop;
    vec2 c;
    ld r;
    arc() {}
    arc(int _id, int _istop, vec2 _c, ld _r) {id = _id, istop = _istop, c = _c, r = _r;}
};

struct circle {
    vec2 c;
    ld r;
    circle() {}
    circle(int x, int y, int _r) {c = {x, y}, r = _r;}
};

ld calc_y(arc a, ld xpos){
    ld da = sqrt(max((ld) 0, a.r * a.r - (xpos - a.c.x) * (xpos - a.c.x)));
    ld ya = a.c.y + da * (a.istop? 1 : -1);
    if(isnan(ya)) {
        cout << "NAN!!" << endl;
        cout << a.r << " " << a.istop << " " << a.id << " " << a.c << " " << a.r * a.r - (xpos - a.c.x) * (xpos - a.c.x)  << endl;
        // ya = 0;
    }
    return ya;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ifstream in("bomas.in");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("bomas.out");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    // cout << "START : " << endl;
    int n, q;
    cin >> n >> q;
    vector<circle> cir(n + q);
    vector<pair<int, pii>> ord(0);   //{xpos, {should add? 1 : 0, ind}}
    for(int i = 0; i < n + q; i++){
        int x, y, r;
        cin >> x >> y >> r;
        cir[i] = {x, y, r};
        ord.push_back({x - r, {1, i}});
        ord.push_back({x + r, {0, i}});
    }
    sort(ord.begin(), ord.end());
    ld xpos = -1e8;
    function<bool(arc a, arc b)> cmp = [&xpos](arc a, arc b) -> bool {
        //compute deviation
        //x^2 + y^2 = r^2
        //x = (xpos - c.x)
        //|y| = sqrt(r^2 - (xpos - c.x)^2)
        // ld da = sqrt(max((ld) 0, a.r * a.r - (xpos - a.c.x) * (xpos - a.c.x)));
        // ld db = sqrt(max((ld) 0, b.r * b.r - (xpos - b.c.x) * (xpos - b.c.x)));
        // da = 0, db = 0;
        //only care about ypos
        ld ya = calc_y(a, xpos);
        ld yb = calc_y(b, xpos);
        if(ya == yb) return a.istop > b.istop;
        return ya > yb;
    };
    //for each circle, compute its children and siblings
    vvi c(n + q), sib(n + q);
    vb isr(n, true);
    set<arc, decltype(cmp)> s(cmp);
    for(int i = 0; i < ord.size(); i++){
        int ind = ord[i].second.second;
        if(ord[i].second.first) {
            xpos = ord[i].first + 0.1;
            cout << "ADDING : " << ind << " " << cir[ind].r << " " << fixed << setprecision(10) << xpos << endl;
            //adding
            arc top = {ind, 1, cir[ind].c, cir[ind].r};
            arc bot = {ind, 0, cir[ind].c, cir[ind].r};
            auto ptr = s.lower_bound(top);
            if(ptr != s.begin()) {
                isr[ind] = false;
                ptr --;
                if(ptr->istop) {
                    //this is my parent
                    // cout << "PAR : " << ptr->id << endl;
                    c[ptr->id].push_back(ind);
                }
                else {
                    //this is my sibling
                    // cout << "SIB : " << ptr->id << endl;
                    sib[ptr->id].push_back(ind);
                }
            }
            s.insert(top);
            s.insert(bot);
        }
        else {
            //removing
            // xpos = ord[i].first - epsilon;
            cout << "REMOVING : " << ind << " " << cir[ind].r << endl;
            s.erase({ind, 1, cir[ind].c, cir[ind].r});
            s.erase({ind, 0, cir[ind].c, cir[ind].r});
            // int fid, sid;
            // auto ptr = s.lower_bound({ind, 1, {cir[ind].c.x, cir[ind].c.y + epsilon}, cir[ind].r});
            // assert(ptr != s.end());
            // assert(ptr->istop);
            // fid = ptr->id;
            // // cout << "RM : " << ptr->id << " " << ptr->istop << endl;
            // s.erase(ptr);
            // ptr = s.lower_bound({ind, 1, {cir[ind].c.x, cir[ind].c.y + epsilon}, cir[ind].r});
            // assert(ptr != s.end());
            // assert(!ptr->istop);
            // sid = ptr->id;
            // // cout << "RM : " << ptr->id << " " << ptr->istop << endl;
            // s.erase(ptr);
            // assert(fid == sid);
        }
        cout << "S : " << endl;
        for(auto j = s.begin(); j != s.end(); j++){
            cout << j->id << " " << j->istop << " " << calc_y(*j, xpos) << " " << j->r << endl;
        }
    }
    // cout << "2\n1\n1\n1\n3\n";
    // return 0;
    //build tree structure. circles without parents will have -1 as their parent
    vi p(n + q, -1);
    function<void(int, int)> build_tree = [&](int ind, int par) -> void {
        p[ind] = par;
        //siblings should all have the same parent
        for(int x : sib[ind]) build_tree(x, par);
        //children should have this as parent
        for(int x : c[ind]) build_tree(x, ind);
    };
    for(int i = 0; i < n + q; i++){
        if(isr[i]){
            // cout << "TREE ROOT : " << i << endl;
            build_tree(i, -1);
        }
    }
    c = vvi(n + q, vi(0));
    for(int i = 0; i < n + q; i++){
        if(p[i] != -1) c[p[i]].push_back(i);
    }
    // cout << "TREE : " << "\n";
    // for(int i = 0; i < n + q; i++){
    //     cout << "I : " << i << ", ";
    //     for(int x : c[i]) cout << x << " ";
    //     cout << "\n";
    // }
    //calc mis for every subtree, ignoring query nodes
    vvi dp(n + q, vi(2, -1));   //par selected, par not selected
    function<int(int, int)> calc_mis = [&](int cur, int par_sel) -> int {
        if(dp[cur][par_sel] != -1) return dp[cur][par_sel];
        int ans = 0;
        if(cur >= n){
            //query node, just pass the info along
            for(int x : c[cur]) ans += calc_mis(x, par_sel);
        }
        else {
            //normal node, decide to select or not
            if(!par_sel) {
                //select
                int cans = 1;
                for(int x : c[cur]) cans += calc_mis(x, 1);
                ans = max(ans, cans);
            }
            {
                //don't select
                int cans = 0;
                for(int x : c[cur]) cans += calc_mis(x, 0);
                ans = max(ans, cans);
            }
        }
        return ans;
    };
    //print ans
    for(int i = n; i < n + q; i++){
        int ans = 0;
        {
            //select
            int cans = 1;
            for(int x : c[i]) cans += calc_mis(x, 1);
            ans = max(ans, cans);
        }
        {
            //don't select
            int cans = 0;
            for(int x : c[i]) cans += calc_mis(x, 0);
            ans = max(ans, cans);
        }
        cout << ans << "\n";
    }
    
    return 0;
}