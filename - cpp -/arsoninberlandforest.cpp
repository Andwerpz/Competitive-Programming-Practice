#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1227E

//notice that each initially ignited tree will burn a square around it. Then, the problem reduces to finding the largest
//odd side length of square that we can paste around to fully describe all of the 'X's. We can binary search over the 
//side length, and use prefix sums to check a side length in O(n * m) time. 

bool is_valid(vector<vector<int>>& pfx, vector<vector<int>>& g, int t, int n, int m) {
    vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int tr = i - t;
            int tc = j - t;
            int br = i + t;
            int bc = j + t;
            if(tr < 0 || tc < 0 || br >= n || bc >= m){
                continue;
            }
            br ++;
            bc ++;
            int sum = pfx[br][bc] + pfx[tr][tc] - pfx[br][tc] - pfx[tr][bc];
            if(sum == (2 * t + 1) * (2 * t + 1)) {
                a[tr][tc] ++;
                a[br][bc] ++;
                a[tr][bc] --;
                a[br][tc] --;
            }
        }
    }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if(i != 0){
                a[i][j] += a[i - 1][j];
            }
            if(j != 0){
                a[i][j] += a[i][j - 1];
            }
            if(i != 0 && j != 0){
                a[i][j] -= a[i - 1][j - 1];
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j] == 0){
                continue;
            }
            if(a[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m, 0));
    vector<vector<int>> pfx(n + 1, vector<int>(m + 1, 0));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            g[i][j] = s[j] == 'X'? 1 : 0;
            pfx[i + 1][j + 1] = g[i][j];
        }
    }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if(i != 0) {
                pfx[i][j] += pfx[i - 1][j];
            }
            if(j != 0){
                pfx[i][j] += pfx[i][j - 1];
            }
            if(i != 0 && j != 0){
                pfx[i][j] -= pfx[i - 1][j - 1];
            }
        }
    }
    int low = 0;
    int high = min(n, m);
    int ans = low;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(is_valid(pfx, g, mid, n, m)) {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    cout << ans << "\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int tr = i - ans;
            int tc = j - ans;
            int br = i + ans;
            int bc = j + ans;
            if(tr < 0 || tc < 0 || br >= n || bc >= m){
                cout << ".";
                continue;
            }
            int sum = pfx[br + 1][bc + 1] + pfx[tr][tc] - pfx[br + 1][tc] - pfx[tr][bc + 1];
            if(sum == (2 * ans + 1) * (2 * ans + 1)) {
                cout << "X";
            }
            else {
                cout << ".";
            }
        }
        cout << "\n";
    }
    
    return 0;
}