
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1193

//we can generate the path from A to B, starting from B. By doing a BFS search from B, we can guarantee to find
//the length of the shortest path from A to B.

//to actually generate the path, we can record for each cell, in which direction should you move to get back to B.
//we could start from A to do this backtracking, but starting it from B is much more straightforward, and it supports
//path reconstruction from multiple points in the grid.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for(int i = 0; i < n; i++){
        cin >> grid[i];
    }
    vector<vector<bool>> v(n, vector<bool>(m));
    vector<vector<char>> backtrack(n, vector<char>(m));
    bool isValid = true;
    string ans = "";
    vector<int> dr = {-1, 1, 0, 0}; //U, D, L, R
    vector<int> dc = {0, 0, -1, 1};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] != 'B'){
                continue;
            }
            //we create the path from a to b, starting from b
            bool foundA = false;
            pair<int, int> aRC;
            v[i][j] = true;
            queue<pair<int, int>> s;    //r, c
            s.push({i, j});
            while(s.size() != 0){
                int r = s.front().first;
                int c = s.front().second;
                s.pop();
                for(int k = 0; k < 4; k++){
                    int nextR = r + dr[k];
                    int nextC = c + dc[k];
                    if(nextR < 0 || nextC < 0 || nextR >= n || nextC >= m || grid[nextR][nextC] == '#' || v[nextR][nextC]){
                        continue;
                    }
                    if(grid[nextR][nextC] == 'A'){
                        foundA = true;
                        aRC = {nextR, nextC};
                    }
                    v[nextR][nextC] = true;
                    s.push({nextR, nextC});
                    //what move is required from the next cell to get back to the cur cell
                    if(k == 0){
                        backtrack[nextR][nextC] = 'D';
                    }
                    else if(k == 1){
                        backtrack[nextR][nextC] = 'U';
                    }
                    else if(k == 2){
                        backtrack[nextR][nextC] = 'R';
                    }
                    else if(k == 3){
                        backtrack[nextR][nextC] = 'L';
                    }
                }
            }
            if(!foundA){
                isValid = false;
                goto outer;
            }
            //generate ans
            int curR = aRC.first;
            int curC = aRC.second;
            while(true){
                ans.push_back(backtrack[curR][curC]);
                if(backtrack[curR][curC] == 'U'){
                    curR --;
                }
                else if(backtrack[curR][curC] == 'D'){
                    curR ++;
                }
                else if(backtrack[curR][curC] == 'L'){
                    curC --;
                }
                else if(backtrack[curR][curC] == 'R'){
                    curC ++;
                }
                if(grid[curR][curC] == 'B'){
                    break;
                }
            }
            goto outer;
        }
    }
    outer:;
    if(!isValid){
        cout << "NO\n";
    }
    else {
        cout << "YES\n";
        cout << ans.size() << endl << ans << endl;
    }
    
    return 0;
}
