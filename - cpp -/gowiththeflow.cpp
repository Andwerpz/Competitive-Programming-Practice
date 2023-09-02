#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2018 F

//brute force to find the maximum river. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> a(n);
    int minWidth = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        minWidth = max(minWidth, (int) a[i].size());
    }
    int ans = -1;
    int bestLineWidth = -1;
    int curLineWidth = minWidth;
    vector<vector<pair<int, pair<int, int>>>> dp(2, vector<pair<int, pair<int, int>>>(n * 80, {-1, {-2, 0}}));
    while(true) {
        //cout << ans << " " << curLineWidth << endl;
        int cwidth = 0;
        int crow = 0;
        vector<pair<int, int>> spaceInd(0);
        for(int i = 0; i < n; i++) {
            int nwidth = a[i].size();
            int nspaceind = cwidth;
            if(cwidth + nwidth <= curLineWidth) {
                if(nspaceind != 0){
                    //we can place it
                    //cout << "FOUND SPACE" << endl;
                    spaceInd.push_back({crow, nspaceind});
                }
                cwidth += nwidth + 1;
            }
            else {
                //we can't place it
                crow ++;
                cwidth = nwidth + 1;
            }
        }
        //cout << "NUM ROWS: " << crow + 1 << "\n";
        if(ans >= crow + 1) {
            break;
        }
        int prow = 0;
        for(int i = 0; i < spaceInd.size(); i++){
            int row = spaceInd[i].first;
            int col = spaceInd[i].second;
            if(row != prow) {
                swap(dp[0], dp[1]);
                prow = row;
            }
            dp[1][col] = {curLineWidth, {row, 1}};
            if(row != 0){
                if(col != 0 && dp[0][col - 1].first == curLineWidth && dp[0][col - 1].second.first == row - 1){
                    dp[1][col].second.second = max(dp[1][col].second.second, dp[0][col - 1].second.second + 1);
                }
                if(dp[0][col].first == curLineWidth && dp[0][col].second.first == row - 1){
                    dp[1][col].second.second = max(dp[1][col].second.second, dp[0][col].second.second + 1);
                }
                if(col != curLineWidth - 1 && dp[0][col + 1].first == curLineWidth && dp[0][col + 1].second.first == row - 1){
                    dp[1][col].second.second = max(dp[1][col].second.second, dp[0][col + 1].second.second + 1);
                }
            }
            if(dp[1][col].second.second > ans) {
                ans = dp[1][col].second.second;
                bestLineWidth = curLineWidth;
            }
        }
        curLineWidth ++;
    }
    cout << bestLineWidth << " " << ans << "\n";
    
    return 0;
}
