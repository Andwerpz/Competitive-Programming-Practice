#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals B

//lets say that for each segment, we can query in O(1) time whether or not we can build an arch over it. 
//then, the solution would just be an n^2 dp to find the minimum cost. 

//in order to support these queries, we must do some precomputation. 

//for each key point, figure out the maximum diameter of half-arch we can build to the left and to the right. 
//to do this, we can independently query each point to the left and right, and see what is the maximum
//diameter before the half arch will intersect with the ground at that key point.

//then, to check if we can build an arch between two key points, we just need to make sure the maximum diameter half arch 
//for both the left and right key points is greater than the diameter required. 

ld distSq(pair<ld, ld> a, pair<ld, ld> b) {
    return pow(abs(a.first - b.first), 2) + pow(abs(a.second - b.second), 2);
}

pair<ld, ld> sub(pair<ld, ld> a, pair<ld, ld> b) {
    return {a.first - b.first, a.second - b.second};
}

pair<ld, ld> add(pair<ld, ld> a, pair<ld, ld> b) {
    return {a.first + b.first, a.second + b.second};
}

pair<ld, ld> mul(pair<ld, ld> a, ld s) {
    return {a.first * s, a.second * s};
}

ld dot(pair<ld, ld> a, pair<ld, ld> b) {
    return a.first * b.first + a.second * b.second;
}

ld length(pair<ld, ld> a){
    return sqrt(pow(a.first, 2) + pow(a.second, 2));
}

pair<ld, ld> normalize(pair<ld, ld> a) {
    ld len = length(a);
    return {a.first / len, a.second / len};
}

//returns the distance along the ray from ray_a to the nearest point on the circle. 
ld rayCircleDist(pair<ld, ld>& ray_a, pair<ld, ld>& ray_b, pair<ld, ld>& center, ld radius) {
    //cout << "RAY CIRCLE DIST : " << center.first << " " << center.second << " " << radius << "\n";
    //cout << "RAY : " << "(" << ray_a.first << ", " << ray_a.second << ") (" << ray_b.first << ", " << ray_b.second << ")" << "\n";
    pair<ld, ld> ray_dir = normalize(sub(ray_b, ray_a));
    pair<ld, ld> to_center = sub(center, ray_a);
    pair<ld, ld> center_proj = add(ray_a, mul(ray_dir, dot(ray_dir, to_center)));
    ld center_proj_len = length(sub(center, center_proj));
    //cout << dot(ray_dir, to_center) << "\n";
    //cout << "(" << center_proj.first << ", " << center_proj.second << ")" << "\n";
    //cout << center_proj_len << "\n";
    //radius^2 = center_proj_len^2 + int_depth^2
    //int_depth = sqrt(radius^2 - center_proj_len^2)
    ld int_depth = sqrt(radius * radius - center_proj_len * center_proj_len);
    return dot(ray_dir, to_center) - int_depth;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ll h, a, b;
    cin >> n >> h >> a >> b;
    vector<pair<ll, ll>> gint(n, {0, 0});
    vector<pair<ld, ld>> ground(n, {0, 0});
    for(int i = 0; i < n; i++){
        cin >> gint[i].first >> gint[i].second;
        ground[i].first = gint[i].first;
        ground[i].second = gint[i].second;
    }
    vector<ld> max_rd(n, 0);
    vector<ld> max_ld(n, 0);
    //maximum diameter to the left
    for(int i = 0; i < n; i++){
        max_ld[i] = (h - ground[i].second) * 2;
        pair<ld, ld> corner = {ground[i].first, h};
        for(int j = i - 1; j >= 0; j--){
            ld radius = max_ld[i] / 2;
            pair<ld, ld> center = {corner.first - radius, corner.second - radius};
            ld circleDist = rayCircleDist(corner, ground[j], center, radius);
            ld groundDist = length(sub(ground[j], corner));
            ld maxDiameter = (groundDist / circleDist) * max_ld[i];
            max_ld[i] = min(max_ld[i], maxDiameter);
        }
    }
    //maximum diameter to the right
    for(int i = 0; i < n; i++){
        //cout << "MAX RIGHT DIAMETER : " << i << "\n";
        max_rd[i] = (h - ground[i].second) * 2;
        pair<ld, ld> corner = {ground[i].first, h};
        for(int j = i + 1; j < n; j++){
            //cout << "CHECKING J : " << j << "\n";
            ld radius = max_rd[i] / 2;
            pair<ld, ld> center = {corner.first + radius, corner.second - radius};
            ld circleDist = rayCircleDist(corner, ground[j], center, radius);
            ld groundDist = length(sub(ground[j], corner));
            ld maxDiameter = (groundDist / circleDist) * max_rd[i];
            max_rd[i] = min(max_rd[i], maxDiameter);
            //cout << circleDist << " " << groundDist << " " << maxDiameter << "\n";
        }
    }
    vector<vector<bool>> valid(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            ld diameter = ground[j].first - ground[i].first;
            diameter -= 1e-9;
            valid[i][j] = max_rd[i] > diameter && max_ld[j] > diameter;
        }
    }
    // for(int i = 0; i < n; i++){
    //     cout << max_ld[i] << " ";
    // }
    // cout << "\n";
    // for(int i = 0; i < n; i++){
    //     cout << max_rd[i] << " ";
    // }
    // cout << "\n";
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         cout << valid[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    ll unv = 1e18;
    vector<ll> dp(n, unv);
    dp[0] = (h - gint[0].second) * a;
    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(dp[j] == unv) {
                continue;
            }
            if(!valid[j][i]) {
                continue;
            }
            ll diameter = gint[i].first - gint[j].first;
            ll pillar = h - gint[i].second;
            dp[i] = min(dp[i], dp[j] + pillar * a + diameter * diameter * b);
        }
        //cout << dp[i] << "\n";
    }
    if(dp[n - 1] == unv) {
        cout << "impossible\n";
    }
    else {
        cout << dp[n - 1] << "\n";
    }
    
    return 0;
}
