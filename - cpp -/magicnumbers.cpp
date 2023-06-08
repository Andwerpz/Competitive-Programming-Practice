#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 628D

//digit dp problem. 

//dp[i][j][k][l] :
//i = num digits so far
//j = number % m
//k : if k == 1, then the number = ith prefix of max. 
//l : if l == 1, then last digit is d, else, last digit is not d. 

//base cases will come from when you start a new number from a prefix of 0s. 
//you can add them in as you go. 

//answer is sum of dp[n][0], where n is length of maximum num. 

//the mem constraints on this problem are pretty tight, so you can just save two i states at a time, swapping them when you fill one in. 

ll mod = 1e9 + 7;
vector<vector<int>> rem;

ll solve(string max, int m, int d) {
    int n = max.size();
    vector<vector<vector<vector<int>>>> dp(2, vector<vector<vector<int>>>(m, vector<vector<int>>(2, vector<int>(2, 0))));
    //dp[i][j][k][l] :
    //i = num digits so far
    //j = number % m
    //k : if k == 1, then the number = ith prefix of max. 
    //l : if l == 1, then last digit is d, else, last digit is not d. 
    for(int i = 0; i < n; i++){
        //reset
        for(int j = 0; j < m; j++){
            dp[1][j][0][0] = 0;
            dp[1][j][1][0] = 0;
            dp[1][j][0][1] = 0;
            dp[1][j][1][1] = 0;
        }
        //do base states as we go
        for(int j = 1; j < 10; j++){
            if(j == d) {
                continue;
            }
            if(i == 0 && j > (max[0] - '0')) {
                break;
            }
            int r = rem[i][j];
            //cout << "BASE : " << (i + 1) << " " << r  << " " << j << endl;
            if(i == 0 && j == (max[0] - '0')) {
                dp[1][r][1][0] += 1;
            }
            else {
                dp[1][r][0][0] += 1;
            }
        }
        //state transitions
        for(int j = 0; j < m; j++){
            //tight
            {
                int dig = max[i] - '0';
                //prev is d
                {  
                    //next digit cannot be d
                    //maintain tight
                    if(dig != d) {
                        int r = rem[i][dig];
                        int nxt = j + r;
                        if(nxt >= m) {
                            nxt -= m;
                        }
                        dp[1][(j + r) % m][1][0] += dp[0][j][1][1];
                        if(dp[1][(j + r) % m][1][0] >= mod){
                            dp[1][(j + r) % m][1][0] -= mod;
                        }
                    }
                    //don't maintain
                    for(int k = 0; k < dig; k++){
                        if(k == d) {
                            continue;
                        }
                        int r = rem[i][k];
                        dp[1][(j + r) % m][0][0] += dp[0][j][1][1];
                        if(dp[1][(j + r) % m][0][0] >= mod){
                            dp[1][(j + r) % m][0][0] -= mod;
                        }
                    }
                }
                //prev is not d
                {   
                    //next digit must be d. 
                    //maintain tight
                    if(dig == d) {
                        int r = rem[i][d];
                        dp[1][(j + r) % m][1][1] += dp[0][j][1][0];
                        if(dp[1][(j + r) % m][1][1] >= mod){
                            dp[1][(j + r) % m][1][1] -= mod;
                        }
                    }
                    //don't maintain
                    if(dig != d && d < dig) {
                        int r = rem[i][d];
                        dp[1][(j + r) % m][0][1] += dp[0][j][1][0];
                        if(dp[1][(j + r) % m][0][1] >= mod){
                            dp[1][(j + r) % m][0][1] -= mod;
                        }
                    }
                }
            }
            //not tight
            {
                //prev is d
                {
                    //next digit cannot be d
                    for(int k = 0; k < 10; k++){
                        if(k == d) {
                            continue;
                        }
                        int r = rem[i][k];
                        dp[1][(j + r) % m][0][0] += dp[0][j][0][1];
                        if(dp[1][(j + r) % m][0][0] >= mod){
                            dp[1][(j + r) % m][0][0] -= mod;
                        }
                    }
                }
                //prev is not d
                {
                    //next digit must be d
                    int r = rem[i][d];
                    dp[1][(j + r) % m][0][1] += dp[0][j][0][0];
                    if(dp[1][(j + r) % m][0][1] >= mod){
                        dp[1][(j + r) % m][0][1] -= mod;
                    }
                }
            }
        }
        //swap dp arrays
        swap(dp[0], dp[1]);
    }

    ll ans = 0;
    ans += dp[0][0][0][0];
    ans += dp[0][0][1][0];
    ans += dp[0][0][0][1];
    ans += dp[0][0][1][1];
    ans %= mod;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, d;
    cin >> m >> d;
    string a, b;
    cin >> a >> b;
    rem = vector<vector<int>>(a.size(), vector<int>(10, 0));
    for(int i = 0; i < 10; i++){
        rem[a.size() - 1][i] = i % m;
    }
    for(int i = a.size() - 1; i >= 1; i--){
        for(int j = 0; j < 10; j++){
            rem[i - 1][j] = (rem[i][j] * 10) % m;
        }
    }
    ll high = solve(b, m, d);
    ll low = solve(a, m, d);
    ll ans = high - low;
    //check if low is valid
    bool valid = true;
    int r = 0;
    for(int i = 0; i < a.size(); i++){
        r += rem[i][a[i] - '0'];
        r %= m;
        if((i % 2 == 1) ^ ((a[i] - '0') == d)) {
            valid = false;
        }
    }
    if(r != 0){
        valid = false;
    }
    if(valid) {
        ans ++;
    }
    if(ans < 0){
        ans += mod;
    }
    ans %= mod;
    cout << ans << "\n";
    
    return 0;
}
