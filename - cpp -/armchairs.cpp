#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1525D

//first, notice that it's optimal to move each person exactly once. Any solution that involves moving someone twice can 
//be turned into an equal or better solution by just moving everyone once. 

//Next, consider the set of chairs that are initially occupied, S, and the set of chairs that are initially 
//not occupied, E. We want to match every element in S to exactly 1 element in E such that each element in E
//is used no more than once, and the sum of absolute differences of matched elements is minimized. 

//first notice that if we have two matchings (a, b) and (c, d), a, c in S and b, d in E, if a < c then b should be
//less than d. If b > d, then we could always equal or improve the answer by just swapping b and d. 
//in general, if we know the set S, and which elements we will pick in E to create the matching, we simply need to 
//sort both lists, and match the elements up in sorted order, and that will minimize the sum of absolute differences. 

//the problem now is that we don't know the optimal set of elements to pick from E. This is where dynamic programming 
//comes in. Since we know that the elements must be matched up in sorted order, we can just first sort S and E. 
//Then, dp[i][j] = minimum cost of matching the ith prefix of S with the jth prefix of E. 

//transitions are :
//dp[i][j] -> dp[i + 1][j + 1]; we match the next element of S with the next element of E
//dp[i][j] -> dp[i][j + 1]; we skip the next element of E. 

//notice we don't have a transition like dp[i][j] -> dp[i + 1][j]. This is because we can't skip any elements of S.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> s(0), e(0);
    for(int i = 0; i < n; i++){
        if(a[i]) {
            s.push_back(i);
        }
        else {
            e.push_back(i);
        }
    }
    vector<vector<ll>> dp(s.size() + 1, vector<ll>(e.size() + 1, 1e18));
    dp[0][0] = 0;
    for(int i = 0; i < s.size(); i++){
        for(int j = 0; j < e.size(); j++){
            //match the current one up
            dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + abs(s[i] - e[j]));
            //skip the current e
            dp[i][j + 1] = min(dp[i][j + 1], dp[i][j]);
        }
    }
    ll ans = 1e18;
    for(int i = 0; i <= e.size(); i++){
        ans = min(ans, dp[s.size()][i]);
    }
    cout << ans << "\n";
    
    return 0;
}