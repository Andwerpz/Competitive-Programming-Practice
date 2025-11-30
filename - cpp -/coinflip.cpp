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

//2025 Damascus University Programming Contest - F

//cool problem. You don't need to know how many even / odd queries there are to get the optimal score. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vl a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    int eptr = 0, optr = 0;
    vector<pll> e, o;
    for(int i = 0; i < n; i++) {
        if((i + 1) % 2) o.push_back({a[i], i + 1});
        else e.push_back({a[i], i + 1});
    }
    sort(e.begin(), e.end());
    sort(o.begin(), o.end());
    reverse(e.begin(), e.end());
    reverse(o.begin(), o.end());
    for(int i = 0; i < k; i++){
        int x;
        cin >> x;
        assert(eptr != e.size());
        assert(optr != o.size());
        if(x == 2) {
            cout << e[eptr].second << endl;
            eptr ++;
        }
        else {
            if(e[eptr + k - i - 1].first > o[optr].first) {
                cout << e[eptr].second << endl;
                eptr ++;
            }
            else {
                cout << o[optr].second << endl;
                optr ++;
            }
        }
        int stat;
        cin >> stat;
        assert(stat == 1);
    }
    
    return 0;
}