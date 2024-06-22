#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1979E

//I define a diamond of radius d around a point p as all the points that are distance d from p. (i call it a diamond
//because the points in question look like one)

//If we have some point A, and want to see if A is part of a triangle, first we need to find another point B that
//is on the diamond around A. Then, to see if there is a third point C that can form the triangle ABC, C can
//only be on the intersection between the A and B triangles, because the distance between A, B, and C must be
//equal to d. 

//First, to make the problem easier, we can just apply a 45 degree rotation to the entire plane, so now our diamonds
//are squares. 

//Second, the crucial observation to solving this problem is that in any valid triangle, two of the points must
//have the same x or y value (after we rotated everything 45 degrees). This can be seen by considering where
//the intersection points between two equal sized squares are, if the second square's center is on the edge of the 
//first square. 

//So, all we have to do is iterate through every row with a point in it, and for each point, we can look for some
//horizontally adjacent point distance d away. Then, the third point needs to be d above or below. 
//The same needs to be repeated for the vertical direction. 

vector<int> solve(map<int, set<int>>& rows, map<pair<int, int>, int>& ind_m, int d) {
    for(auto i = rows.begin(); i != rows.end(); i++){
        int y0 = i->first;
        for(auto j = rows[y0].begin(); j != rows[y0].end(); j++){
            int x0 = *j;
            int x1 = x0 + d;
            if(!rows[y0].count(x1)) {
                continue;
            }
            if(rows.count(y0 + d)) {
                int y1 = y0 + d;
                auto ptr = rows[y1].lower_bound(x0);
                if(ptr != rows[y1].end() && *ptr <= x1) {
                    return {ind_m[{x0, y0}], ind_m[{x1, y0}], ind_m[{*ptr, y1}]};
                }
            }
            if(rows.count(y0 - d)) {
                int y1 = y0 - d;
                auto ptr = rows[y1].lower_bound(x0);
                if(ptr != rows[y1].end() && *ptr <= x1) {
                    return {ind_m[{x0, y0}], ind_m[{x1, y0}], ind_m[{*ptr, y1}]};
                }
            }
        }
    }
    return {};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, d;
        cin >> n >> d;
        map<int, set<int>> hori, vert;
        map<pair<int, int>, int> hori_m, vert_m;
        for(int i = 0; i < n; i++){
            int _x, _y;
            cin >> _x >> _y;
            int x = _x + _y;
            int y = _x - _y;
            hori[y].insert(x);
            hori_m[{x, y}] = i + 1;
            vert[x].insert(y);
            vert_m[{y, x}] = i + 1;
        }
        vector<int> h_ans = solve(hori, hori_m, d);
        vector<int> v_ans = solve(vert, vert_m, d);
        if(h_ans.size() != 0){
            cout << h_ans[0] << " " << h_ans[1] << " " << h_ans[2] << "\n";
            continue;
        }
        if(v_ans.size() != 0){
            cout << v_ans[0] << " " << v_ans[1] << " " << v_ans[2] << "\n";
            continue;
        }
        cout << "0 0 0\n";
    }
    
    return 0;
}