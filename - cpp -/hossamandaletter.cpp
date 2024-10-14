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

//Codeforces - 1771E

//holy moly, not even RMQ can save this solution. 

//i'll refer to the pieces of the 'H' as the left column, right column, and horizontal bar. 

//idea is to fix the position and length of the left column, and figure out the maximum from there. 
//since the size of the columns are fixed, the only thing we need to do is maximize the length of the 
//horizontal bar. 

//as it doesn't matter where the horizontal bar is placed (as long as on the right side and adjacent to the 
//left column), we just pick the longest one. Then, we just have to find the farthest out right column within
//the range given by the longest horizontal bar. Both of these can be precomputed to find in O(1) time. 

//Since there are O(n) sizes and O(n^2) positions of the left column, this will run in O(n^3) time. 
//Beware of constant factors, as this solution barely didn't TLE. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i = 0; i < n; i++){
        cin >> g[i];
    }
    // *with and without using a 'medium' quality cell. 
    //for every cell, compute the maximum downwards extension
    vector mx_down(n, vvi(m, vi(2, 0)));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            bool found_med = false;
            for(int k = 0; i + k < n; k++){
                char c = g[i + k][j];
                if(c == '#') {
                    break;
                }
                else if(c == 'm'){
                    if(found_med) {
                        break;
                    }
                    found_med = true;
                }
                mx_down[i][j][1] = k + 1;
                if(!found_med) {
                    mx_down[i][j][0] = k + 1;
                }
            }
        }
    }
    //maximum rightwards extension
    vector mxr_tmp(n, vvi(m, vi(2, 0)));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            bool found_med = false;
            int mx_nomed = 0, mx_med = 0;
            for(int k = 0; j + k < m; k++){
                char c = g[i][j + k];
                if(c == '#') {
                    break;
                }
                else if(c == 'm') {
                    if(found_med) {
                        break;
                    }
                    found_med = true;
                }
                mx_med = k + 1;
                if(!found_med) {
                    mx_nomed = k + 1;
                }
            }
            mxr_tmp[i][j][0] = mx_nomed;
            mxr_tmp[i][j][1] = mx_med;
        }
    }
    vector mx_right(n, vvi(m, vi(2, 0)));
    // cout << "DONE INIT RMQ" << endl;
    //iterate over all tl corner + height combos
    int ans = 0;
    for(int h = 3; h <= n; h++){
        //upd mx_right
        for(int i = 0; i + h - 3 < n; i++){
            for(int j = 0; j < m; j++){
                mx_right[i][j][0] = max(mx_right[i][j][0], mxr_tmp[i + h - 3][j][0]);
                mx_right[i][j][1] = max(mx_right[i][j][1], mxr_tmp[i + h - 3][j][1]);
            }
        }
        for(int i = 0; i + h <= n; i++){
            //put med on left col
            {
                queue<int> s_med, s_nomed;
                for(int j = m - 3; j >= 0; j--){
                    if(mx_down[i][j + 2][0] >= h) {
                        s_nomed.push(j + 2);
                    }
                    if(mx_down[i][j + 2][1] >= h) {
                        s_med.push(j + 2);
                    }
                    if(mx_down[i][j][1] < h) {
                        continue;
                    }
                    bool lmed = mx_down[i][j][0] < h;
                    // cout << "LMED : " << lmed << " " << i << " " << j << endl;
                    if(lmed) {
                        //have to have no medium on horiz and right col
                        // cout << "TRY L HORIZ" << " " << i + 1 << " " << i + h - 1 << " " << mx_right[j + 1][0].n << endl;
                        int mx_horiz = mx_right[i + 1][j + 1][0];
                        // cout << "MX_HORIZ : " << mx_horiz << endl;
                        while(s_nomed.size() != 0 && s_nomed.front() > j + mx_horiz + 1) {
                            s_nomed.pop();
                        }
                        if(s_nomed.size() != 0){
                            int crow = s_nomed.front();
                            ans = max(ans, h * 2 + (crow - j) - 1);
                        }
                    }
                }
            }
            //put med not on left col
            {
                queue<int> s_med, s_nomed;
                for(int j = m - 3; j >= 0; j--){
                    if(mx_down[i][j + 2][0] >= h) {
                        s_nomed.push(j + 2);
                    }
                    if(mx_down[i][j + 2][1] >= h) {
                        s_med.push(j + 2);
                    }
                    if(mx_down[i][j][1] < h) {
                        continue;
                    }
                    bool lmed = mx_down[i][j][0] < h;
                    // cout << "LMED : " << lmed << " " << i << " " << j << endl;
                    if(!lmed){
                        //try put medium on horiz
                        {
                            // cout << "TRY MED HORIZ" << endl;
                            int mx_horiz = mx_right[i + 1][j + 1][1];
                            // cout << "MX_HORIZ : " << mx_horiz << endl;
                            while(s_nomed.size() != 0 && s_nomed.front() > j + mx_horiz + 1) {
                                s_nomed.pop();
                            }
                            if(s_nomed.size() != 0){
                                int crow = s_nomed.front();
                                ans = max(ans, h * 2 + (crow - j) - 1);
                            }
                        }
                        //medium on right col
                        {
                            int mx_horiz = mx_right[i + 1][j + 1][0];
                            while(s_med.size() != 0 && s_med.front() > j + mx_horiz + 1) {
                                s_med.pop();
                            }
                            if(s_med.size() != 0){
                                int crow = s_med.front();
                                ans = max(ans, h * 2 + (crow - j) - 1);
                            }
                        }
                    }
                }
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}