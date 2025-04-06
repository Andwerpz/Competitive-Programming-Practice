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

//Codeforces - 1826A

//the constraints are so small, you can just test every amount of liars. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        int ans = -1;
        for(int i = 0; i <= n; i++){
            //exactly i liars
            int lcnt = 0;
            for(int j = 0; j < n; j++) lcnt += a[j] > i;
            if(lcnt == i) ans = i;
        }
        cout << ans << "\n";
    }
    
    return 0;
}