#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pdd;
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

//2024 ICPC NAQ - F

//we need to find the minimum and maximum x and y coordinates from any point on the ellipse. 

//if we can check if a given horizontal or vertical line intersects the ellipse, then we can
//just do binary search. 

//to check if a horizontal line intersects with the ellipse, can just do ternary search. 

pdd f1, f2;
ld fc;

ld dist(pdd a, pdd b){
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

ld e_val(pdd x) {
    return dist(f1, x) + dist(f2, x) - fc;
}

ld lerp(ld x0, ld t0, ld x1, ld t1, ld t) {
    return x0 + (x1 - x0) * ((t - t0) / (t1 - t0));
}

pdd lerp(pdd x0, ld t0, pdd x1, ld t1, ld t) {
    return {lerp(x0.first, t0, x1.first, t1, t), lerp(x0.second, t0, x1.second, t1, t)};
}

bool vert_eint(ld x) {
    ld low = -1000;
    ld high = 1000;
    ld epsilon = 1e-11;
    while(high - low > epsilon) {
        ld m0 = low + (high - low) * (1.0 / 3.0);
        ld m1 = low + (high - low) * (2.0 / 3.0);
        ld v0 = e_val({x, m0});
        ld v1 = e_val({x, m1});
        if(v0 < v1) {
            high = m1;
        }
        else {
            low = m0;
        }
    }
    return e_val({x, low}) < 0;
}

bool horiz_eint(ld y) {
    ld low = -1000;
    ld high = 1000;
    ld epsilon = 1e-11;
    while(high - low > epsilon) {
        ld m0 = low + (high - low) * (1.0 / 3.0);
        ld m1 = low + (high - low) * (2.0 / 3.0);
        ld v0 = e_val({m0, y});
        ld v1 = e_val({m1, y});
        if(v0 < v1) {
            high = m1;
        }
        else {
            low = m0;
        }
    }
    return e_val({low, y}) < 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> f1.first >> f1.second >> f2.first >> f2.second >> fc;
    pdd center = lerp(f1, 0, f2, 1, 0.5);
    ld epsilon = 1e-9;
    //xlow
    {
        ld low = -1000;
        ld high = center.first;
        while(high - low > epsilon) {
            ld mid = low + (high - low) / 2;
            if(vert_eint(mid)) {
                high = mid;
            }
            else {
                low = mid;
            }
        }
        cout << fixed << setprecision(10) << low << " ";
    }
    //ylow
    {
        ld low = -1000;
        ld high = center.second;
        while(high - low > epsilon) {
            ld mid = low + (high - low) / 2;
            if(horiz_eint(mid)) {
                high = mid;
            }
            else {
                low = mid;
            }
        }
        cout << fixed << setprecision(10) << low << " ";
    }
    //xhigh
    {
        ld low = center.first;
        ld high = 1000;
        while(high - low > epsilon) {
            ld mid = low + (high - low) / 2;
            if(vert_eint(mid)) {
                low = mid;
            }
            else {
                high = mid;
            }
        }
        cout << fixed << setprecision(10) << low << " ";
    }
    //yhigh
    {
        ld low = center.second;
        ld high = 1000;
        while(high - low > epsilon) {
            ld mid = low + (high - low) / 2;
            if(horiz_eint(mid)) {
                low = mid;
            }
            else {
                high = mid;
            }
        }
        cout << fixed << setprecision(10) << low << " ";
    }
    cout << "\n";
    
    return 0;
}