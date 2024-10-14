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

//Codeforces - 1809E

//note that after applying the operation, the total amount of water in the two tanks remains
//constant.

//each diagonal in the answer represents some sum of water in the two tanks. So it would probably
//be smart to solve each diagonal as one. 

//for a given sum of water, note that after a few operations some initial states become equivalent to
//other ones due to them being 'smushed' against the 'edge' (edge being when one of the tanks
//becomes empty)

//we just have to find the 'extent' of these edges, and where they end up. 

void transfer(int& aamt, int& bamt, int a, int b, int v) {
    v *= -1;
    if(v > 0){
        int diff = min({a - aamt, bamt, v});
        aamt += diff;
        bamt -= diff;
    }
    else {
        int diff = min({b - bamt, aamt, -v});
        bamt += diff;
        aamt -= diff;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, a, b;
    cin >> n >> a >> b;
    vi v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }   
    vvi ans(a + 1, vi(b + 1, 0));
    //each diagonal represents some total amount of water between a and b.
    for(int i = 0; i <= a + b; i++){
        int min_a = max(0, i - b);
        int min_b = i - min_a;
        int max_a = min(a, i);
        int max_b = i - max_a;
        for(int j = 0; j < n; j++){
            transfer(min_a, min_b, a, b, v[j]);
            transfer(max_a, max_b, a, b, v[j]);
        }
        int min_v = min_a;
        int max_v = max_a;
        //reverse
        for(int j = n - 1; j >= 0; j--){
            transfer(min_a, min_b, a, b, -v[j]);
            transfer(max_a, max_b, a, b, -v[j]);
        }
        int r = min(a, i);
        int c = i - r;
        while(r >= 0 && c <= b){
            // cout << "RC : " << r << " " << c << "\n";
            if(r >= max_a){
                ans[r][c] = max_v;
            }
            else if(r >= min_a) {
                ans[r][c] = max_v - (max_a - r);
            }
            else {
                ans[r][c] = min_v;
            }
            r --;
            c ++;
        }
    }
    for(int i = 0; i <= a; i++){
        for(int j = 0; j <= b; j++){
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}