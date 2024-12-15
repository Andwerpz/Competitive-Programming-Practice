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

//USACO 2024 December Contest Gold 1

//can consider every label value seperately. 
//for each label value, figure out on what x does the amount of groups go up, starting from x = n. 
//there can only be at most sqrt(n) going up values of x. 

//final complexity is around n * sqrt(n) * log(n), but it somehow doesn't TLE. 

int test_x(vi& g, int x) {
    int ans = 0;
    int prev = -1e9;
    for(int i = 0; i < g.size(); i++){
        if(g[i] - prev > x) ans ++, prev = g[i];
    }
    return ans;
}

void calc_ans(vi& g, vi& ans) {
    if(g.size() == 0) return;
    int n = ans.size() - 1;
    int gcnt = 1;
    ans[n] += gcnt;
    int x = n;
    while(true){
        //look for greatest x that will result in rise of gcnt
        int low = 0;
        int high = x - 1;
        int nx = -1;
        int ngcnt = 1e9;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            int _ngcnt = test_x(g, mid);
            if(_ngcnt > gcnt) {
                nx = mid;
                ngcnt = min(ngcnt, _ngcnt);
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        if(nx == -1) break;
        ans[nx] += ngcnt - gcnt;
        gcnt = ngcnt;
        x = nx;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    vvi g(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
        g[a[i]].push_back(i);
    }
    vi ans(n + 1, 0);
    for(int i = 0; i < n; i++){
        calc_ans(g[i], ans);
    }
    for(int i = n - 1; i >= 0; i--){
        ans[i] += ans[i + 1];
    }
    for(int i = 1; i <= n; i++){
        cout << ans[i] << "\n";
    }
    
    return 0;
}