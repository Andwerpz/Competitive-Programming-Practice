#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problem Set #1 (Spring 2023) A

//basic dp problem. 

//is this 0-1 knapsack? no, right? because it also wants to get the minimum. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for(int i = 0; i < n; i++){
        cin >> c[i];
    }
    vector<int> dp(x + 1, -1);
    dp[0] = 0;
    for(int i = 0; i < x; i++){
        if(dp[i] == -1){
            continue;
        }
        for(int j = 0; j < n; j++) {
            int next = i + c[j];
            if(next > x) {
                continue;
            }
            if(dp[next] == -1){
                dp[next] = dp[i] + 1;
            }
            dp[next] = min(dp[next], dp[i] + 1);
        }
    }
    cout << dp[x] << "\n";
    
    return 0;
}
