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
typedef vector<vector<bool>> vvb;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1994G

//"Think of the most stupid solution you can do" 
// - editorial

//we can build the solution bit by bit using dp, starting from the least significant bit. 
//dp[i][j] = whether or not we can sucessfully finish building where we've built i bits so far, and 
//our current 'extra' sum is j. 

//consider starting to build from the 2^0 bit. If we choose to turn that bit off, then we'll have to 
//add to the sum the amount of values in a which have the 2^0 bit on. When doing the transition, we'll 
//have to check whether or not our current sum satisfies the current bit in s. 

signed main() { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vb s(k);
        string line;
        cin >> line;
        for(int i = 0; i < k; i++){
            s[i] = line[i] - '0';
        }
        reverse(s.begin(), s.end());
        vvb g(n, vb(k));
        for(int i = 0; i < n; i++){
            cin >> line;
            for(int j = 0; j < k; j++){
                g[i][j] = line[j] - '0';
            }
            reverse(g[i].begin(), g[i].end());
        }
        vi cnt(k, 0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < k; j++){
                cnt[j] += g[i][j];
            }
        }
        vector<vb> dp(k + 1, vb(n, false)), nxt(k, vb(n, false));
        dp[k][0] = true;
        for(int i = k - 1; i >= 0; i--){
            for(int j = 0; j < n; j++){
                int ntake = j + cnt[i];
                int take = j + n - cnt[i];
                if(ntake % 2 == s[i] && dp[i + 1][ntake / 2]) {
                    dp[i][j] = true;
                    nxt[i][j] = false;
                }
                if(take % 2 == s[i] && dp[i + 1][take / 2]) {
                    dp[i][j] = true;
                    nxt[i][j] = true;
                }
            }
        }
        if(!dp[0][0]) {
            cout << "-1\n";
            continue;
        }
        vb ans(k);
        int sum = 0;
        for(int i = 0; i < k; i++){
            ans[i] = nxt[i][sum];
            if(nxt[i][sum]) {
                sum += n - cnt[i];
            }
            else {
                sum += cnt[i];
            }
            sum /= 2;
        }
        reverse(ans.begin(), ans.end());
        for(int i = 0; i < k; i++){
            cout << ans[i];
        }
        cout << "\n";
    }
    
    return 0;
}