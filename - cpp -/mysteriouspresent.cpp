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

//Codeforces - 4D

//For each envelope, need to compute the longest chain ending at that envelope. 
//Can sort envelopes by width first then height. Then, it's true that any envelope that comes after the 
//current one will never be able to be contained by the current one. 

//So can just do dp[i] = longest chain ending at the ith envelope, and look at dp[j] where j < i

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, cw, ch;
    cin >> n >> cw >> ch;
    vector<array<int, 3>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
    }
    sort(a.begin(), a.end());
    vi dp(n, 0), pv(n, -1);
    for(int i = 0; i < n; i++) {
        if(cw >= a[i][0] || ch >= a[i][1]) {
            dp[i] = -1e9 - 100;
            continue;
        }
        for(int j = 0; j < i; j++) {
            if(a[i][0] > a[j][0] && a[i][1] > a[j][1] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                pv[i] = j;
            }
        }   
    }
    int mxind = -1, mx = -1e9;
    for(int i = 0; i < n; i++) if(dp[i] > mx) {
        mx = dp[i];
        mxind = i;
    }
    if(mxind == -1) {
        cout << "0\n";
        return 0;
    }
    int ptr = mxind;
    vi ans(0);
    while(ptr != -1) {
        ans.push_back(a[ptr][2] + 1);
        ptr = pv[ptr];
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
    cout << "\n";
    
    return 0;
}