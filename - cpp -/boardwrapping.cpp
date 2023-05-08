#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 13 B

//classic convex hull

struct pt {
    ld x, y;
};

pt rotateCCW(pt a, ld rad) {
    pt res;
    res.x = a.x * cos(rad) - a.y * sin(rad);
    res.y = a.x * sin(rad) + a.y * cos(rad);
    return res;
}

int orientation(pt a, pt b, pt c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool collinear(pt a, pt b, pt c) { return orientation(a, b, c) == 0; }

void convex_hull(vector<pt>& a, bool include_collinear = false) {
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0](const pt& a, const pt& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }

    vector<pt> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }

    a = st;
}

ld dist(pt a, pt b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

ld area(pt a, pt b, pt c) {
    ld sa = dist(a, b);
    ld sb = dist(b, c);
    ld sc = dist(c, a);
    ld s = (sa + sb + sc) / 2.0;
    return sqrt(s * (s - sa) * (s - sb) * (s - sc));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<pt> a(0);
        ld sArea = 0;
        for(int i = 0; i < n; i++){
            ld x, y, w, h, r;
            cin >> x >> y >> w >> h >> r;
            sArea += w * h;
            pt bl, tl, br, tr;
            bl.x = 0; bl.y = 0;
            tl.x = 0; tl.y = h;
            br.x = w; br.y = 0;
            tr.x = w; tr.y = h;
            r = -(r / 180.0) * 3.1415926;
            bl = rotateCCW(bl, r);
            tl = rotateCCW(tl, r);
            br = rotateCCW(br, r);
            tr = rotateCCW(tr, r);
            pt c;
            c.x = w / 2; c.y = h / 2;
            c = rotateCCW(c, r);
            ld xOff = x - c.x;
            ld yOff = y - c.y;
            bl.x += xOff; bl.y += yOff;
            tl.x += xOff; tl.y += yOff;
            br.x += xOff; br.y += yOff;
            tr.x += xOff; tr.y += yOff;
            a.push_back(bl);
            a.push_back(tl);
            a.push_back(br);
            a.push_back(tr);
        }
        convex_hull(a);
        ld tArea = 0;
        for(int i = 1; i < a.size() - 1; i++){
            tArea += area(a[0], a[i], a[i + 1]);
        }
        ld ans = sArea / tArea;
        ans *= 100;
        cout << fixed << setprecision(1) << ans << " %\n";
    }
    
    return 0;
}
