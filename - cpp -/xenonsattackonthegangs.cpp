#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int getMax(vector<bool> &v, vector<vector<int>> &c, set<int> &s) {
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    int nn = 4;
    vector<int> a = {1, 2, 5, 1, 1};
    vector<int> pfx = {1, 3, 8, 9, 10};
    vector<int> sfx = {10, 9, 7, 2, 1};
    vector<vector<int>> dp(nn, vector<int>(nn));
    for(int k = 1; k < nn; k++){
        for(int l = 0; l < nn - k; l++){
            int r = l + k;
            dp[l][r] = pfx[l] * sfx[r];
            if(k != 1) {
                dp[l][r] += max(dp[l + 1][r], dp[l][r - 1]);
            }
            cout << l << " " << r << " : " << dp[l][r] << endl;
        }
    }
    cout << dp[0][nn - 1];
    
    return 0;
}
