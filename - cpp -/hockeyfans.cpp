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

//Alberta Collegiate Programming Contest 2024, Open Division - G

//can do binary search on D. 

bool is_valid(vi& a, int s, int m, int val) {
    int n = a.size();
    vi pfx(a.size() + 1, 0);
    for(int i = 1; i <= n; i++){
        pfx[i] = pfx[i - 1] + (a[i - 1] >= val);
    }
    int cnt = 0;
    for(int i = 0; i + s <= n;){
        if(pfx[i + s] - pfx[i] == s){
            i += s;
            cnt ++;
        }
        else {
            i ++;
        }
    }
    return cnt >= m;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, s, m;
    cin >> n >> s >> m;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int low = 0;
    int high = 1e9 + 100;
    int ans = low;
    while(low <= high){
        int mid = low + (high - low) / 2;
        if(is_valid(a, s, m, mid)) {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}