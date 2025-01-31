#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//USACO 2025 January Contest Gold 3

//this actually doesn't get AC, but the idea is there. 

map<int, int> ansm;
int X, Y;
set<array<int, 4>> seg;

ld dist(int x1, int y1, int x2, int y2) {
    return sqrt((ld) (x1 - x2) * (ld) (x1 - x2) + (ld) (y1 - y2) * (ld) (y1 - y2));
}

int calc_ans(int lx, int rx, int ly, int ry) {
    ld cans = 0;
    int sx = X, sy = Y;
    if(X < lx) cans += lx - X, sx = lx;
    else if(rx < X) cans += X - rx, sx = rx;
    if(Y < ly) cans += ly - Y, sy = ly;
    else if(ry < Y) cans += Y - ry, sy = ry;
    cans += dist(sx, 0, 0, sy);
    return (int) cans;
}

int calc_ans(array<int, 4> s) {
    return calc_ans(s[0], s[1], s[2], s[3]);
}

void insert_seg(array<int, 4> s) {
    if(seg.count(s)) return;
    seg.insert(s);
    int ans = calc_ans(s);
    ansm[ans] ++;
}

void erase_seg(array<int, 4> s){
    if(!seg.erase(s)) return;
    int ans = calc_ans(s);
    ansm[ans] --;
    if(ansm[ans] == 0) ansm.erase(ans);
}

void insert_seg(int x, int y){
    assert(seg.size() != 0);
    //find which segment x is a part of
    auto xptr = seg.lower_bound({x, -1, -1, -1});
    xptr --;
    auto yptr = xptr;
    vector<array<int, 4>> rm;
    rm.push_back(*xptr);
    bool down = false;
    while(y < (*yptr)[2]) {
        assert(yptr != seg.begin());
        down = true;
        yptr --;
        rm.push_back(*yptr);
    }
    while(!down && y > (*yptr)[3]) {
        assert((*yptr)[0] != (*seg.rbegin())[0]);
        yptr ++;
        rm.push_back(*yptr);
    }
    int xlx = (*xptr)[0], xrx = (*xptr)[1], xly = (*xptr)[2], xry = (*xptr)[3];
    int ylx = (*yptr)[0], yrx = (*yptr)[1], yly = (*yptr)[2], yry = (*yptr)[3];
    // cout << "SEG INSERT : " << x << " " << y << " " << endl;
    // cout << xlx << " " << xrx << " " << xly << " " << xry << endl;
    // cout << ylx << " " << yrx << " " << yly << " " << yry << endl;
    // cout << "RM : " << "\n";
    // for(array<int, 4> _ : rm) cout << _[0] << " " << _[1] << " " << _[2] << " " << _[3] << endl;
    for(array<int, 4> _ : rm) erase_seg(_);
    if(xlx == ylx){
        if(x > xlx) insert_seg({xlx, min(x, xrx), xly, y});
        if(x < xrx) insert_seg({max(x, xlx), xrx, y, xry});
    }
    else if(xlx > ylx) {
        insert_seg({max(x, xlx), xrx, xly, xry});
        insert_seg({ylx, yrx, yly, min(y, yry)});
    }
    else {  //xlx < ylx
        insert_seg({xlx, min(x, xrx), xly, xry});
        insert_seg({ylx, yrx, max(y, yly), yry});
    }
}

ld lfa(set<array<int, 4>>& seg, int X, int Y) {
    ld ans = 1e18;
    assert(seg.size() != 0);
    auto ptr = seg.upper_bound({X, 0, 0, 0});
    if(ptr == seg.end()) ptr --;
    for(int i = 0; i < 5; i++){
        auto tmp = ptr;
        tmp ++;
        if(tmp != seg.end()) ptr = tmp;
    }
    for(int j = 0; j < 10; j++){
        int lx = (*ptr)[0], rx = (*ptr)[1], ly = (*ptr)[2], ry = (*ptr)[3];
        ld cans = 0;
        int sx = X, sy = Y;
        if(X < lx) cans += lx - X, sx = lx;
        else if(rx < X) cans += X - rx, sx = rx;
        if(Y < ly) cans += ly - Y, sy = ly;
        else if(ry < Y) cans += Y - ry, sy = ry;
        cans += dist(sx, 0, 0, sy);
        // cout << "DIST : " << dist(sx, 0, 0, sy) << " " << sx << " " << sy << "\n";
        // cout << "TEST : " << lx << " " << rx << " " << ly << " " << ry << " " << cans << "\n";
        ans = min(ans, cans);
        if(ptr == seg.begin()) break;
        ptr --;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, t;
    cin >> n >> t;
    cin >> X >> Y;
    vector<array<int, 3>> s(n); //{s, x, y}
    for(int i = 0; i < n; i++){
        cin >> s[i][0] >> s[i][1] >> s[i][2];
    }
    insert_seg({0, (int) 1e8, 0, (int) 1e8});
    int sptr = 0;
    for(int i = 0; i < t; i++){
        while(sptr != n && s[sptr][0] <= i) {
            insert_seg(s[sptr][1], s[sptr][2]);
            sptr ++;
        }
        // cout << "SEG : " << endl;
        // for(auto j = segx.begin(); j != segx.end(); j++){
        //     array<int, 4> tmp = *j;
        //     cout << tmp[0] << " " << tmp[1] << " " << tmp[2] << " " << tmp[3] << endl;
        // }
        cout << ansm.begin()->first << "\n";
    }
    
    return 0;
}