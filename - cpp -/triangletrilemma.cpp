#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - trilemma

//just a bunch of casework. 

struct vec2 {
    int x, y;
    vec2() {}
    vec2(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

vec2 sub(vec2 a, vec2 b) {
    return vec2(a.x - b.x, a.y - b.y);
}

vec2 add(vec2 a, vec2 b) {
    return vec2(a.x + b.x, a.y + b.y);
}

int dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

int cross(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}

ld calc_angl(vec2 a, vec2 b, vec2 c) {
    vec2 ba = sub(a, b);
    vec2 bc = sub(c, b);
    return acos((ld) dot(ba, bc) / (ld) sqrt((ld) dot(ba, ba)) / sqrt((ld) dot(bc, bc)));
}

vector<ld> get_angl(vec2 a, vec2 b, vec2 c) {
    return {
        calc_angl(c, a, b),
        calc_angl(a, b, c),
        calc_angl(b, c, a),
    };
}

bool is_iso(vec2 a, vec2 b, vec2 c) {
    vec2 ab = sub(b, a);
    vec2 bc = sub(c, b);
    vec2 ca = sub(a, c);
    if(dot(ab, ab) == dot(bc, bc) || dot(bc, bc) == dot(ca, ca) || dot(ca, ca) == dot(ab, ab)) {
        return true;
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    int casi = 0;
    while(t--){
        casi ++;
        cout << "Case #" << casi << ": ";
        vec2 a, b, c;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        vec2 ab = sub(b, a);
        vec2 ac = sub(c, a);
        //check if degenerate
        if(cross(ab, ac) == 0){
            cout << "not a triangle" << "\n";
            continue;
        }
        vector<ld> angl = get_angl(a, b, c);
        ld epsilon = 1e-9;
        ld maxa = 0;
        ld pi = acos(-1);
        for(int i = 0; i < 3; i++){
            maxa = max(maxa, angl[i]);
        }
        cout << (is_iso(a, b, c)? "isosceles" : "scalene") << " ";
        if(abs((pi / 2.0) - maxa) <= epsilon) {
            cout << "right triangle\n";
        }
        else if(maxa < pi / 2.0){
            cout << "acute triangle\n";
        }
        else {
            cout << "obtuse triangle\n";
        }
    }
    
    return 0;
}
