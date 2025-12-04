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

//Kattis - sneakattack

//can reinterpret the mirror as viewing through a 'portal'. However, instead of reflecting the entire wall
//through the mirror, we can just reflect the viewing position through the mirror. 

//ok, so now we have a window that we can look through, we just need to find the amount of the wall that we can see. 
//observe first that since our viewing angle is restricted to strictly less than 180 deg, we can never see 
//the entire wall at once (we can never print pos and neg infinity). So if we test the intersection points
//on the edges of our window, being able to see the wall implies that at least one of our window 
//edges must be on the wall. 

//if both edges are on the wall, then that case is easy. 
//if both edges are not on the wall, we can't see any of it
//otherwise, one edge is on the wall, and one edge is off the wall. We just need to figure out in which 
//infinite direction can we see. This can be resolved by just considering the direction in which the window
//is facing. If it's facing up, then we can see in the +infinity direction.

struct vec2 {
    ld x, y;
};

vec2 add(vec2 a, vec2 b) {
    return {a.x + b.x, a.y + b.y};
}

vec2 sub(vec2 a, vec2 b) {
    return {a.x - b.x, a.y - b.y};
}

vec2 mul(vec2 a, ld s) {
    return {a.x * s, a.y * s};
}

ld dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

ld length_sq(vec2 a) {
    return a.x * a.x + a.y * a.y;
}

ld length(vec2 a) {
    return sqrt(length_sq(a));
}

vec2 normalize(vec2 a) {
    return mul(a, 1.0 / length(a));
}

vec2 proj(vec2 l1, vec2 l2, vec2 pt) {
    vec2 dir = normalize(sub(l2, l1));
    vec2 pt_l2 = sub(l2, pt);
    vec2 pt_l2_tang = mul(dir, dot(dir, pt_l2));
    return add(pt, sub(pt_l2, pt_l2_tang));
}

vec2 mirror(vec2 l1, vec2 l2, vec2 pt) {
    vec2 pr = proj(l1, l2, pt);
    return add(pr, sub(pr, pt));
}

// {flag, y}
// flag = 0, found intersection
// flag = 1, doesn't hit yaxis, towards +infinity
// flag = -1, doesn't hit yaxis, towards -infinity
pair<int, ld> int_yaxis(vec2 l1, vec2 dir) {
    if(l1.x < 0) {
        l1.x *= -1;
        dir.x *= -1;
    }
    if(dir.x >= 0) {
        if(dir.y >= 0) return {1, 0};
        else return {-1, 0};
    }
    return {0, l1.y + l1.x / (-dir.x) * dir.y};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    while(true) {
        vec2 m1, m2, vp;
        cin >> m1.x >> m1.y >> m2.x >> m2.y >> vp.x >> vp.y;
        if(cin.eof()) break;
        //mirror viewing point across mirror
        vp = mirror(m1, m2, vp);
        //get intersection points of ray of viewing point to mirror ends on wall
        pair<int, ld> i1 = int_yaxis(m1, sub(m1, vp));
        pair<int, ld> i2 = int_yaxis(m2, sub(m2, vp));
        if(i1 > i2) swap(i1, i2);
        //casework
        if(i1.first != 0 && i2.first != 0) {
            cout << "can't hit the wall\n";
        }
        else if((i1.first == 0) ^ (i2.first == 0)) {
            ld ypos;
            if(i1.first == 0) ypos = i1.second;
            else if(i2.first == 0) ypos = i2.second;
            vec2 pr = proj(m1, m2, vp);
            vec2 mdir = sub(pr, vp);
            if(mdir.y >= 0) cout << fixed << setprecision(10) << ypos << " positive-infinity\n";
            else cout << fixed << setprecision(10) << "negative-infinity " << ypos << "\n";
        }
        else if(i1.first == 0 && i2.first == 0) {
            cout << fixed << setprecision(10) << i1.second << " " << i2.second << "\n";
        }
    }
    
    return 0;
}