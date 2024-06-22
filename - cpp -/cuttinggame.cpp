#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1974F

//we can simply simulate the problem using a visited array, and two sets to quickly determine what to 
//mark as visited. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int a, b, n, m;
        cin >> a >> b >> n >> m;
        vector<bool> v(n, false);
        set<pair<int, int>> x, y;
        for(int i = 0; i < n; i++){
            int _x, _y;
            cin >> _x >> _y;
            x.insert({_y, i});
            y.insert({_x, i});
        }
        int l = 1;
        int r = b;
        int u = 1;
        int d = a;
        int aans = 0;
        int bans = 0;
        for(int i = 0; i < m; i++){
            int ans = 0;
            char type;
            int k;
            cin >> type >> k;
            if(type == 'L') {
                l += k;
                while(x.size() != 0 && x.begin() -> first < l) {
                    int ind = x.begin() -> second;
                    ans += !v[ind];
                    v[ind] = true;
                    x.erase(*x.begin());
                }
            }
            else if(type == 'R') {
                r -= k;
                while(x.size() != 0 && x.rbegin() -> first > r){
                    int ind = x.rbegin() -> second;
                    ans += !v[ind];
                    v[ind] = true;
                    x.erase(*x.rbegin());
                }
            }
            else if(type == 'U') {
                u += k;
                while(y.size() != 0 && y.begin() -> first < u) {
                    int ind = y.begin() -> second;
                    ans += !v[ind];
                    v[ind] = true;
                    y.erase(*y.begin());
                }
            }
            else if(type == 'D') {
                d -= k;
                while(y.size() != 0 && y.rbegin() -> first > d) {
                    int ind = y.rbegin() -> second;
                    ans += !v[ind];
                    v[ind] = true;
                    y.erase(*y.rbegin());
                }
            }
            if(i % 2 == 0){
                aans += ans;
            }
            else {
                bans += ans;
            }
        }
        cout << aans << " " << bans << "\n";
    }
    
    return 0;
}