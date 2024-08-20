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

//AtCoder - ABC366E

//note that we can solve x distances and y distances seperately. Since the range on the coordinates is 
//relatively small, it enables this solution:

//for each x and y coordinate, compute the sum of x and y distances respectively. Then, sort all the distances
//and do a 2 pointer where for each x distance, we figure out how many y distances can sum up to that x distance
//and still be less than d. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, d;
    cin >> n >> d;
    vl x(n), y(n);
    for(int i = 0; i < n; i++){
        cin >> x[i] >> y[i];
        x[i] += 2e6 + 50;
        y[i] += 2e6 + 50;
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    vl xc(4e6 + 100, 0), yc(4e6 + 100, 0);
    for(int i = 0; i < n; i++){
        xc[0] += x[i];
        yc[0] += y[i];
    }
    int xptr = 0, yptr = 0;
    for(int i = 1; i < xc.size(); i++){
        xc[i] = xc[i - 1] + xptr - (n - xptr);
        yc[i] = yc[i - 1] + yptr - (n - yptr);
        while(xptr != n && x[xptr] == i) {
            xptr ++;
        }
        while(yptr != n && y[yptr] == i){
            yptr ++;
        }
    }
    ll ans = 0;
    sort(xc.begin(), xc.end());
    sort(yc.begin(), yc.end());
    yptr = yc.size();
    for(int i = 0; i < xc.size(); i++){
        while(yptr != 0 && xc[i] + yc[yptr - 1] > d) {
            yptr --;
        }
        ans += yptr;
    }
    cout << ans << "\n";
    
    return 0;
}