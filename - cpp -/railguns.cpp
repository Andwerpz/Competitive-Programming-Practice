#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1840F

//note that there are only 100 railgun shots, and the maximum amount of cells is 10^4. This means we can do 
//one full bfs per railgun shot. 

//worst case, all the railgun shots are at different times

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> dr = {1, 0};
    vector<int> dc = {0, 1};
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        n ++;
        m ++;
        int r;
        cin >> r;
        vector<vector<int>> shots(r, vector<int>(4));
        for(int i = 0; i < r; i++){
            cin >> shots[i][0] >> shots[i][1] >> shots[i][2];
        }
        sort(shots.begin(), shots.end());
        int curT = 1;
        for(int i = 0; i < r; i++){
            if(i == 0 || shots[i][0] != shots[i - 1][0]) {
                curT ++;
            }
            shots[i][3] = curT;
        }
        vector<vector<bool>> v(n, vector<bool>(m, false));
        v[0][0] = true;
        int ans = -1;
        int curShot = 0;
        int timeSum = 0;
        while(true) {
            int time;
            if(curShot == 0){
                time = shots[0][0];
            }
            else if(curShot == shots.size()) {
                time = 1e9;
            }
            else {
                time = shots[curShot][0] - shots[curShot - 1][0];
            }
            //cout << "TIME : " << time << "\n";
            vector<vector<int>> dist(n, vector<int>(m, 1e9));
            queue<pair<int, int>> q;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    if(v[i][j]) {
                        dist[i][j] = 0;
                        q.push({i, j});
                    }
                }
            }
            if(q.size() == 0){
                //we dead
                break;
            }
            while(q.size() != 0) {
                int row = q.front().first;
                int col = q.front().second;
                q.pop();
                for(int i = 0; i < dr.size(); i++){
                    int nr = row + dr[i];
                    int nc = col + dc[i];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m) {
                        continue;
                    }
                    if(v[nr][nc]) {
                        continue;
                    }
                    v[nr][nc] = true;
                    dist[nr][nc] = dist[row][col] + 1;
                    q.push({nr, nc});
                }
            }
            //prune visited array
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    v[i][j] = dist[i][j] <= time;
                }
            }
            //do the shots
            int fshot = curShot == shots.size()? -1 : shots[curShot][3];
            while(curShot < shots.size() && shots[curShot][3] == fshot) {
                if(shots[curShot][1] == 1) {
                    //horizontal
                    for(int i = 0; i < m; i++){
                        v[shots[curShot][2]][i] = false;
                    }
                }
                else {
                    //vertical
                    for(int i = 0; i < n; i++){
                        v[i][shots[curShot][2]] = false;
                    }
                }
                curShot ++;
            }
            //check if reached end
            if(dist[n - 1][m - 1] <= time - 1) {
                ans = timeSum + dist[n - 1][m - 1];
                break;
            }
            if(v[n - 1][m - 1] && dist[n - 1][m - 1] <= time) {
                ans = timeSum + dist[n - 1][m - 1];
                break;
            }
            timeSum += time;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
