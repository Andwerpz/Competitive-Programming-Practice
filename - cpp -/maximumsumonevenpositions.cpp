#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problem Set #1 (Spring 2023) I

//notice that reversing an odd length segment of the array does nothing, so we'll stick to reversing even length segments. 

//if you reverse an even length segment, then what you'll find is that every number that was on an even index in that segment
//is now on an odd index, and vice versa. 

//babadobee, you use dp. 

ll solve(vector<pair<ll, ll>> a) {
    int n = a.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(3, 0));
    //0 : haven't reversed
    //1 : during reverse
    //2 : after reverse
    //take then decide
    for(int i = 0; i < n; i++){
        dp[i + 1][0] = max(dp[i + 1][0], dp[i][0] + a[i].first);
        dp[i + 1][1] = max(dp[i + 1][1], dp[i][0] + a[i].second);
        dp[i + 1][1] = max(dp[i + 1][1], dp[i][1] + a[i].second);
        dp[i + 1][2] = max(dp[i + 1][2], dp[i][1] + a[i].first);
        dp[i + 1][2] = max(dp[i + 1][2], dp[i][2] + a[i].first);
    }
    return max(dp[n][0], max(dp[n][1], dp[n][2]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        if(n % 2 == 1){
            a.push_back(0);
        }
        vector<pair<ll, ll>> p1(0);
        vector<pair<ll, ll>> p2(0);
        for(int i = 0; i + 1 < a.size(); i += 2){
            p1.push_back({a[i], a[i + 1]});
        }
        p2.push_back({a[0], a[0]});
        for(int i = 1; i + 1 < a.size(); i += 2){
            p2.push_back({a[i + 1], a[i]});
        }
        cout << max(solve(p1), solve(p2)) << "\n";
    }
    
    return 0;
}
