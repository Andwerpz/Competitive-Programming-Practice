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

//Kattis - deathtaxes

//simulation. Note that you only care about the tax on die. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int cnt = 0;
    ld avg = 0;
    while(true) {
        string ty;
        cin >> ty;
        if(ty == "buy") {
            int x, y;
            cin >> x >> y;
            if(cnt == 0) {
                cnt = x, avg = y;
            }
            else {
                avg = (avg * cnt + y * x) / (cnt + x);
                cnt += x;
            }
        }
        else if(ty == "sell") {
            int x, y;
            cin >> x >> y;
            cnt -= x;
        }
        else if(ty == "split") {
            int x;
            cin >> x;
            // cout << "X : " << x << "\n";
            cnt *= x;
            avg /= x;
        }
        else if(ty == "merge") {
            int x;
            cin >> x;
            cnt /= x;
            avg *= x;
        }
        else if(ty == "die") {
            ld y;
            cin >> y;
            ld ans = y * cnt;
            ld prof = (y - avg) * cnt;
            prof = max(prof, (ld) 0);
            ans -= prof * 0.3;
            cout << fixed << setprecision(10) << ans << "\n";
            break;
        }
        // cout << cnt << " " << avg << "\n";
    }
    
    return 0;
}