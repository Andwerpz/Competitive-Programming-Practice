#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - halloweenloot

string s_ans = "";
int d_ans = 1e9;
int zero = 100 * 100 + 50;

void solve(vector<vector<bool>>& dp, vector<bool>& path, int i, int c_diff, vector<int>& a, vector<int>& b) {
    if(i == dp.size() - 1) {
        if(abs(c_diff - zero) <= d_ans) {
            string n_s_ans = "";
            for(int j = 0; j < path.size(); j++){
                n_s_ans.push_back(path[j]? 'A' : 'B');
            }
            if(d_ans == abs(c_diff - zero) && s_ans.size() != 0) {
                if(n_s_ans < s_ans) {
                    s_ans = n_s_ans;
                }
            }
            else {
                d_ans = abs(c_diff - zero);
                s_ans = n_s_ans;
            }
        }
        return;
    }
    if(dp[i][c_diff]) {
        return;
    }
    dp[i][c_diff] = true;
    //take a
    path.push_back(true);
    solve(dp, path, i + 1, c_diff + a[i], a, b);
    path.pop_back();
    //take b
    path.push_back(false);
    solve(dp, path, i + 1, c_diff - b[i], a, b);
    path.pop_back();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> b(n);
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    vector<vector<bool>> dp(n + 1, vector<bool>(100 * 100 * 2 + 100, false));
    vector<bool> path(0);
    solve(dp, path, 0, zero, a, b);
    cout << s_ans << "\n";
    
    return 0;
}
