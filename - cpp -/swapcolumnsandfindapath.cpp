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

//Codeforces - 2046A

//each column is either to the left, to the right, or is the middle column (the middle column
//is the one in which we take our only downwards step). We can arbitrarily assign these columns to
//the left or right, and ofc we'll greedily assign them to maximize the sum. 

//then, after assigning to left and right, we'll choose the maximum one to be the middle. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pii> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].first;
        }
        for(int i = 0; i < n; i++){
            cin >> a[i].second;
        }
        int mxmin = -1e9;
        int maxmin_ind = 0;
        ll ans = 0;
        for(int i = 0; i < n; i++){
            ans += max(a[i].first, a[i].second);
            if(min(a[i].first, a[i].second) > mxmin) {
                mxmin = min(a[i].first, a[i].second);
                maxmin_ind = i;
            }
        }
        ans += mxmin;
        cout << ans << "\n";
    }
    
    return 0;
}