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

//Codeforces - 2004B

//if the segments don't intersect, then the answer is pretty simple: just close one door between the segments. 
//otherwise, if they do intersect, we must close all doors surrounding the intersection. 

//be careful of one edge case though: if the segments share the same left or right bounds, then we don't need
//to close the door on the right or left bound. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int la, ra, lb, rb;
        cin >> la >> ra >> lb >> rb;
        la --;
        lb --;
        int l = max(la, lb);
        int r = min(ra, rb);
        int ans = max(0, r - l) + 1;
        if(la == lb) {
            ans --;
        }
        if(ra == rb) {
            ans --;
        }
        cout << ans << "\n";
    }
    
    return 0;
}