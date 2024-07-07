#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1938C

//we can use a 2 pointer method to find the minimum segment in which Alice will be satisfied, and then Bob and Charlie
//will have to be on either side of Alice's segment. 

//We then do the same with Bob and Charlie in the middle. 

//My implementation is a little different, but it's mostly the same idea. 

vector<int> solve(vector<vector<ll>>& pfx, vector<int> ord, ll tgt) {
    int a = -1;
    int n = pfx[0].size() - 1;
    for(int i = 1; i <= n; i++){
        if(pfx[ord[0]][i] >= tgt) {
            a = i;
            break;
        }
    }
    int b = -1;
    for(int i = a; i <= n; i++){
        if(pfx[ord[1]][i] - pfx[ord[1]][a] >= tgt) {
            b = i;
            break;
        }
    }
    int c = n;
    if(b == -1 || pfx[ord[2]][n] - pfx[ord[2]][b] < tgt) {
        return {};
    }
    vector<int> ans(6, -1);
    ans[ord[0] * 2] = 1;
    ans[ord[0] * 2 + 1] = a;
    ans[ord[1] * 2] = a + 1;
    ans[ord[1] * 2 + 1] = b;
    ans[ord[2] * 2] = b + 1;
    ans[ord[2] * 2 + 1] = c;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n + 1), b(n + 1), c(n + 1);
        a[0] = 0, b[0] = 0, c[0] = 0;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            a[i] += a[i - 1];
        }
        for(int i = 1; i <= n; i++){
            cin >> b[i];
            b[i] += b[i - 1];
        }
        for(int i = 1; i <= n; i++){
            cin >> c[i];
            c[i] += c[i - 1];
        }
        vector<vector<ll>> pfx = {a, b, c};
        ll tgt = (a[n] + 2) / 3;
        vector<vector<int>> ords = {
            {0, 1, 2},
            {0, 2, 1},
            {1, 0, 2},
            {1, 2, 0},
            {2, 0, 1},
            {2, 1, 0}
        };
        vector<int> ans = {};
        for(int i = 0; i < ords.size(); i++){
            vector<int> cans = solve(pfx, ords[i], tgt);
            if(cans.size() != 0){
                ans = cans;
            }
        }
        if(ans.size() == 0){
            cout << "-1\n";
        }
        else {
            for(int i = 0; i < 6; i++){
                cout << ans[i] << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}