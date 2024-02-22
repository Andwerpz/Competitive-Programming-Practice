#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1928E

//first, note that any a_i % y is always going to equal x % y. Since we know the remainder of every
//element mod y, we can just subtract from s, (x % y) * n, and subtract (x % y) from every element.

//now, we can just assume that every a_i % y == 0. Now, if s % y != 0, then it's impossible to make.

//if s is divisible by y, then we might as well divide every value by y, and y := 1. Now, all we
//need to check is if it is possible to create a bunch of disjoint ascending sequences such that 
//the total length is n, and it adds up to s / y. 

//to do so, we can use dp :))

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<ll> sums(1e6, 0);
    for(int i = 1; i < sums.size(); i++){
        sums[i] = sums[i - 1] + i - 1;
    }
    int t;
    cin >> t;
    string fout = "";
    while(t--){
        ll n, x, y, s;
        cin >> n >> x >> y >> s;
        ll cur = x / y;
        ll rem = x % y;
        s -= rem * n;
        if(s < 0 || s % y != 0){
            fout += "NO\n";
            continue;
        }
        s /= y;
        vector<ll> ans(0);
        ans.push_back(x);
        s -= cur;
        if(s < 0){
            fout += "NO\n";
            continue;
        }
        //see if we can make the remaining s using a bunch of disjoint ascending sequences
        vector<ll> dp(s + 1, 1e9);
        vector<int> prev(s + 1, -1);
        //base cases
        {
            int sum = 0;
            int ptr = cur;
            int cnt = 0;
            while(sum <= s) {
                dp[sum] = cnt;
                ptr ++;
                cnt ++;
                sum += ptr;
            }
        }
        //do dp
        for(int i = 0; i < s; i++){
            for(int j = 1; j < sums.size(); j++) {
                if(i + sums[j] > s){
                    break;
                }
                if(dp[i] + j < dp[i + sums[j]]) {
                    dp[i + sums[j]] = dp[i] + j;
                    prev[i + sums[j]] = i;
                }
            }
        }
        //does answer exist?
        if(dp[s] > n - 1){
            fout += "NO\n";
            continue;
        }
        //construct answer
        vector<int> cnts(0);
        {
            int ptr = s;
            while(true) {
                if(prev[ptr] == -1){
                    cnts.push_back(dp[ptr]);
                    break;
                }
                int next = prev[ptr];
                cnts.push_back(dp[ptr] - dp[next]);
                ptr = next;
            }
            reverse(cnts.begin(), cnts.end());
        }
        for(int i = 0; i < cnts.size(); i++){
            for(int j = 0; j < cnts[i]; j++){
                cur ++;
                ans.push_back(cur * y + rem);
            }
            cur = -1;
        }
        while(ans.size() < n) {
            ans.push_back(rem);
        }
        fout += "YES\n";
        for(int i = 0; i < ans.size(); i++){
            fout += to_string(ans[i]) + " \n"[i == n - 1];
        }
    }
    cout << fout;
    
    return 0;
}
