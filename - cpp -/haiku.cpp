#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Kattis - haiku

//for each line, we can do dp to determine if there is a breakdown that matches the required number of syllables. 

bool is_valid(vector<string>& a, string& s, int tgt) {
    vector<vector<bool>> dp(s.size() + 1, vector<bool>(tgt + 1, false));
    dp[0][0] = true;
    for(int i = 0; i < s.size(); i++){
        for(int j = 0; j < tgt; j++){
            if(i != 0 && s[i - 1] == ' ') {
                dp[i][j] = dp[i - 1][j];
            }
            if(!dp[i][j]) {
                continue;
            }
            for(int k = 0; k < a.size(); k++){
                int nsize = a[k].size();
                if(i + nsize <= s.size() && s.substr(i, nsize) == a[k]) {
                    dp[i + nsize][j + 1] = true;
                }
            }
        }
    }
    return dp[s.size()][tgt];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    string s0, s1, s2;
    getline(cin, s0);
    getline(cin, s0);
    getline(cin, s1);
    getline(cin, s2);
    cout << (is_valid(a, s0, 5) && is_valid(a, s1, 7) && is_valid(a, s2, 5)? "haiku" : "come back next year") << "\n";
    
    return 0;
}
