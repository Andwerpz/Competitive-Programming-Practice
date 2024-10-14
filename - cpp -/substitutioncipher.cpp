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

//Meta Hacker Cup 2024 Round 1 - D

//this solution is incorrect, but it's not really worth to upsolve imo. Too much casework. 
//you also have to consider when we must take the next character along with the next one (it happens when
//there is a '0' in front of the next one). Then, we can assign to the current '?' any element from '1' to '9'. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ifstream in("--in--.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    ll mod = 998244353;
    int t;
    cin >> t;
    int casi = 0;
    while(t--) {
        casi ++;
        string s;
        cin >> s;
        int k;
        cin >> k;
        k --;
        //get rid of '?' that are forced to be '1'
        int n = s.size();
        for(int i = 0; i < n - 1; i++){
            if(s[i] == '?' && s[i + 1] > '6' && s[i + 1] != '?') {
                s[i] = '1';
            }
        }
        //compute the kth largest string. 
        //if the last digit is a '?', it can be either:
        // '1' to '6' if previous is '2'
        // '1' to '9' otherwise
        //if previous digit is a '?', this becomes annoying. 
        //note that we should never assign a '?' to 0, because this only limits the amount of combinations. 
        if(s[n - 1] == '?') {
            if(n == 1 || s[n - 2] != '?'){
                //binary but with a twist
                if(n >= 2 && s[n - 2] == '2'){
                    s[n - 1] = '6' - (k % 6);
                    k /= 6;
                }
                else {
                    s[n - 1] = '9' - (k % 9);
                    k /= 9;
                }
                for(int i = n - 2; i >= 0; i--){
                    if(s[i] == '?') {
                        s[i] = (k % 2) ? '1' : '2';
                        k /= 2;
                    }
                }
            }
            else {
                //annoying D:
                //account for last 2 '?', and assign binary for rest. 
                int rem = k % 15;
                k /= 15;
                if(rem < 6){
                    s[n - 2] = '2';
                    s[n - 1] = '6' - rem;
                }
                else {
                    rem -= 6;
                    s[n - 2] = '1';
                    s[n - 1] = '9' - rem;
                }
                for(int i = n - 2; i >= 0; i--){
                    if(s[i] == '?') {
                        s[i] = (k % 2) ? '1' : '2';
                        k /= 2;
                    }
                }
            }
        }
        else {
            //can just assign as binary representation of k
            for(int i = n - 1; i >= 0; i--){
                if(s[i] == '?') {
                    s[i] = (k % 2) ? '1' : '2';
                    k /= 2;
                }
            }
        }
        //nr combinations. 
        vl dp(n + 1, 0);
        dp[0] = 1;
        for(int i = 0; i < n; i++){
            if(s[i] == '0'){
                //bruh
            }
            else {
                //take character individually
                dp[i + 1] = (dp[i + 1] + dp[i]) % mod;  
                //take next 2
                if(s[i] == '1' && i < n - 1){
                    dp[i + 2] = (dp[i + 2] + dp[i]) % mod;
                }
                else if(s[i] == '2' && i < n - 1 && s[i + 1] <= '6'){
                    dp[i + 2] = (dp[i + 2] + dp[i]) % mod;
                }
            }
        }
        cout << "Case #" << casi << ": " << s << " " << dp[n] << "\n";
    }
    
    return 0;
}