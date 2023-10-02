#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - deceptivedice

//the expected value for one dice roll is trivial, just average the results from all faces. 

//if you have 2 dice rolls, for each face you land on, you can either take the value of the face, or 
//the expected value for 1 dice roll. Of course, you always want to take the maximum. 

//thus, with this recursive recurrence, we can solve for any n and k. 

vector<ld> dp;

ld solve(int n, int k) {
    if(k == 0){
        return 0;
    }
    if(dp[k] != -1){
        return dp[k];
    }
    //for each possible dice value you roll:
    ld ans = 0;
    for(int i = 1; i <= n; i++){
        ld take = i;
        ld notake = solve(n, k - 1);
        ans += max(take, notake);
    }
    ans /= (ld) n;
    dp[k] = ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    dp = vector<ld>(k + 1, -1);
    cout << fixed << setprecision(10) << solve(n, k) << "\n";
    
    return 0;
}
