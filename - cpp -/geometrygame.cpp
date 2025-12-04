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

// BAPC 2023 - G

//just some casework. Main thing is to observe that you don't actually need to compute angles to determine
//the type of shape. 

//square : all side lengths have to be equal, two diagonals have to be equal
//rectangle : opposite side lengths have to be equal, two diagonals have to be equal
//rhombus : all side lengths have to be equal
//parallelogram : opposite side lengths have to be equal
//trapezium : just have to check if some pair of opposing sides are parallel
//kite : two pairs of adjacent sides must be equal length

struct vec2 {
    ll x, y;
};

ll dist_sq(vec2 a, vec2 b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

vec2 sub(vec2 a, vec2 b) {
    return {a.x - b.x, a.y - b.y};
}

vec2 add(vec2 a, vec2 b) {
    return {a.x + b.x, a.y + b.y};
}

vec2 gred(vec2 a) {
    ll g = gcd(abs(a.x), abs(a.y));
    a.x /= g, a.y /= g;
    return a;
}

vec2 neg(vec2 a) {
    return {-a.x, -a.y};
}

bool equals(vec2 a, vec2 b) {
    return a.x == b.x && a.y == b.y;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    vector<vec2> a(4);
    for(int i = 0; i < 4; i++) cin >> a[i].x >> a[i].y;
    vl ssq(4);
    ssq[0] = dist_sq(a[0], a[1]);
    ssq[1] = dist_sq(a[1], a[2]);
    ssq[2] = dist_sq(a[2], a[3]);
    ssq[3] = dist_sq(a[3], a[0]);
    
    ll d1 = dist_sq(a[0], a[2]);
    ll d2 = dist_sq(a[1], a[3]);

    vector<vec2> s(4);
    s[0] = sub(a[1], a[0]);
    s[1] = sub(a[2], a[1]);
    s[2] = sub(a[3], a[2]);
    s[3] = sub(a[0], a[3]);

    if(ssq[0] == ssq[1] && ssq[1] == ssq[2] && ssq[2] == ssq[3] && d1 == d2) {
        cout << "square\n";
        return 0;
    }
    if(ssq[0] == ssq[2] && ssq[1] == ssq[3] && d1 == d2) {
        cout << "rectangle\n";
        return 0;
    }
    if(ssq[0] == ssq[1] && ssq[1] == ssq[2] && ssq[2] == ssq[3]) {
        cout << "rhombus\n";
        return 0;
    }
    if(ssq[0] == ssq[2] && ssq[1] == ssq[3]) {
        cout << "parallelogram\n";
        return 0;
    }

    {
        vec2 g0 = gred(s[0]);
        vec2 g1 = gred(s[1]);
        vec2 g2 = neg(gred(s[2]));
        vec2 g3 = neg(gred(s[3]));

        if(equals(g0, g2) || equals(g1, g3)) {
            cout << "trapezium\n";
            return 0;
        }
    }

    if((ssq[0] == ssq[1] && ssq[2] == ssq[3]) || (ssq[1] == ssq[2] && ssq[3] == ssq[0])){
        cout << "kite\n";
        return 0;
    }

    cout << "none\n";
    
    return 0;
}