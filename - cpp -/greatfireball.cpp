#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//2018 South Central USA Regional - H

//if we fix the radius of the fireball, we can do a sweepline to determine how many orcs it gets. 
//Imagine rotating the fireball around the origin such that the origin is always on the circumference of the
//blast radius. Then, for each orc, calculate the polar angle at which it will enter and exit the fireball. 
//Sort these events by the polar angle, and we can do sweepline. 

//then, we simply have to do a binary search over the radius. If a radius of around 1e9 still doesn't work, 
//then we can just say that it's impossible. 

//even with a generous time limit of 18 seconds, we still might TLE, so we can take advantage of the lenient
//error tolerance and terminate our binary search at around 1e-6. 

ld pi = acos(-1);
ld epsilon = 1e-9;

struct vec2 {
    ld x, y;
    vec2() {this->x = 0; this->y = 0;}
    vec2(ld x, ld y) {this->x = x; this->y = y;}
};

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

ld distance(vec2 a, vec2 b){
    return length(sub(a, b));
}

ld lerp(ld t0, ld t1, ld x0, ld x1, ld t) {
    ld slope = (x1 - x0) / (t1 - t0);
    return x0 + slope * (t - t0);
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

//angle from the +x axis in range (-pi, pi)
ld polar_angle(vec2 a) {
    return atan2(a.y, a.x);
}

//project a onto b
vec2 project(vec2 a, vec2 b) {
    b = normalize(b);
    ld proj_mag = dot(a, b);
    return mul(b, proj_mag);
}

vec2 rotateCCW(vec2 a, ld theta) {
    vec2 ret(0, 0);
    ret.x = a.x * cos(theta) - a.y * sin(theta);
    ret.y = a.x * sin(theta) + a.y * cos(theta);
    return ret;
}

int calc_nr(vector<vec2>& a, ld radius) {
    vector<pair<ld, pair<bool, int>>> events;   //{polar angle, {add flag, id}}
    for(int i = 0; i < a.size(); i++){
        vec2 cur = a[i];
        ld polar = polar_angle(cur);
        ld x = length(cur) / 2.0;
        if(x + epsilon >= radius) {
            continue;
        }
        ld theta = acos(x / radius);
        events.push_back({polar - theta, {true, i}});
        events.push_back({polar + theta, {false, i}});
    }
    for(int i = 0; i < events.size(); i++){
        while(events[i].first < 0){
            events[i].first += 2.0 * pi;
        }
        while(events[i].first > 2.0 * pi) {
            events[i].first -= 2.0 * pi;
        }
    }
    sort(events.begin(), events.end());
    int ans = 0;
    set<int> s;
    for(int i = 0; i < 2 * events.size(); i++){
        int id = events[i % events.size()].second.second;
        bool add = events[i % events.size()].second.first;
        if(add){
            s.insert(id);
        }
        else {
            s.erase(id);
        }
        ans = max(ans, (int) s.size());
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<vec2> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
    }
    ld low = epsilon;
    ld high = 1e10;
    ld ans = high;
    while(high - low > 1e-6) {
        ld mid = low + (high - low) / 2;
        if(calc_nr(a, mid) >= k) {
            high = mid;
            ans = min(ans, mid);
        }
        else {
            low = mid;
        }
    }
    if(ans == 1e10){
        cout << "-1\n";
    }
    else {
        cout << fixed << setprecision(10) << ans << "\n";
    }
    
    return 0;
}
