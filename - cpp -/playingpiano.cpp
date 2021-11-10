
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1032C

//simple dp. 

//for each prefix of keys, generate the set of keys that you can end on. When trying to generate the next set of keys, you just have to try for each key, all other valid
//keys of the previous set. Since there are only 5 keys, 25 combinations * n, it's fast enough to pass.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> keys(n);
    for(int i = 0; i < n; i++){
        cin >> keys[i];
    }
    vector<vector<int>> dp(n);
    dp[0] = vector<int>(5, 0);
    for(int i = 1; i < n; i++){
        dp[i] = vector<int>(5, -1);
    }
    for(int i = 1; i < n; i++){
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                if(dp[i - 1][k] != -1 && j != k){
                    if(keys[i - 1] > keys[i]){
                        if(k > j){
                            dp[i][j] = k;
                            break;
                        }
                    }
                    else if(keys[i - 1] < keys[i]){
                        if(k < j){
                            dp[i][j] = k;
                            break;
                        }
                    }
                    else{
                        dp[i][j] = k;
                        break;
                    }
                }
            }
        }
    }
    bool isValid = false;
    int pointer = 0;
    for(int i = 0; i < 5; i++){
        if(dp[n - 1][i] != -1){
            isValid = true;
            pointer = i;
            break;
        }
    }
    if(isValid){
        vector<int> ans(n);
        ans[n - 1] = pointer + 1;
        for(int i = n - 1; i > 0; i--){
            pointer = dp[i][pointer];
            ans[i - 1] = pointer + 1;
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    else{
        cout << "-1\n";
    }

    return 0;
}



