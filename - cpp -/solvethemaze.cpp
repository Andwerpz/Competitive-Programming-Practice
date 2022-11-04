#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problemset 5G

//to guarantee that no bad people can get out, you just need to surround each one with walls. 

//then, just do a bfs from the exit. If you can reach all of the good people, and none of the bad people, 
//then it is possible to solve the maze. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<string> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};
        int gCnt = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(a[i][j] == 'G'){
                    gCnt ++;
                }
                if(a[i][j] != 'B'){
                    continue;
                }
                for(int k = 0; k < 4; k++){
                    int nr = i + dr[k];
                    int nc = j + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                        continue;
                    }
                    if(a[nr][nc] == '.'){
                        a[nr][nc] = '#';
                    }
                }
            }
        }
        stack<pair<int, int>> s;
        if(a[n - 1][m - 1] == '.') {
            s.push(pair<int, int>(n - 1, m - 1));
        }
        a[n - 1][m - 1] = '#';
        while(s.size() != 0){
            pair<int, int> next = s.top();
            s.pop();
            int r = next.first;
            int c = next.second;
            for(int k = 0; k < 4; k++){
                int nr = r + dr[k];
                int nc = c + dc[k];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    continue;
                }
                if(a[nr][nc] == '.' || a[nr][nc] == 'G' || a[nr][nc] == 'B'){
                    if(a[nr][nc] == 'B'){
                        gCnt = 100000;
                    }
                    if(a[nr][nc] == 'G'){
                        gCnt --;
                    }
                    a[nr][nc] = '#';
                    s.push(pair<int, int>(nr, nc));
                }
            }
        }
        cout << (gCnt == 0? "Yes\n" : "No\n");
    }
    
    return 0;
}
