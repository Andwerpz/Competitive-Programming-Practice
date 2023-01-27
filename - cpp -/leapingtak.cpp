#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problem Set #1 (Spring 2023) C

//i really liked this one. Combining pfx sums and dp is neat

//basically like the coins problem, but instead of choosing a specific value to increment the state, we can 
//choose the value that is in any of 10 disjoint ranges. The number of values can be very large, so we can't treat
//it like we have a bunch of different coins. 

//the answer is to notice that instead of simulating all of the values within the ranges, we can instead update the dp
//array as if it were a pfx sum array, making use of the range edit pfx sum technique. Then we keep a sum variable, and
//just add to it every time we come across a new state. 

//this works since we only edit ranges that we are going to visit in the future, and never ones that we've already visited. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    ll mod = 998244353;
    vector<ll> dp(n + 1, 0);
    vector<pair<int, int>> s(k, pair<int, int>(0, 0));
    for(int i = 0; i < k; i++){
        cin >> s[i].first >> s[i].second;
    }
    dp[0] = 1;
    dp[1] = -1;
    ll sum = 0;
    for(int i = 0; i < n; i++){
        sum += dp[i];
        sum %= mod;
        //cout << sum << " " << dp[i] << endl;
        for(int j = 0; j < k; j++){
            int l = i + s[j].first;
            int r = i + s[j].second + 1;
            if(l <= n) {
                dp[l] += sum;
                dp[l] %= mod;
            }
            if(r <= n){
                dp[r] -= sum;
                if(dp[r] < 0){
                    dp[r] += mod;
                }
            }
        }
    }
    cout << sum << "\n";
    
    return 0;
}
