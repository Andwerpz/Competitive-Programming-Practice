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

//Codeforces - 2147B

//we can do a construction like this:

//n = 5
// 5 4 3 2 1 5 1 2 3 4

//n = 8
// 8 7 6 5 4 3 2 1 8 1 2 3 4 5 6 7

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi ans(2 * n);
        ans[0] = n, ans[n] = n;
        int ptr = 1;
        for(int i = n - 1; i >= 1; i--) {
            ans[ptr] = i, ans[2 * n - ptr] = i;
            ptr ++;
        }
        for(int x : ans) cout << x << " ";
        cout << "\n";
    }
    
    return 0;
}