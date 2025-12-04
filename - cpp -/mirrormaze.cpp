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

//Mines HSPC 2025 Open Division - L

//first, observe that the distance to the reflections is always going to be a multiple of 2. 

//for even k we have (d / 2) = (k / 2) x + (k / 2) y
//for odd k we have (d / 2) = ((k + 1) / 2) x + ((k - 1) / 2) y

//even case is trivial, can solve odd case by noticing the coefficients on x and y are one apart. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        ll k, d;
        cin >> k >> d;
        if(d % 2) {
            cout << "impossible\n";
            continue;
        }
        d /= 2;
        ll x, y;
        if(k == 1){
            x = d;
            y = 1;
        }
        else if(k % 2 == 1) {
            //(d / 2) = (k / 2 + 1) x + (k / 2) y
            ll ck = k / 2 + 1;
            x = d / ck;
            if(ck * x == d) x --;
            ll rem = d - (ck * x);
            rem %= (ck - 1);
            // cout << "X : " << x << " " << rem << "\n";
            x -= (((ck - 1) - rem) % (ck - 1));
            assert((d - (ck * x)) % (ck - 1) == 0);
            y = (d - (ck * x)) / (ck - 1);
            // cout << "Y : " << y << "\n";
            if(x <= 0) {
                cout << "impossible\n";
                continue;
            }
        }
        else {
            //(d / 2) = (k / 2) x + (k / 2) y
            if(d % (k / 2) != 0 || k > d) {
                cout << "impossible\n";
                continue;
            }
            x = 1;
            y = (d - (k / 2)) / (k / 2);
        }
        ll val;
        if(k % 2) val = (x + y) * (k / 2) + x;
        else val = (x + y) * (k / 2);
        // cout << "VAL : " << val << endl;
        assert(val == d);
        cout << x << " " << y << "\n";
    }
    
    return 0;
}