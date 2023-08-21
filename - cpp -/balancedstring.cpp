#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1860D

//initial greedy solution got hacked. 
//intended solution is dp. 

//lets try constructing the string from left to right. 
//dp[i][j][k] = min number of incorrect digits in the ith prefix where
//we've constructed the ith prefix
//there are j 0s in the ith prefix
//there are k 01 sequences in the ith prefix. 

//transitions are as follows
//if the next digit is a '0', then
//dp[i][j][k] -> dp[i + 1][j + 1][k] + (s[i] == '1'). 
//this one should be pretty obvious

//if the next digit is a '1', then
//dp[i][j][k] -> dp[i + 1][j][k + j] + (s[i] == '0').
//the number of 01 sequences ending on the newly added '1' character is exactly equal to the number of 0s in the string so far. 

//now, we want to extract the answer. i should obviously be n, and j should be equal to the count of 0s in 
//the given string. Since the sum of 01 + 10 sequences doesn't change when permuting the string, k can just be
//the sum divided by 2, since we want to balance the array. 

//since dp[i][j][k] computes the minimum number of incorrect digits, not the number of swaps, we should divide the answer by 2
//since each pair of incorrect digits can be fixed with 1 swap. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(n + 1, vector<int>(n * n, 1e9)));
    dp[0][0][0] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < dp[0][j].size(); k++){
                dp[1][j][k] = 1e9;
            }
        }
        for(int j = 0; j < n; j++){
            for(int k = 0; k < dp[0][j].size(); k++){
                if(dp[0][j][k] == 1e9){
                    continue;
                }
                //put a '0'
                dp[1][j + 1][k] = min(dp[1][j + 1][k], dp[0][j][k] + (s[i] == '1'));
                //put a '1'
                dp[1][j][k + j] = min(dp[1][j][k + j], dp[0][j][k] + (s[i] == '0'));
            }
        }
        swap(dp[0], dp[1]);
    }
    int cnt = 0;
    int zcnt = 0;
    int ocnt = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '0'){
            cnt += ocnt;
            zcnt ++;
        }
        if(s[i] == '1'){
            cnt += zcnt;
            ocnt ++;
        }
    }
    //cout << cnt << " " << zcnt << " " << ocnt << "\n";
    cout << dp[0][zcnt][cnt / 2] / 2 << "\n";
    
    return 0;
}
