#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1203F2

//essentially the same as the easy version, except we keep a count of how many projects we do. 
//if we can't do a project, we just skip it and move onto the next one. 

//considering the negative projects is a little trickier though, as we need to use dp knapsack to solve 
//it. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, r;
    cin >> n >> r;
    vector<pair<int, int>> pos(0);
    vector<pair<int, int>> neg(0);
    int ans = 0;
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        if(b >= 0){
            pos.push_back({a, b});
        }
        else{
            neg.push_back({a, b});
        }
    }
    sort(pos.begin(), pos.end(), [] (pair<int, int>& a, pair<int, int>& b) {return a.first < b.first;});
    sort(neg.begin(), neg.end(), [] (pair<int, int>& a, pair<int, int>& b) {return (b.first + b.second) < (a.first + a.second);});
    for(int i = 0; i < pos.size(); i++){
        if(pos[i].first <= r){
            ans ++;
            r += pos[i].second;
        }
    }
    vector<int> dp(100000, -1);
    dp[r] = 0;
    int maxNeg = 0;
    for(int i = 0; i < neg.size(); i++){
        for(int j = neg[i].first; j < dp.size(); j++){
            if(dp[j] == -1 || j + neg[i].second < 0){
                continue;
            }
            dp[j + neg[i].second] = max(dp[j + neg[i].second], dp[j] + 1);
            maxNeg = max(maxNeg, dp[j + neg[i].second]);
        }
    }
    cout << (ans + maxNeg) << endl;
    
    return 0;
}
