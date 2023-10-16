#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ABC292F

ld pi = acos(-1);
ld epsilon = 1e-12;

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

vec2 rotateCCW(vec2 a, ld theta) {
    vec2 ret(0, 0);
    ret.x = a.x * cos(theta) - a.y * sin(theta);
    ret.y = a.x * sin(theta) + a.y * cos(theta);
    return ret;
}

//width <= height;
bool isValid(ld width, ld height, ld len) {
    vec2 t0(0, 0);
    vec2 t1(0, 0);
    if(len < width) {
        t1.x = len;
    }
    else {
        t1.x = width;
        t1.y = sqrt(len * len - width * width);
    }
    vec2 t2 = rotateCCW(t1, pi / 3.0);
    if(t2.x < 0 || t2.y > height) {
        return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ld a, b;
    cin >> a >> b;
    if(a > b){
        swap(a, b);
    }
    ld low = 0;
    ld high = sqrt(a * a + b * b);
    ld ans = low;
    while(high - low > epsilon) {
        ld mid = low + (high - low) / 2;
        if(isValid(a, b, mid)) {
            ans = max(ans, mid);
            low = mid;
        }
        else {
            high = mid;
        }
    }
    cout << fixed << setprecision(15) << ans << "\n";
    
    return 0;
}
