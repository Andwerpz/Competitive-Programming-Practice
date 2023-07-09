#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1846D

//we can intitially set our answer to the total amount of area covered by the triangles, or b * h / 2 * n. 
//then, we just have to subtract the total overlap. 

//if we consider building the tree from bottom up, we can notice that each triangle only has to worry about 
//overlap from the triangle directly below it. So for each triangle, just calculate how much the triangle directly below
//it overlaps, and subtract it from the total area. 

ld getb(ld b, ld h, ld y1, ld y2) {
    if(y2 >= y1 + h) {
        return 0;
    }
    return b * (1 - (y2 - y1) / h);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        ld b, h;
        cin >> n >> b >> h;
        b /= 2;
        ld prevy = 0;
        ld ans = 0;
        for(int i = 0; i < n; i++){
            ld y;
            cin >> y;
            ld prevb = getb(b, h, prevy, y);
            ld prevh = h - (y - prevy);
            //cout << prevb << " " << prevh << "\n";
            if(i != 0){
                ans -= prevb * (h - (y - prevy));
            }
            ans += b * h;
            prevy = y;
        }
        cout << fixed << setprecision(10) << ans << "\n";
    }
    
    return 0;
}
