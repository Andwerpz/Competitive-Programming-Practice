#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ACPC Weekly Problem Set 3 Fall 2023 E

//classic dp

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> dp(n, 1e9 * 2);
    dp[0] = 0;
    for(int i = 0; i < n; i++){
        if(i < n - 1){
            dp[i + 1] = min(dp[i + 1], dp[i] + abs(a[i] - a[i + 1]));
        }
        if(i < n - 2) {
            dp[i + 2] = min(dp[i + 2], dp[i] + abs(a[i] - a[i + 2]));
        }
    }
    cout << dp[n - 1] << "\n";
    
    return 0;
}
