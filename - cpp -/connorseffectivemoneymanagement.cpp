#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ACPC Weekly Problem Set 3 Fall 2023 B

//classic coin change dp

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> dp(x + 1, 1e9);
    dp[0] = 0;
    for(int i = 0; i < x; i++){
        if(dp[i] == 1e9){
            continue;
        }
        for(int j = 0; j < n; j++){
            int next = i + a[j];
            if(next <= x){
                dp[next] = min(dp[next], dp[i] + 1);
            }
        }
    }
    cout << (dp[x] == 1e9? -1 : dp[x]) << "\n";
    
    return 0;
}
