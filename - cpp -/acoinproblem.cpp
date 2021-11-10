
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//DMOJ - acoinproblem

//since we have costs up to v, and we have n different types of coins. That means that we can generate a dp state for each number of coins from 1 - n in O(v * n) time
//which is less than 10^9.

//since the memory limit is very tight, we can't save all of our dp states at once, we need to generate it, use it, then move on. This doesn't really change our solution though.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, v;
    cin >> n >> v;
    vector<int> dp(100001);
    vector<int> coins(n);
    for(int i = 0; i < n; i++){
        cin >> coins[i];
    }
    vector<vector<int>> queries(v);
    for(int i = 0; i < v; i++){
        int c, l;
        cin >> c >> l;
        l --;
        queries[i] = {c, l, i};
        //cout << c << " " << l << " " << i << endl;
    }
    sort(queries.begin(), queries.end(), [&](vector<int> a, vector<int> b) -> bool {return a[1] < b[1];});
    fill(dp.begin(), dp.end(), -1);
    dp[0] = 0;
    int pointer = 0;
    for(int i = 0; i < n; i++){
        int nextCoin = coins[i];
        for(int j = 0; j < dp.size(); j++){
            if(dp[j] != -1 && j + nextCoin < dp.size()){
                if(dp[j + nextCoin] == -1){
                    dp[j + nextCoin] = dp[j] + 1;
                }
                else{
                    dp[j + nextCoin] = min(dp[j + nextCoin], dp[j] + 1); 
                }
            }
            //cout << dp[j] << " ";
        }
        //cout << endl;
        while(pointer != queries.size() && queries[pointer][1] == i){
            if(queries[pointer][0] < dp.size()){
               queries[pointer][0] = dp[queries[pointer][0]]; 
            }
            
            pointer ++;
        }
    }  
    //cout << "ANS\n";
    sort(queries.begin(), queries.end(), [&](vector<int> a, vector<int> b) -> bool {return a[2] < b[2];});
    for(int i = 0; i < queries.size(); i++){
        cout << queries[i][0] << endl;
    }

    return 0;
}



