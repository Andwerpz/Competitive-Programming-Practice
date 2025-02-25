#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Topcoder - 14535

//If n <= 26, then we can just make all strings just contain each character once. This will give us an instability and 
//similarity of 0. 

//If n > 26, then this doesn't work because we don't have enough characters. So our similarity will have to be greater
//than 0. 

//Therefore, we need to raise our instability. We can reserve the first two characters in the first string to generate a 
//bunch of instability, so a string like "abababab..." and we don't use 'a' or 'b' in any other string to keep the
//similarity low. 

//turns out we need two such strings to make it to 100. 

class BalancedStrings {
public:
    vector<string> findAny(int n) {
        vector<string> ans;
        if(n <= 26) {
            for(int i = 0; i < n; i++){
                ans.push_back(string(1, 'a' + i));
            }
        }   
        else {
            int sim = 0;
            n -= 3;
            ans.push_back("a");
            ans.push_back("a");
            ans.push_back("a");
            for(int i = 0; i < n; i++){
                sim += i / 20;
                ans.push_back(string(1, 'g' + (i % 20)));
            }
            for(int i = 0; i < 3; i++){
                int amt = min(99, sim);
                sim -= amt;
                for(int j = 0; j < amt; j++){
                    ans[i].push_back('a' + (1 - (j % 2)));
                }
                for(int j = 0; j < ans[i].size(); j++) ans[i][j] += i * 2;
            }
        }
        return ans;
    }
};

vector<string> solve(int n) {
    vector<string> ans;
    if(n <= 26) {
        for(int i = 0; i < n; i++){
            ans.push_back(string(1, 'a' + i));
        }
    }   
    else {
        int sim = 0;
        n -= 3;
        ans.push_back("a");
        ans.push_back("a");
        ans.push_back("a");
        for(int i = 0; i < n; i++){
            sim += i / 20;
            ans.push_back(string(1, 'g' + (i % 20)));
        }
        for(int i = 0; i < 3; i++){
            int amt = min(99, sim);
            sim -= amt;
            for(int j = 0; j < amt; j++){
                ans[i].push_back('a' + (1 - (j % 2)));
            }
            for(int j = 0; j < ans[i].size(); j++) ans[i][j] += i * 2;
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> ans = solve(n);
    for(string x : ans) cout << x << "\n";
    
    return 0;
}