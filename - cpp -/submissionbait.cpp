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

//Codeforces - 1990A

//first, sort a, then just do dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        a.push_back(0);
        n ++;
        sort(a.begin(), a.end());
        vb dp(n);
        dp[n - 1] = false;
        for(int i = n - 2; i >= 0; i--){
            bool win = !dp[i + 1];
            for(int j = i + 1; j < n; j++){
                if(a[j] != a[j - 1] && !dp[j]){
                    win = true;
                }
            }
            dp[i] = win;
        }
        cout << (dp[0]? "YES" : "NO") << "\n";
    }
    
    return 0;
}