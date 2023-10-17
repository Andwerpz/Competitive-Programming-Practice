#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1886B

//we can directly compute the answer for several cases, and just take the minimum out of all of them. 

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        vec2 start(0, 0);
        vec2 end, a, b;
        cin >> end.x >> end.y >> a.x >> a.y >> b.x >> b.y;
        ld ans = 1e9;
        ld start_a = length(sub(start, a));
        ld start_b = length(sub(start, b));
        ld end_a = length(sub(end, a));
        ld end_b = length(sub(end, b));
        ld a_b = length(sub(a, b));
        ans = min(ans, max(start_a, end_a));    //start and end contained within a
        ans = min(ans, max(start_b, end_b));    //start and end contained within b
        ans = min(ans, max(max(start_a, end_b), a_b / 2.0));  //start within a, end within b, a b touching
        ans = min(ans, max(max(start_b, end_a), a_b / 2.0));  //start within b, end within a, a b touching
        cout << fixed << setprecision(10) << ans << "\n";
    }
    
    return 0;
}
