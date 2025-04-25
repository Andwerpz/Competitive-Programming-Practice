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

//Spring 2025 Columbia University Local Contest - H

//direct application of 3d prefix sum. 

//first, fix the top left corner of the cube. Then, we can slowly expand the cube until it's not all 1s. 
//there are n^3 unique corners, and once we fixed it, we can expand it at most n times, so this is O(n^4), which
//is good enough with good constant factor. 

int getsum(vector<vvi>& a, int x1, int y1, int z1, int x2, int y2, int z2) {
    int ans = a[x2][y2][z2];
    ans -= a[x1][y2][z2] + a[x2][y1][z2] + a[x2][y2][z1];
    ans += a[x1][y1][z2] + a[x2][y1][z1] + a[x1][y2][z1];
    ans -= a[x1][y1][z1];
    return ans;
}   

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int z, x, y;
        cin >> z >> x >> y;
        vector<vvi> a(x + 1, vvi(y + 1, vi(z + 1, 0)));
        for(int k = 1; k <= z; k++){
            for(int i = 1; i <= x; i++){
                for(int j = 1; j <= y; j++){
                    cin >> a[i][j][k];
                    a[i][j][k] += a[i - 1][j][k] + a[i][j - 1][k] + a[i][j][k - 1];
                    a[i][j][k] -= a[i - 1][j - 1][k] + a[i][j - 1][k - 1] + a[i - 1][j][k - 1];
                    a[i][j][k] += a[i - 1][j - 1][k - 1];
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                for(int k = 0; k < z; k++){
                    int ib = i, jb = j, kb = k, s = 0;
                    while(i + s <= x && j + s <= y && k + s <= z) {
                        if(getsum(a, i, j, k, i + s, j + s, k + s) != s * s * s) {
                            break;
                        }
                        ans = max(ans, s);
                        s ++;
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}