#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//2023-2024 ICPC Asia Jakarta Regional A

//brute force greedy backtracking. 

vector<int> dr = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
vector<int> dc = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

string solve(int r, int c, vector<string>& g, vector<vector<bool>>& v, int rem) {
    if(rem == 1){
        return string(1, g[r][c]);
    }
    v[r][c] = true;
    string ans = "ZZZZZ";
    for(int i = 0; i < 9; i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(nr < 0 || nr >= 3 || nc < 0 || nc >= 3) {
            continue;
        }
        if(v[nr][nc]) {
            continue;
        }
        string next = g[r][c] + solve(nr, nc, g, v, rem - 1);
        if(next < ans) {
            ans = next;
        }
    }
    v[r][c] = false;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string ans = "ZZZZZZ";
    vector<string> g(3);
    for(int i = 0; i < 3; i++){
        cin >> g[i];
    }
    vector<vector<bool>> v(3, vector<bool>(3, false));
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            string next = solve(i, j, g, v, 3);
            if(next < ans) {
                ans = next;
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
