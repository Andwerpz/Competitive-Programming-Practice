#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC 2022 Week 1 F

//2D pfx sum problem. 

//Notice the small bounds on l and w of rectangles. We can create a 1000 x 1000 array pfx, pfx[i][j] cell holds the cumulative
//area of all given rectangles of l = i and w = j. 

//notice that given a rectangle l, w, the cumulative area of all rectangles that can fit into it is simply the pfx query at l - 1, w - 1. 
//likewise, the area of all rectangles that it can fit into is sfx query at l, w. 

//Since we want to find the union of these two queries, we can simply just use the pfx array, and do a standard 2D range sum operation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, q;
        cin >> n >> q;
        vector<vector<ll>> pfx(1001, vector<ll>(1001, 0));
        for(int i = 0; i < n; i++){
            int h, w;
            cin >> h >> w;
            pfx[h][w] += (ll) h * (ll) w;
        }
        for(int i = 0; i < pfx.size(); i++){
            for(int j = 0; j < pfx.size(); j++){
                if(i != 0){
                    pfx[i][j] += pfx[i - 1][j];
                }
                if(j != 0){
                    pfx[i][j] += pfx[i][j - 1];
                }
                if(i != 0 && j != 0){
                    pfx[i][j] -= pfx[i - 1][j - 1];
                }
            }
        }
        while(q-- > 0){
            int rl, cl, rh, ch;
            cin >> rl >> cl >> rh >> ch;
            cout << (pfx[rh - 1][ch - 1] - pfx[rh - 1][cl] - pfx[rl][ch - 1] + pfx[rl][cl]) << "\n";
        }
    }
    
    return 0;
}
