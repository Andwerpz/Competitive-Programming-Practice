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

//Kattis - inflagrantedelicto

//question is really hard to read, but what I assumed is that to prove one side wrong, you need to find some subsequence of
//events such that one side agrees and the other disagrees. 

//answer to question 1 = 2; there has to be some out of order pair
//answer to question 2 = lcs + 1

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    //relabel all elements in a by where they occur in b. do LIS
    vi bo(n);
    {
        map<int, int> indmp;
        for(int i = 0; i < n; i++) indmp[b[i]] = i;
        for(int i = 0; i < n; i++) bo[i] = indmp[a[i]];
    }
    vi dp(n + 1, 1e9);
    dp[0] = -1;
    int ans = 0;
    for(int i = 0; i < n; i++){ 
        int low = 0, high = n + 1;
        int ind = 0;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(dp[mid] < bo[i]) ind = mid + 1, low = mid + 1;
            else high = mid - 1;
        }
        // cout << "IND : " << ind << "\n";
        dp[ind] = min(dp[ind], bo[i]);
        ans = max(ans, ind);
    }
    cout << "2 " << ans + 1 << "\n";

    return 0;
}