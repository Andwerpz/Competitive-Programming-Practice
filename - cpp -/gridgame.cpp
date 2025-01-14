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

//AtCoder - AGC29D

//If Takahashi ever chooses to stand still, then Aoki will just stand still, ending the game. Therefore, Takahashi's
//strategy is to always move if possible. Let's now analyze from Aoki's perspective. Aoki wants to make the active
//cell 'run into' an obstacle as soon as possible. Since the amount of moves Takahashi can do is purely determined
//by the x coordinate of the nearest obstacle, we'll look column by column starting from x = 0 to find the closest
//obstacle. 

//For each column we'll maintain the maximum reachable y coordinate. If we can't find a cell on the next column to
//run into, then we should increment the max y coordinate, except in the case where there is a cell blocking us from
//moving further downwards. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int w, h, n;
    cin >> w >> h >> n;
    vvi a(w, vi(0));
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        x --;
        y --;
        a[x].push_back(y);
    }
    int ans = w, mx_y = 0;
    for(int i = 0; i < w - 1; i++){
        bool inc = true, block = false;
        for(int j = 0; j < a[i + 1].size(); j++){
            if(a[i + 1][j] == mx_y + 1) inc = false;
            if(a[i + 1][j] <= mx_y) block = true;
        }
        if(block) {
            ans = i + 1;
            break;
        }
        mx_y += inc;
    }
    cout << ans << "\n";
    
    return 0;
}