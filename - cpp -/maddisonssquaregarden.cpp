#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//University of Alberta Programming Contest 2023 E

//binary search the size of the garden. 

//the hard part is calculating the time taken to travel across the square given the size of the garden. 
//use line segment intersection algorithm to do so. 

pair<ld, ld> sub(pair<ld, ld> a, pair<ld, ld> b) {
    return {a.first - b.first, a.second - b.second};
}

ld cross(pair<ld, ld> a, pair<ld, ld> b) {
    return a.first * b.second - a.second * b.first;
}

pair<ld, ld> intersect(pair<ld, ld> a1, pair<ld, ld> a2, pair<ld, ld> b1, pair<ld, ld> b2) {
    pair<ld, ld> adir = sub(a2, a1);
    pair<ld, ld> bdir = sub(b2, b1);
    //cout << "adir: " << adir.first << " " << adir.second << "\n";
    //cout << "bdir: " << bdir.first << " " << bdir.second << "\n";
    ld t = cross(sub(a1, b1), bdir) / cross(bdir, adir);
    ld u = cross(sub(b1, a1), adir) / cross(adir, bdir);
    //cout << t << "\n";
    if(t < 0 || t > 1 || u < 0 || u > 1){
        return {-1, -1};
    }
    return {a1.first + adir.first * t, a1.second + adir.second * t};
}

ld dist(pair<ld, ld> a, pair<ld, ld> b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

bool isValid(vector<pair<ld, ld>>& a, vector<pair<ld, ld>>& b, vector<ld>& time, ld r, ld val) {
    //cout << "VAL: " <<  val << "\n";
    pair<ld, ld> tr = {0.5 + val / 2, 0.5 + val / 2};
    pair<ld, ld> tl = {0.5 - val / 2, 0.5 + val / 2};
    pair<ld, ld> br = {0.5 + val / 2, 0.5 - val / 2};
    pair<ld, ld> bl = {0.5 - val / 2, 0.5 - val / 2};
    for(int i = 0; i < a.size(); i++){
        vector<pair<ld, ld>> tmp(0);
        tmp.push_back(intersect(a[i], b[i], tr, tl));
        tmp.push_back(intersect(a[i], b[i], br, bl));
        tmp.push_back(intersect(a[i], b[i], tr, br));
        tmp.push_back(intersect(a[i], b[i], tl, bl));
        vector<pair<ld, ld>> inter(0);
        for(int j = 0; j < 4; j++){
            if(tmp[j].first == -1) {
                continue;
            }
            //cout << tmp[j].first << " " << tmp[j].second << "\n";
            inter.push_back(tmp[j]);
        }
        ld thruNot = dist(a[i], b[i]);
        ld thruGarden = 0;
        if(inter.size() == 2){
            thruGarden = dist(inter[0], inter[1]);
        }
        else if(inter.size() > 2){
            thruGarden = max(dist(inter[0], inter[1]), dist(inter[0], inter[2]));
        }
        thruNot -= thruGarden;
        ld t = thruNot / 0.1 + thruGarden / (0.1 * r);
        if(t > time[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ld r;
    cin >> n >> r;
    vector<pair<ld, ld>> a(n, {0, 0});
    vector<pair<ld, ld>> b(n, {0, 0});
    vector<ld> t(n, 0);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second >> b[i].first >> b[i].second >> t[i];
    }
    ld low = 0;
    ld high = 1;
    ld mid = low + (high - low) / 2;
    ld ans = low;
    while(high - low > 0.00000001) {
        if(isValid(a, b, t, r, mid)) {
            ans = max(ans, mid);
            low = mid;
        }
        else {
            high = mid;
        }
        mid = low + (high - low) / 2;
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}
