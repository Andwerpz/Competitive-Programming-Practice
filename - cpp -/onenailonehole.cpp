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

//University of Alberta Programming Contest 2025 Open - H

//observe that if we put the nails in a periodic fashion, in a grid spaced (W + 1), (H + 1) spaces horizontally
//and vertically, then any paper placed will be punctured by exactly 1 nail. 

//we just need to find for each paper, which nail it will be punctured by in this grid, and add them all to a set. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    int W, H;
    cin >> n >> W >> H;
    set<pii> ans;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        int nx = ((x + W) / (W + 1)) * (W + 1);
        int ny = ((y + H) / (H + 1)) * (H + 1);
        ans.insert({nx, ny});
    }
    cout << ans.size() << "\n";
    for(pii x : ans) cout << x.first << " " << x.second << "\n";
    
    return 0;
}