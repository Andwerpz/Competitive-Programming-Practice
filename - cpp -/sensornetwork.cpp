#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC Finals 2014

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

ld epsilon = 1e-11;

vector<int>* contain(vec2 p, ld d, vector<vec2>& a) {
    //cout << "TESTING : " << p.x << " " << p.y << "\n";
    vector<int>* ret = new vector<int>(0, 0);
    for(int i = 0; i < a.size(); i++){
        vec2 v = sub(p, a[i]);
        if(length(v) < d + epsilon) {
            ret->push_back(i);
        }
    }
    return ret;
}

vector<int>* solve(int ia, int ib, vector<vec2>& a, ld d) {
    vec2 pa = a[ia];
    vec2 pb = a[ib];
    vec2 diff = sub(pa, pb);
    if(length(diff) < epsilon) {
        return contain(pa, d, a);
    }
    diff = mul(diff, 1.0 / 2.0);
    vec2 inter = add(pb, diff);
    ld difflen = length(diff);
    vec2 perp = vec2(-diff.y, diff.x);
    ld len = sqrt(d * d - difflen * difflen);
    perp = mul(normalize(perp), len);
    vec2 ta = add(inter, perp);
    vec2 tb = add(inter, mul(perp, -1));
    vec2 tdiff = sub(tb, ta);
    ld nr = 10;
    tdiff = mul(tdiff, 1.0 / nr);
    vector<int>* ret = new vector<int>(1, 0);
    for(int i = 0; i < (int) nr; i++){
        vector<int>* ans = contain(ta, d, a);
        if(ret->size() < ans->size()) {
            swap(ans, ret);
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    ld d; cin >> d;
    d /= 2;
    vector<vec2> a(n, vec2());
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
    }
    vector<int>* ans = new vector<int>(1, 0);
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            vector<int>* ret = solve(i, j, a, d);
            if(ret->size() > ans->size()) {
                swap(ret, ans);
            }
        }
    }
    cout << ans->size() << "\n";
    for(int i = 0; i < ans->size(); i++){
        cout << (*ans)[i] + 1 << " \n"[i == ans->size() - 1];
    }
    
    return 0;
}
