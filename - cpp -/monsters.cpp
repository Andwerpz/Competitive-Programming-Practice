
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1194

//it can be shown that if the player is closer to an exit cell than a monster, then the player can always get to
//the exit by taking the shortest path from the start location to the exit cell.

//if the monster is closer or the same distance to the exit than the player, then the player always gets caught

//Since we have multiple exits (all the edge cells), we need a good way to find which edge cell, if any, is closer
//to the player than any of the monsters. 

//consider the case where there is only 1 monster. We can easily do a bfs search starting from the monster to calculate
//how far away this monster is from all the exit cells. Expanding this to multiple monsters isn't that hard, we just
//need to have multiple starting points. 

//calculating the distance from the player start to the exit cells is the same as the case with only 1 monster.

//once we calulate all the distances, we can just take a look at all exit cells to see if there exists one that is closer
//to the player than it is to any monster.

//when we have the start and end cells, it's just a matter of finding the shortest path between them, and backtracking
//to generate the moves required.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for(int i = 0; i < n; i++){
        cin >> grid[i];
    }
    vector<vector<int>> monsterDist(n, vector<int>(m, 1e9));
    vector<vector<bool>> v(n, vector<bool>(m, false));
    queue<vector<int>> q;    //r, c
    pair<int, int> startLoc;
    //gather all monsters
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == 'M'){
                q.push({i, j, 0});
                monsterDist[i][j] = 0;
            }
            else if(grid[i][j] == 'A'){
                startLoc = {i, j};
            }
        }
    }
    vector<int> dr = {-1, 1, 0, 0}; //U, D, L, R
    vector<int> dc = {0, 0, -1, 1};
    while(q.size() != 0){
        int r = q.front()[0];
        int c = q.front()[1];
        int val = q.front()[2];
        q.pop();
        for(int i = 0; i < 4; i++){
            int nextR = r + dr[i];
            int nextC = c + dc[i];
            if(nextR < 0 || nextC < 0 || nextR >= n || nextC >= m || v[nextR][nextC] || grid[nextR][nextC] == '#' || monsterDist[nextR][nextC] <= val + 1){
                continue;
            }
            v[nextR][nextC] = true;
            monsterDist[nextR][nextC] = val + 1;
            q.push({nextR, nextC, val + 1});
        }
    }
    //generate dist from player
    vector<vector<int>> playerDist(n, vector<int>(m, 1e9));
    v = vector<vector<bool>>(n, vector<bool>(m, false));
    q.push({startLoc.first, startLoc.second, 0});
    playerDist[startLoc.first][startLoc.second] = 0;
    while(q.size() != 0){
        int r = q.front()[0];
        int c = q.front()[1];
        int val = q.front()[2];
        q.pop();
        for(int i = 0; i < 4; i++){
            int nextR = r + dr[i];
            int nextC = c + dc[i];
            if(nextR < 0 || nextC < 0 || nextR >= n || nextC >= m || v[nextR][nextC] || grid[nextR][nextC] == '#' || playerDist[nextR][nextC] <= val + 1){
                continue;
            }
            v[nextR][nextC] = true;
            playerDist[nextR][nextC] = val + 1;
            q.push({nextR, nextC, val + 1});
        }
    }
    //check along edges to see if there is an edge cell with player dist < monster dist
    pair<int, int> endLoc;
    bool isValid = false;
    for(int i = 0; i < n; i++){
        if(monsterDist[i][0] > playerDist[i][0]){
            endLoc = {i, 0};
            isValid = true;
        }
        else if(monsterDist[i][m - 1] > playerDist[i][m - 1]){
            endLoc = {i, m - 1};
            isValid = true;
        }
    }
    for(int i = 0; i < m; i++){
        if(monsterDist[0][i] > playerDist[0][i]){
            endLoc = {0, i};
            isValid = true;
        }
        else if(monsterDist[n - 1][i] > playerDist[n - 1][i]){
            endLoc = {n - 1, i};
            isValid = true;
        }
    }
    //cout << endLoc.first << " " << endLoc.second << endl;
    if(!isValid){
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    //generate flow field from endLoc
    q.push({endLoc.first, endLoc.second});
    vector<vector<char>> backtrack(n, vector<char>(m));
    v = vector<vector<bool>>(n, vector<bool>(m, false));
    while(q.size() != 0){
        int r = q.front()[0];
        int c = q.front()[1];
        q.pop();
        for(int i = 0; i < 4; i++){
            int nextR = r + dr[i];
            int nextC = c + dc[i];
            if(nextR < 0 || nextC < 0 || nextR >= n || nextC >= m || v[nextR][nextC] || grid[nextR][nextC] == '#'){
                continue;
            }
            if(i == 0){
                backtrack[nextR][nextC] = 'D';
            }
            else if(i == 1){
                backtrack[nextR][nextC] = 'U';
            }
            else if(i == 2){
                backtrack[nextR][nextC] = 'R';
            }
            else if(i == 3){
                backtrack[nextR][nextC] = 'L';
            }
            v[nextR][nextC] = true;
            q.push({nextR, nextC});
        }
    }   
    string ans = "";
    int curR = startLoc.first;
    int curC = startLoc.second;
    while(curR != endLoc.first || curC != endLoc.second){
        ans.push_back(backtrack[curR][curC]);
        char nextMove = backtrack[curR][curC];
        if(nextMove == 'U'){
            curR --;
        }
        else if(nextMove == 'D'){
            curR ++;
        }
        else if(nextMove == 'L'){
            curC --;
        }
        else if(nextMove == 'R'){
            curC ++;
        }
    }
    cout << ans.size() << endl;
    cout << ans << endl;
    
    return 0;
}
