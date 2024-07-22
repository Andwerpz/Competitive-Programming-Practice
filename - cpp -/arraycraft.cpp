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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1990B

//for the interval between x and y, put all 1s, for everything else, you need to alternate. 
//this works because x != y. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, x, y;
        cin >> n >> x >> y;
        y --;
        vi ans(n);
        for(int i = y; i < x; i++){
            ans[i] = 1;
        }
        bool pos = false;
        for(int i = x; i < n; i++){
            ans[i] = pos? 1 : -1;
            pos = !pos;
        }
        pos = false;
        for(int i = y - 1; i >= 0; i--){
            ans[i] = pos? 1 : -1;
            pos = !pos;
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}