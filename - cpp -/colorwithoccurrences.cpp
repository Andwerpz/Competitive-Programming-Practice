#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1714D

//notice the extremely small input sizes. You can prob brute force. 

//to solve, just use dp. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        int n;
        cin >> n;
        vector<string> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> dp(s.size() + 1, -1);
        vector<pair<int, int>> b(s.size() + 1, {-1, -1});
        dp[0] = 0;
        for(int i = 0; i < s.size(); i++){
            if(dp[i] == -1){
                break;
            }
            int maxl = 0;
            int maxi = -1;
            for(int j = 0; j < n; j++){
                if(i + a[j].size() > s.size()) {
                    continue;
                }
                if(s.substr(i, a[j].size()) == a[j]) {
                    if(maxl < a[j].size()) {
                        maxl = a[j].size();
                        maxi = j;
                    }
                }
            }
            //cout << i << " " << maxl << "\n";
            for(int j = 0; j < maxl; j++){
                if(dp[i + j + 1] == -1){
                    dp[i + j + 1] = 10000;
                }
                if(dp[i + j + 1] > dp[i] + 1){
                    dp[i + j + 1] = dp[i] + 1;
                    b[i + j + 1] = {maxi, i};
                }
            }
            //cout << b[i].second << "\n";
        }
        if(dp[s.size()] != -1) {
            cout << dp[s.size()] << "\n";
            int ind = b[s.size()].second;
            int aind = b[s.size()].first;
            while(ind != -1){
                cout << (aind + 1) << " " << (ind + 1) << "\n";
                aind = b.at(ind).first;
                ind = b.at(ind).second;
            }
        }
        else {
            cout << "-1\n";
        }
    }
    
    return 0;
}
