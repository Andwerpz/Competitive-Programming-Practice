#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
typedef array<ld, 2> vec2;

//ICPC NA East 2024 - E

//let's remove the constraint that the two triangles containing the brothers must be separated by exactly
//1 triangle. Then, this problem is just finding the triangle partition that minimizes the sum of added
//side lengths. Note that since the given shape is a convex polygon, we can directly connect any vertex to
//any other vertex. 

//We can use dp to solve this. dp[l][r] is the minimum cost to partition the vertices in range [l, r]. 
//Note that we enumerate the nodes clockwise, and so when l < r, we really mean the union of ranges [l, n] and 
//[0, r]. 

//transitions are not too hard. The edge going from node l to r must be part of a triangle, so we can iterate through
//all nodes k, l < k < r, that can be the third vertex of the triangle. Then, the range will be split up into
//subranges [l, k] and [k, r] which we must solve. 

//We can reincorporate the brothers into our solution by iterating over the triangle which is going to be 
//in between the brothers. The only constraint on this triangle is that it has to be directly touching both of
//the brothers triangles, and this also guarantees that the brothers triangles are not directly touching. 

//To find the minimum cost given some middle triangle, we can precompute for each [l, r] the minimum cost given
//that it contains some brother b0 or b1 in the triangle that is touching edge l -> r. This can be done while
//doing the main dp. 

//Since our solution is O(n^3) and n = 500, we'll have to make sure our constant factor is not bad. Specifically,
//we can't be doing a bunch of expensive geometry stuff n^3 times. We can precompute in O(n^2 * log(n)) expensive
//geometry calculations what triangles contain the brothers, and that should be enough to not TLE. 

ld epsilon = 1e-10;

ll dist_sq(vec2 v0, vec2 v1) {return pow(v0[0] - v1[0], 2) + pow(v0[1] - v1[1], 2);}
ld dist(vec2 v0, vec2 v1) {
    return sqrt(dist_sq(v0, v1));
}

bool pt_on_line(vec2 v0, vec2 v1, vec2 pt) {
    return abs(dist(v0, v1) - dist(v0, pt) - dist(v1, pt)) < epsilon;
}

vec2 sub(vec2 v0, vec2 v1) {
    return {v0[0] - v1[0], v0[1] - v1[1]};
}

vec2 add(vec2 v0, vec2 v1) {
    return {v0[0] + v1[0], v0[1] + v1[1]};
}

ld cross(vec2 a, vec2 b) {
    return a[0] * b[1] - a[1] * b[0];
}

ld tri_area(vec2 v0, vec2 v1, vec2 v2) {
    vec2 a = sub(v1, v0), b = sub(v2, v0);
    return abs(cross(a, b) / 2.0);
}

bool pt_in_tri(vec2 v0, vec2 v1, vec2 v2, vec2 pt) {
    v0 = sub(v0, pt), v1 = sub(v1, pt), v2 = sub(v2, pt);
    vec2 orig = {0, 0};
    ld area = tri_area(v0, v1, v2);
    ld test = tri_area(orig, v0, v1) + tri_area(orig, v1, v2) + tri_area(orig, v2, v0);
    return abs(area - test) < epsilon;
}

ld dot(vec2 a, vec2 b){
    return a[0] * b[0] + a[1] * b[1];
}

bool same_side(vec2 v0, vec2 v1, vec2 a, vec2 b) {
    vec2 dir = sub(v1, v0);
    vec2 perp = {-dir[1], dir[0]};
    return dot(perp, sub(v0, a)) * dot(perp, sub(v0, b)) >= 0.0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vec2> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i][0] >> a[i][1];
    }
    vec2 b0, b1;
    cin >> b0[0] >> b0[1] >> b1[0] >> b1[1];
    vector<vector<bool>> legal(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++){
        for(int j = 1; j < n - 1; j++){
            if(!pt_on_line(a[i], a[(i + j) % n], b0) && !pt_on_line(a[i], a[(i + j) % n], b1)) legal[i][(i + j) % n] = true;
        }
    }
    //for segment [l, r] what selection of k contains the brother?
    //the valid k that can be picked should form a contiguous segment
    vector<vector<vector<bool>>> c0(n, vector<vector<bool>>(n, vector<bool>(n, false)));
    vector<vector<vector<bool>>> c1(n, vector<vector<bool>>(n, vector<bool>(n, false)));
    for(int i = 0; i < n; i++){
        for(int j = i + 2; j % n != i; j++){
            int l = i, r = j % n;
            int c0_mn = j, c0_mx = l;
            int c1_mn = j, c1_mx = l;
            if(same_side(a[l], a[r], a[(l + 1) % n], b0)) {
                //find min
                {
                    int low = l + 1, high = j - 1;
                    while(low <= high) {
                        int mid = low + (high - low) / 2;
                        if(same_side(a[r], a[mid % n], a[l], b0)) c0_mn = mid, high = mid - 1;
                        else low = mid + 1;
                    }
                }
                //find max
                {   
                    int low = l + 1, high = j - 1;
                    while(low <= high) {
                        int mid = low + (high - low) / 2;
                        if(same_side(a[l], a[mid % n], a[r], b0)) c0_mx = mid, low = mid + 1;
                        else high = mid - 1;
                    }
                }
            }
            if(same_side(a[l], a[r], a[(l + 1) % n], b1)) {
                //find min
                {
                    int low = l + 1, high = j - 1;
                    while(low <= high) {
                        int mid = low + (high - low) / 2;
                        if(same_side(a[r], a[mid % n], a[l], b1)) c1_mn = mid, high = mid - 1;
                        else low = mid + 1;
                    }
                }
                //find max
                {   
                    int low = l + 1, high = j - 1;
                    while(low <= high) {
                        int mid = low + (high - low) / 2;
                        if(same_side(a[l], a[mid % n], a[r], b1)) c1_mx = mid, low = mid + 1;
                        else high = mid - 1;
                    }
                }
            }
            for(int k = c0_mn; k <= c0_mx; k++) c0[l][r][k % n] = true;
            for(int k = c1_mn; k <= c1_mx; k++) c1[l][r][k % n] = true;
        }
    }
    vector<vector<ld>> dst(n, vector<ld>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) dst[i][j] = dist(a[i], a[j]);
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(legal[i][j]) legal[j][i] = true;
        }
    }
    vector<vector<ld>> dpa(n, vector<ld>(n, 1e18)), dpb(n, vector<ld>(n, 1e18));
    vector<vector<ld>> dp(n, vector<ld>(n, 1e18));  //inclusive
    //base case
    for(int i = 0; i < n; i++) {
        dp[i][(i + 1) % n] = 0;
    }
    for(int i = 2; i < n; i++) {
        for(int j = 0; j < n; j++){
            int l = j, _r = j + i, r = _r % n;
            for(int _k = l + 1; _k < _r; _k++){
                int k = _k % n;
                if(!legal[l][k] || !legal[k][r]) continue;
                ld cval = dp[l][k] + dp[k][r] + dst[l][k] + dst[k][r];
                dp[l][r] = min(dp[l][r], cval);
                if(c0[l][r][k]) dpa[l][r] = min(dpa[l][r], cval);
                if(c1[l][r][k]) dpb[l][r] = min(dpb[l][r], cval);
            }
        }
    }
    ld edge_amt = 0;
    for(int i = 0; i < n; i++) edge_amt += dst[i][(i + 1) % n];
    ld ans = 1e18;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; (j + 1) % n != i; j++){
            for(int k = j + 1; k % n != i; k++){
                int ia = i, ib = j % n, ic = k % n;
                if(!legal[ia][ib] || !legal[ib][ic] || !legal[ic][ia]) continue;
                ld cans = min(dpa[ia][ib] + dpb[ib][ic] + dp[ic][ia], dpb[ia][ib] + dpa[ib][ic] + dp[ic][ia]) + dst[ia][ib] + dst[ib][ic] + dst[ic][ia];
                ans = min(ans, cans);
            }
        }
    }
    if(ans == 1e18) cout << "IMPOSSIBLE\n";
    else cout << fixed << setprecision(10) << ans - edge_amt << "\n";

    return 0;
}