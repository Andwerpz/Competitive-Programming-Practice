#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2010 G

//instead of making a round trip, we can think of this as instead two trips originating from island 0, going to 
//island n - 1, while visiting every island on the way. 

//dp[i][j] is the minimum total distance where trip 1 has reached island i, and trip 2 has reached island j. 

ld best_ans = 1e18;
vector<int> best_path;

ld dist(pair<int, int>& a, pair<int, int>& b) {
    return sqrt((ld) pow(a.first - b.first, 2) + (ld) pow(a.second - b.second, 2));
}

ld round_hund(ld a) {
    return round(a * 100.0) / 100.0;
}

void dp_assign(vector<vector<ld>>& dp, vector<vector<pair<int, int>>>& prev, ld val, int i, int j, int pi, int pj) {
    if(val < dp[i][j]) {
        dp[i][j] = val;
        prev[i][j] = {pi, pj};
    }
}

void solve(vector<pair<int, int>>& a, int b1, int b2) {
    int n = a.size();
    vector<vector<pair<int, int>>> prev(n, vector<pair<int, int>>(n));
    vector<vector<ld>> dp(n, vector<ld>(n, 1e9));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == n - 1 && j == n - 1) {
                continue;
            }
            if(i == n - 1) {
                dp_assign(dp, prev, dp[i][j] + dist(a[j], a[n - 1]), n - 1, n - 1, i, j);
                continue;
            }
            else if(j == n - 1){
                dp_assign(dp, prev, dp[i][j] + dist(a[i], a[n - 1]), n - 1, n - 1, i, j);
                continue;
            }
            int next = max(i, j) + 1;
            if(next == b1 || (next != b1 && next != b2)) {
                dp_assign(dp, prev, dp[i][j] + dist(a[i], a[next]), next, j, i, j);
            }
            if(next == b2 || (next != b1 && next != b2)) {
                dp_assign(dp, prev, dp[i][j] + dist(a[j], a[next]), i, next, i, j);
            }
        }
    }
    ld ans = dp[n - 1][n - 1];
    if(ans < best_ans) {
        best_ans = ans;
        vector<int> path_0(0);
        vector<int> path_1(0);
        pair<int, int> state = {n - 1, n - 1};
        while(state.first != 0 || state.second != 0) {
            //cout << state.first << " " << state.second << endl;
            pair<int, int> pstate = prev[state.first][state.second];
            if(pstate.first != state.first) {
                path_0.push_back(pstate.first);
            }
            else {
                path_1.push_back(pstate.second);
            }
            state = pstate;
        }
        reverse(path_0.begin(), path_0.end());
        best_path = vector<int>(0);
        for(int i = 0; i < path_0.size(); i++){
            best_path.push_back(path_0[i]);
        }
        best_path.push_back(n - 1);
        for(int i = 0; i < path_1.size(); i++){
            best_path.push_back(path_1[i]);
        }
        if(best_path[1] != 1){
            reverse(best_path.begin(), best_path.end());
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, b1, b2;
    cin >> n >> b1 >> b2;
    int caseno = 0;
    while(n != 0){
        caseno ++;
        cout << "Case " << caseno << ": ";
        vector<pair<int, int>> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].first >> a[i].second;
        }
        best_ans = 1e18;
        solve(a, b1, b2);
        solve(a, b2, b1);
        cout << fixed << setprecision(2) << round_hund(best_ans) << "\n";
        for(int i = 0; i < best_path.size(); i++){
            cout << best_path[i] << " \n"[i == best_path.size() - 1];
        }
        cin >> n >> b1 >> b2;
    }
    
    return 0;
}
