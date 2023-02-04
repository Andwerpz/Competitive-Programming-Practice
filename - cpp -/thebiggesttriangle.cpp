#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//RMRC 2019 Practice H

//all you need to do is loop through all triples of lines. 

//the hard part is coming up with the line - line intersection algorithm. 

void normalize(pair<double, double>& a) {
    double length = sqrt(a.first * a.first + a.second * a.second);
    a.first /= length;
    a.second /= length;
}

double length(pair<double, double> a) {
    return sqrt(a.first * a.first + a.second * a.second);
}

pair<double, double> sub(pair<double, double> a, pair<double, double> b) {
    return {a.first - b.first, a.second - b.second};
}

pair<double, double> add(pair<double, double> a, pair<double, double> b) {
    return {a.first + b.first, a.second + b.second};
}

double dot(pair<double, double> a, pair<double, double> b) {
    return a.first * b.first + a.second * b.second;
}

pair<double, double> mul(pair<double, double> a, double val) {
    return {a.first * val, a.second * val};
}

double cross(pair<double, double> a, pair<double, double> b) {
    return a.first * b.second - a.second * b.first;
}

pair<double, double> getRayIntersect(pair<double, double> aOrigin, pair<double, double> aDir, pair<double, double> bOrigin, pair<double, double> bDir) {
    double t = cross(sub(bOrigin, aOrigin), bDir) / cross(aDir, bDir);
    return add(aOrigin, mul(aDir, t));
}

int gcd(int a, int b) {
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

bool isParallel(int d1x, int d1y, int d2x, int d2y) {
    int g1 = gcd(d1x, d1y);
    int g2 = gcd(d2x, d2y);
    d1x /= g1;
    d1y /= g1;
    d2x /= g2;
    d2y /= g2;
    return d1x == d2x && d1y == d2y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(4));
    for(int i = 0; i < n; i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        a[i][0] = x1 + 10001;
        a[i][1] = y1 + 10001;
        a[i][2] = x2 + 10001;
        a[i][3] = y2 + 10001;
    }
    double ans = 0;
    bool found = false;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++) {
            for(int k = j + 1; k < n; k++){
                int a1x, a1y, b1x, b1y, c1x, c1y;
                int a2x, a2y, b2x, b2y, c2x, c2y;
                a1x = a[i][0];
                a1y = a[i][1];
                a2x = a[i][2];
                a2y = a[i][3];
                b1x = a[j][0];
                b1y = a[j][1];
                b2x = a[j][2];
                b2y = a[j][3];
                c1x = a[k][0];
                c1y = a[k][1];
                c2x = a[k][2];
                c2y = a[k][3];
                if(isParallel(a1x - a2x, a1y - a2y, b1x - b2x, b1y - b2y) || 
                isParallel(b1x - b2x, b1y - b2y, c1x - c2x, c1y - c2y) || 
                isParallel(c1x - c2x, c1y - c2y, a1x - a2x, a1y - a2y)) {
                    continue;
                }
                //cout << a1x << " " << a1y << " " << b1x << " " << b1y << "\n";
                pair<double, double> a = getRayIntersect({a1x, a1y}, {a2x - a1x, a2y - a1y}, {b1x, b1y}, {b2x - b1x, b2y - b1y});
                pair<double, double> b = getRayIntersect({b1x, b1y}, {b2x - b1x, b2y - b1y}, {c1x, c1y}, {c2x - c1x, c2y - c1y});
                pair<double, double> c = getRayIntersect({c1x, c1y}, {c2x - c1x, c2y - c1y}, {a1x, a1y}, {a2x - a1x, a2y - a1y});
                double next = length(sub(a, b)) + length(sub(b, c)) + length(sub(c, a));
                ans = max(ans, next);
                found = true;
            }
        }
    }
    if(!found || ans < 0.0001) {
        cout << "no triangle\n";
    }
    else {
        cout << fixed << setprecision(6) << ans << "\n";
    }
    
    return 0;
}
