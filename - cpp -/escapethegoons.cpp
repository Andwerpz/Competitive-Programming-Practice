#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//ACPC 2024 Spring Contest - E

//permanently go upwards, and if you encounter a goon, just try to encircle them. 
//if it's possible to encircle them, you can just remove them and continue. Otherwise, you've been encircled.

//to determine if you've been encircled, you can just see if you make a clockwise or counterclockwise
//turn when going around them. 

set<pair<int, int>> goons;
bool isgoon(int x, int y) {
    return goons.count({x, y});
}

//1 if left turn, -1 if right turn  
int circle_increment(int& x, int& y, int& dir) {
    vector<int> dx = {0, 1, 0, -1};
    vector<int> dy = {1, 0, -1, 0};
    int nx, ny, ndir, ret;
    int x_front = x + dx[dir];
    int y_front = y + dy[dir];
    int x_diag = x_front + dx[(dir + 3) % 4];
    int y_diag = y_front + dy[(dir + 3) % 4];
    if(isgoon(x_front, y_front)) {
        nx = x;
        ny = y;
        ndir = (dir + 1) % 4;
        ret = -1;
    }
    else if(isgoon(x_diag, y_diag)) {
        nx = x_front;
        ny = y_front;
        ndir = dir;
        ret = 0;
    }
    else {
        nx = x_diag;
        ny = y_diag;
        ndir = (dir + 3) % 4;
        ret = 1;
    }
    // cout << x << " " << y << " " << 
    // cout << nx << " " << ny << " " << ndir << " " << ret << "\n";
    x = nx;
    y = ny;
    dir = ndir;
    return ret;
}

//assume that we're going upwards. Try circling the goons CCW, and return whether or not we're 
//surrounded. 
//if we're not surrounded, we can safely ignore all these goons, so just remove them all. 
bool do_circle(int sx, int sy) {
    // cout << "DO CIRCLE : " << sx << " " << sy << "\n";
    int cx = sx;
    int cy = sy;
    int cdir = 1;   //URDL
    int tsum = circle_increment(cx, cy, cdir);
    // cout << "FIRST : " << cx << " " << cy << " " << cdir << "\n";
    while(cx != sx || cy != sy || cdir != 1){
        // cout << cx << " " << cy << " " << cdir << "\n";
        tsum += circle_increment(cx, cy, cdir);
    }
    // cout << "TSUM : " << tsum << "\n";
    if(tsum < 0){
        return true;
    }
    queue<pair<int, int>> q;
    goons.erase({cx, cy + 1});
    q.push({cx, cy + 1});
    vector<int> dr = {-1, -1, -1, 0, 0, 1, 1, 1};
    vector<int> dc = {-1, 0, 1, -1, 1, -1, 0, 1};
    while(q.size() != 0){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i = 0; i < 8; i++){
            int nx = x + dr[i];
            int ny = y + dc[i];
            if(isgoon(nx, ny)){
                goons.erase({nx, ny});
                q.push({nx, ny});
            }
        }
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, x, y;
    cin >> n >> x >> y;
    for(int i = 0; i < n; i++){
        int gx, gy;
        cin >> gx >> gy;
        goons.insert({gx, gy});
    }
    for(int i = 0; i < 2e6; i++){
        //just keep moving upwards. 
        if(isgoon(x, y + 1)) {
            if(do_circle(x, y)) {
                cout << "CONTAINED\n";
                return 0;
            }
        }
        y ++;
    }
    cout << "NOT CONTAINED\n";
    
    return 0;
}
