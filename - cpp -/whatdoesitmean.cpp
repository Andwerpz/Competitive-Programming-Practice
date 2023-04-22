#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 11 H

//1 state dp, find out how many meanings for each suffix. 

ll mod = 1e9 + 7;

ll solve(string& name, vector<string>& a, vector<ld>& mean, int i, vector<vector<bool>>& v, vector<ll>& dp) {
    if(dp[i] != -1){
        return dp[i];
    }
    if(i > name.size()){
        return 0;
    }
    ll ans = 0;
    int rem = name.size() - i;
    for(int j = 0; j < a.size(); j++){
        if(v[j][i]) {
            //cout << "USING : " << a[j] << " INDEX : " << i << "\n";
            ll add = solve(name, a, mean, i + a[j].size(), v, dp);
            add *= mean[j];
            ans += add % mod;
            if(ans >= mod){
                ans -= mod;
            }
        }
    }
    dp[i] = ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    string name;
    cin >> name;
    vector<string> a(n);
    vector<ld> mean(n);
    vector<vector<bool>> v(n, vector<bool>(name.size(), false));
    for(int i = 0; i < n; i++){
        cin >> a[i] >> mean[i];
        for(int j = 0; j < name.size(); j++){
            //cout << "I : " << i << " J : " << j << "\n";
            int rem = name.size() - j;
            if(rem < a[i].size()) {
                break;
            }
            v[i][j] = true;
            for(int k = 0; k < a[i].size(); k++){
                if(a[i][k] != name[k + j]){
                    //cout << k << "\n";
                    v[i][j] = false;
                }
            }
        }
    }
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < name.size(); j++){
    //         cout << v[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    vector<ll> dp(name.size() + 1, -1);
    dp[name.size()] = 1;
    cout << solve(name, a, mean, 0, v, dp) << "\n";
    
    return 0;
}
