#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problemset 5B

//basic floodfill counting connected components. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++) {
            a[i][j] = s[j] == '#'? 1 : 0;
        }
    }
    int ans = 0;
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            if(a[i][j] == 1) {
                continue;
            }
            ans ++;
            stack<pair<int, int>> s;
            a[i][j] = 1;
            s.push(pair<int, int>(i, j));
            while(s.size() != 0) {
                pair<int, int> next = s.top();
                s.pop();
                int r = next.first;
                int c = next.second;
                for(int k = 0; k < 4; k++){
                    int nR = r + dx[k];
                    int nC = c + dy[k];
                    if(nR < 0 || nR >= n || nC < 0 || nC >= m) {
                        continue;
                    }
                    if(a[nR][nC] == 1) {
                        continue;
                    }
                    a[nR][nC] = 1;
                    s.push(pair<int, int>(nR, nC));
                }
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
