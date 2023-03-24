#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 08 A

//dp

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(!cin.eof()) {
        int m;
        cin >> m;
        vector<int> a(m);
        for(int i = 0; i < m; i++){
            cin >> a[i];
        }
        vector<pair<bool, bool>> dp(n + 1, {false, false});
        dp[n].second = true;
        for(int i = n - 1; i >= 0; i--){
            //stan's turn
            for(int j = 0; j < a.size(); j++){
                if(i + a[j] > n){
                    continue;
                }
                dp[i].first |= dp[i + a[j]].second;
            }
            dp[i].second = true;
            for(int j = 0; j < a.size(); j++){
                if(i + a[j] > n){
                    continue;
                }
                dp[i].second &= dp[i + a[j]].first;
            }
        }
        cout << (dp[0].first? "Stan wins\n" : "Ollie wins\n");
        cin >> n;
    }
    
    return 0;
}
