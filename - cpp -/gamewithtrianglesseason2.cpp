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

//Codeforces - 2074G

//since n is so small, can just do range dp. dp[l][r] = maximum sum when only considering points in range [l, r]. 
//we have two options:
// - create a triangle with vertices l, r, k, where l < k < r. 
// - subdivide the segment, so take sum of segments [l, k], [k + 1, r]. 
//using these two options we can build any partitioning of the points into triangles. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vl a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        //dp1[l][len] = max sum given we've chosen points l and l + len - 1
        //dpa[l][len] = max sum in segment l to l + len - 1
        vvl dp1(n, vl(n + 1, 0)), dpa(n, vl(n + 1, 0));
        //base cases
        for(int len = 3; len < n - 1; len++){
            for(int l = 0; l < n; l++){
                int r = (n + l + len - 1) % n;
                //add new triangle
                for(int k = (l + 1) % n; k != r; k = (k + 1) % n) {
                    ll cans = a[l] * a[r] * a[k];
                    int len1 = (n + k - l - 1) % n, len2 = (n + r - k - 1) % n;
                    cans += dpa[(l + 1) % n][len1];
                    cans += dpa[(k + 1) % n][len2];
                    dpa[l][len] = max(dpa[l][len], cans);
                }
                //build via subranges
                for(int k = l; k != r; k = (k + 1) % n) {
                    int len1 = (n + k - l + 1) % n, len2 = (n + r - ((k + 1) % n) + 1) % n;
                    ll cans = dpa[l][len1] + dpa[(k + 1) % n][len2];
                    dpa[l][len] = max(dpa[l][len], cans);
                }
            }
        }
        //try everything
        ll ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                for(int k = j + 1; k < n; k++){
                    int len1 = (n + j - i - 1) % n, len2 = (n + k - j - 1) % n, len3 = (n + i - k - 1) % n;
                    ll cans = a[i] * a[j] * a[k];
                    cans += dpa[(i + 1) % n][len1];
                    cans += dpa[(j + 1) % n][len2];
                    cans += dpa[(k + 1) % n][len3];
                    ans = max(ans, cans);
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}