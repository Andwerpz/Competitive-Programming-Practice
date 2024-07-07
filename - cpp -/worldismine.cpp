#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1987D

//Alice's strategy is predictable. Consider the set of unique elements. Since whatever cake she eats has to be 
//tastier than any cake she's ever eaten, the tastiness of cakes she eats has to be strictly ascending. Therefore,
//alice will always want to eat the minimum cake first, then progressively work her way up to the most tasty. 

//In order to minimize the amount of cakes alice eats, bob will need to remove some element from the set 
//before alice gets to it. This requires bob to eat all cakes of a specific tastiness. 

//To find the maximum amount of cakes that bob can remove, we can do dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        map<int, int> m;
        for(int i = 0; i < n; i++){
            m[a[i]] ++;
        }
        vector<int> b(0);
        for(auto i = m.begin(); i != m.end(); i++){
            b.push_back(i -> second);
        }
        vector dp(b.size() + 1, vector<int>(b.size() + 1, -1e9));
        dp[0][0] = 0;
        for(int i = 0; i < b.size(); i++){
            for(int j = 0; j <= b.size(); j++){
                //eat all current ones
                if(b[i] <= j) {
                    dp[i + 1][j - b[i]] = max(dp[i + 1][j - b[i]], dp[i][j] + 1);
                }
                //don't eat current one
                if(j != b.size()) {
                    dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j]);
                }
            }
        }
        int mxdp = 0;
        for(int i = 0; i <= b.size(); i++){
            for(int j = 0; j <= b.size(); j++){
                mxdp = max(mxdp, dp[i][j]);
            }
        }
        cout << b.size() - mxdp << "\n";
    }
    
    return 0;
}