#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//UTPC Contest 01-26-24 Div. 2 - D

//first, sort the numbers. Then, it's straightforwards n^2 dp.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<int> dp(n, 1);
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(a[j] % a[i] == 0){
                dp[j] = max(dp[j], dp[i] + 1);
            }
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << "\n";
    
    return 0;
}
