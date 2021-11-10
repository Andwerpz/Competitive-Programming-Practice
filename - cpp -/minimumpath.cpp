
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1031D

//I like this problem, a good mix of greedy and dp. 

//since you want to minimize the lexographic value, what you first want to do is calculate the maximum prefix of 'a's that you can put on your answer.
//to do this, you can just do a brute force dp approach. 

//now, out of all the maximum prefixes, you need to calculate the maximum suffix you can put. Doing this is simple as well. Just take the minimum every time
//and save each position that gives you the minimum.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<string> grid(n);
    for(int i = 0; i < n; i++){
        cin >> grid[i];
    }
    vector<vector<int>> dp(n);
    for(int i = 0; i < n; i++){
        dp[i] = vector<int>(n, -1);
    }
    dp[0][0] = k - (grid[0][0] == 'a'? 0 : 1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int max = -2;
            if(i - 1 >= 0){
                max = std::max(max, dp[i - 1][j] - 1);
            }
            if(j - 1 >= 0){
                max = std::max(max, dp[i][j - 1] - 1);
            }
            if(grid[i][j] == 'a'){
                max ++;
            }
            dp[i][j] = std::max(max, dp[i][j]);
        }
    }
    int maxDist = 0;
    string ans = "";
    set<pair<int, int>> s;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(dp[i][j] >= 0){
                int curDist = i + j + 1;
                if(curDist > maxDist){
                    maxDist = curDist;
                    s = set<pair<int, int>>();
                    s.insert({i, j});
                }
                else if(curDist == maxDist){
                    s.insert({i, j});
                }
            }
        }
    }
    for(int i = 0; i < maxDist; i++){
        ans += "a";
    }
    if(maxDist == 0){
        ans += grid[0][0];
        s.insert({0, 0});
    }
    while(true){
        if(ans.size() == n * 2 - 1){
            break;
        }
        set<pair<int, int>> nextS;
        char min = 'z';
        for(pair<int, int> i : s){
            int x = i.first;
            int y = i.second;
            if(x + 1 < n){
                min = std::min(min, grid[x + 1][y]);
                nextS.insert({x + 1, y});
            }
            if(y + 1 < n){
                min = std::min(min, grid[x][y + 1]);
                nextS.insert({x, y + 1});
            }
        }
        ans += min;
        s = set<pair<int, int>>();
        for(pair<int, int> i : nextS){
            int x = i.first;
            int y = i.second;
            if(grid[x][y] == min){
                s.insert({x, y});
            }
        }
    }
    cout << ans << endl;

    return 0;
}



