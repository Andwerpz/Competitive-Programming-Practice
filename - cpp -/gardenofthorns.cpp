#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC NAQ 2023 - D

//by linearity of expectation, we can consider the expected value for each flower independently, then add them
//all up in the end. 

//for a given flower at position P, if the center of the circle of thorns is placed within R units of P, then
//the flower will be protected. 

//thus, the probability for the flower being protected is the amount of area that both the garden and the circle
//of radius R around P, divided by the total surface area of the garden. 

//now, given a circle and a rectangle, calculate the intersection area. 

ld PI = 3.1415926535897932384;

ld calc_cap_area_theta(ld theta, ld r){
    ld dist = r * cos(theta);
    ld x = sqrt(r * r - dist * dist);
    ld sector_area = 2.0 * theta * r;
    ld cap_area = sector_area - x * dist;
    return cap_area;
}

ld calc_cap_area(ld dist, ld r){
    if(dist < r){
        ld x = sqrt(r * r - dist * dist);
        ld theta = asin(x / r);
        ld sector_area = r * r * theta;
        ld cap_area = sector_area - x * dist;
        return cap_area;
    }
    return 0;
}

ld calc_cap_area_hchord_len(ld half_chord_len, ld r) {
    ld dist = sqrt(r * r - half_chord_len * half_chord_len);
    // cout << "CAP AREA HCHORD : " << dist << "\n";
    return calc_cap_area(dist, r);
}

ld calc_corner_area(ld dist_left, ld dist_bot, ld r) {
    // cout << "CALC CORNER AREA : " << dist_left << " " << dist_bot << "\n";
    ld x_left = sqrt(r * r - dist_left * dist_left);
    ld x_bot = sqrt(r * r - dist_bot * dist_bot);
    // cout << "X : " << x_left << " " << x_bot << "\n";
    ld a = x_left - dist_bot;
    ld b = x_bot - dist_left;
    if(a < 0 || b < 0 || isnan(a) || isnan(b)){
        return 0;
    }
    // cout << "A B : " << a << " " << b << "\n";
    ld tri_area = a * b / 2.0;
    ld half_chord_len = sqrt(a * a + b * b) / 2.0;
    ld cap_area = calc_cap_area_hchord_len(half_chord_len, r);
    // cout << "SUB AREA : " << tri_area << " " << cap_area << "\n";
    // cout << "CORNER AREA : " << tri_area + cap_area << "\n";
    return tri_area + cap_area;
}

//given circle with center at pos, radius r, how much overlap with rect w h. 
ld calc_overlap(pair<ld, ld>& pos, ld r, ld w, ld h) {
    ld ans = r * r * PI;
    //consider 4 sides
    {
        {
            ld dist = pos.first;
            ans -= calc_cap_area(dist, r);
        }    
        {
            ld dist = w - pos.first;
            ans -= calc_cap_area(dist, r);
        }
        {
            ld dist = pos.second;
            ans -= calc_cap_area(dist, r);
        }
        {
            ld dist = h - pos.second;
            ans -= calc_cap_area(dist, r);
        }
    }
    //correct overcounting
    {   
        ld dist_left = pos.first;
        ld dist_right = w - pos.first;
        ld dist_top = h - pos.second;
        ld dist_bot = pos.second;
        ans += calc_corner_area(dist_left, dist_top, r);
        ans += calc_corner_area(dist_right, dist_top, r);
        ans += calc_corner_area(dist_right, dist_bot, r);
        ans += calc_corner_area(dist_left, dist_bot, r);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ld r, w, h;
    cin >> n >> r >> w >> h;
    vector<pair<ld, ld>> a(n, {0, 0});
    vector<ld> v(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second >> v[i];
    }
    ld rect_area = w * h;
    ld ans = 0;
    for(int i = 0; i < n; i++){
        ld overlap = calc_overlap(a[i], r, w, h);
        ans += overlap / rect_area * v[i];
        // cout << "OVERLAP : " << overlap << "\n";
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}
