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

//NCPC 2024 - A

//just a bunch of casework. To make it easier, you can flip it s.t. xs <= xt and ys <= yt, and solve from there. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    bool xflip = false, yflip = false;
    int xs, ys, xt, yt, xp, yp;
    cin >> xs >> ys >> xt >> yt >> xp >> yp;
    if(xs > xt) {
        xflip = true;
        xs *= -1;
        xt *= -1;
        xp *= -1;
    }
    if(ys > yt) {
        yflip = true;
        ys *= -1;
        yt *= -1;
        yp *= -1;
    }
    bool xcont = xs < xp && xp < xt;
    bool ycont = ys < yp && yp < yt;
    vector<pii> ans(0);
    if(xp <= xs && yp <= ys) {
        //go direct
        ans.push_back({xt, ys});
    }
    else if(xp <= xs && yp >= yt) {
        ans.push_back({xt, ys});
    }
    else if(xp >= xt && yp <= ys) {
        ans.push_back({xs, yt});
    }
    else if(xcont && ycont) {
        ans.push_back({xs, -1e8});
        ans.push_back({1e8, -1e8});
        ans.push_back({1e8, yt});
    }
    else if(ycont) {
        if(xp <= xs) {
            ans.push_back({1e8, ys});
            ans.push_back({1e8, yt});
        }
        else {
            ans.push_back({-1e8, ys});
            ans.push_back({-1e8, yt});
        }
    }
    else {
        if(yp <= ys) {
            ans.push_back({xs, 1e8});
            ans.push_back({xt, 1e8});
        }
        else {
            ans.push_back({xs, -1e8});
            ans.push_back({xt, -1e8});
        }
    }
    // cout << "XY FLIP : " << xflip << " " << yflip << "\n";
    if(xflip) {
        for(pii& x : ans){
            x.first *= -1;
        }
    }
    if(yflip){
        for(pii& x : ans) {
            x.second *= -1;
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    
    return 0;
}