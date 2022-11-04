#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problemset 5E

//simple floodfill problem, just do multiple passes. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    int sr, sc, dr, dc;
    cin >> sr >> sc >> dr >> dc;
    sr--;
    sc--;
    dr--;
    dc--;
    vector<vector<int>> a(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            a[i][j] = s[j] == '#'? -2 : -1;
        }
    }
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};
    vector<pair<int, int>> nextPass(0);
    nextPass.push_back(pair<int, int>(sr, sc));
    a[sr][sc] = 0;
    while(nextPass.size() != 0) {
        stack<pair<int, int>> s;
        for(pair<int, int> i : nextPass){
            s.push(i);
        }
        nextPass.clear();
        vector<pair<int, int>> jump(0);
        while(s.size() != 0){
            pair<int, int> next = s.top();
            s.pop();
            int r = next.first;
            int c = next.second;
            jump.push_back(next);
            for(int k = 0; k < 4; k++){
                int nr = r + dx[k];
                int nc = c + dy[k];
                if(nr < 0 || nc < 0 || nr >= n || nc > m){
                    continue;
                }
                if(a[nr][nc] != -1) {
                    continue;
                }
                a[nr][nc] = a[r][c];
                s.push(pair<int, int>(nr, nc));
            }
        }
        for(pair<int, int> i : jump) {
            int r = i.first;
            int c = i.second;
            for(int k = -2; k <= 2; k++){
                for(int l = -2; l <= 2; l++){
                    int nr = r + k;
                    int nc = c + l;
                    if(nr < 0 || nc < 0 || nr >= n || nc > m){
                    continue;
                    }
                    if(a[nr][nc] != -1) {
                        continue;
                    }
                    a[nr][nc] = a[r][c] + 1;
                    nextPass.push_back(pair<int, int>(nr, nc));
                }
            }
        }
    }
    cout << a[dr][dc] << "\n";
    
    return 0;
}
