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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        vl dp(n + 1, 0);    //how many 3-segments start at each index
        vi nxt(n + 4, n);  //index of next 1
        for(int i = n - 1; i >= 0; i--){
            if(s[i] == '1'){
                nxt[i] = i;
            }
            else {
                nxt[i] = nxt[i + 1];
            }
        }
        for(int i = 0; i < n; i++){
            dp[nxt[i]] ++;
            dp[nxt[i + 3]] += dp[i];
        }
        ll ans = 0;
        ll sum = 0;
        for(int i = 0; i < n; i++){
            sum += dp[i];
        }
        for(int i = n - 1; i >= 0; i--){
            ans += sum;
            sum -= dp[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}