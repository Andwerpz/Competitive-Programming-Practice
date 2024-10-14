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

//Codeforces - 2005C

//dp[i][j] = max score so far where
//we're currently considering string i
//we're j letters through "narek". 

string S = "narek";
pii calc_sdiff(string& s, int ind) {
    int sdiff = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == S[ind]) {
            ind = (ind + 1) % 5;
            if(ind == 0){
                sdiff += 5;
            }
        }
        else if(s[i] == 'n' || s[i] == 'a' || s[i] == 'r' || s[i] == 'e' || s[i] == 'k') {
            sdiff --;
        }
    }
    return {ind, sdiff};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<string> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vvi dp(n + 1, vi(5, -1e9));
        dp[0][0] = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 5; j++){
                pii next = calc_sdiff(a[i], j);
                dp[i + 1][next.first] = max(dp[i + 1][next.first], dp[i][j] + next.second);
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            }
        }
        int ans = -1e9;
        for(int i = 0; i <= n; i++){
            for(int j = 0; j < 5; j++){
                ans = max(ans, dp[i][j] - j);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}