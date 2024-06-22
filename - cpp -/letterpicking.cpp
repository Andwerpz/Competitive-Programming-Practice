#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1728D

//aughfhasd
// - 09/08/2022 andrew
//he certainly has quite a way with words. 

//this problem is actually pretty standard dp. Tricky part is probably implementation details, and thinking about
//how exactly you should update the dp states. 

int figure_out(int ret, char a, char b) {
    if(ret != 0){
        return ret;
    }
    if(a == b){
        return 0;
    }
    return a < b? 1 : -1;
}

int solve(vector<vector<int>>& dp, string& s, int l, int r) {
    if(l == r){
        return 0;   //tie
    }
    if(dp[l][r] != -2){
        return dp[l][r];
    }   
    int al, ar;
    //alice takes left
    {   
        //bob takes left
        int bl = figure_out(solve(dp, s, l + 2, r), s[l], s[l + 1]);
        //bob takes right
        int br = figure_out(solve(dp, s, l + 1, r - 1), s[l], s[r - 1]);
        al = min(bl, br);
    }
    //alice takes right
    {
        //bob takes left
        int bl = figure_out(solve(dp, s, l + 1, r - 1), s[r - 1], s[l]);
        //bob takes right
        int br = figure_out(solve(dp, s, l, r - 2), s[r - 1], s[r - 2]);
        ar = min(bl, br);
    }
    int ans = max(al, ar);
    dp[l][r] = ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, -2));   //1 : A wins, 0 : tie, -1 : B wins
        int ans = solve(dp, s, 0, n);
        cout << (ans == 0? "Draw" : (ans == 1? "Alice" : "Bob")) << "\n";
    }
    
    return 0;
}
