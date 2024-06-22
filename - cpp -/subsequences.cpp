#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1183 E, H

//i have no idea what's the intended solution for the easy version, and how tf is the easy version rated higher
//than the hard version?

//tbh, my solution for the hard version is very jank.

//dp[i][j][k] = number of ways to make given
//we've considered the first i characters in s
//the prefix of our string consists of j characters so far
//the last character that we've added is k

//the idea is that dp[n][j] will give us all the unique subsequences of s that are exactly j characters long. 
//Then, to figure out the minimum cost for k unique subsequences, we can just greedily add the longest subsequences
//until we either get k or run out, in which case we print -1. 

//the problem is that if we were to just run this dp naively, we would overcount or generate duplicate 
//subsequences. The jank part of my solution is avoiding this

//ok, let's assume that dp[i][j][k] actually holds the accurate count of unique subsequences. Where we risk 
//overcounting is when we add a character, or transition from dp[i][j][k] to dp[i + 1][j + 1][s[i]]. But exactly
//how much will we overcount?

//we'll actually overcount by exactly dp[x][j][k], where x is the first index before i where s[x] == s[i]. 
//this is because dp[x][j][k] represents a subset of the subsequences that dp[i][j][k] does, as it is
//also the accurate count of subsequences of length j that end with k. 

//this is probably a bad explanation, and im kinda rushed rn, so go read the editorial for more info :D

vector<vector<vector<ll>>> dp, v;
ll _k;

void incdp(int i, int j, int k, int ni, int nj, int nk) {
    ll diff = dp[i][j][k] - v[j][k][nk];
    dp[ni][nj][nk] = min(diff + dp[ni][nj][nk], _k);
    v[j][k][nk] += diff;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n;
    cin >> n >> _k;
    string s;
    cin >> s;
    dp = vector<vector<vector<ll>>>(n + 1, vector<vector<ll>>(n + 1, vector<ll>(26, 0)));
    dp[0][0][0] = 1;
    v = vector<vector<vector<ll>>>(n + 1, vector<vector<ll>>(26, vector<ll>(26, 0)));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < 26; k++){
                //add the next character
                incdp(i, j, k, i + 1, j + 1, s[i] - 'a');
                //don't add the next character
                dp[i + 1][j][k] = min(dp[i + 1][j][k] + dp[i][j][k], _k);
            }
        }
    }
    ll ans = 0;
    for(int i = n; i >= 0; i--){
        for(int j = 0; j < 26; j++){
            ll amt = dp[n][i][j];
            ll ucost = n - i;
            ll take = min(_k, amt);
            ans += take * ucost;
            _k -= take;
            // if(amt != 0){
            //     cout << "GANS : " << i << " " << (char) (j + 'a') << " " << amt << "\n";
            // }
            // if(take != 0){
            //     cout << "TAKE : " << take << " " << ucost << "\n";
            // }
        }
    }
    cout << (_k != 0? -1 : ans) << "\n";
    
    return 0;
}