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

//Codeforces - 2096D

//observe that the operation doesn't change the parity on each column and each x + y diagonal. 
//therefore, the only column and x + y diagonal on which the parity is not 0 is the one on which the treasure is.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        map<ll, int> cc, dc;
        for(int i = 0; i < n; i++){
            ll x, y;
            cin >> x >> y;
            cc[x] ++;
            dc[x + y] ++;
        }
        ll ansx = -1, ansd = -1;
        for(auto i = cc.begin(); i != cc.end(); i++){
            if(i->second % 2) ansx = i->first;
        }
        for(auto i = dc.begin(); i != dc.end(); i++){
            if(i->second % 2) ansd = i->first;
        }
        //ansd = x + y, ansx = x
        ll ansy = ansd - ansx;
        cout << ansx << " " << ansy << "\n";
    }
    
    return 0;
}