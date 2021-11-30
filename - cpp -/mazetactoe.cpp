
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

vector<vector<string>> board;
int startX, startY;

string convertToBase3(int val) {
    if(val < 3) {
        return to_string(val);
    }
    int rem = val % 3;
    return convertToBase3(val / 3) + to_string(rem);
}

string pairToString(int x, int y){
    return to_string(x + 1) + to_string(y + 1);
}

bool checkForWin(vector<string> grid){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(grid[i][j] == '2'){
                //do win check
                bool curWin = false;
                //vertical
                if(i == 0 && grid[i + 1][j] == '1' && grid[i + 2][j] == '1'){
                    return true;
                }
                else if(i == 2 && grid[i - 1][j] == '1' && grid[i - 2][j] == '1'){
                    return true;
                }
                //horizontal
                if(j == 0 && grid[i][j + 1] == '1' && grid[i][j + 2] == '1'){
                    return true;
                }
                else if(j == 2 && grid[i][j - 1] == '1' && grid[i][j - 2] == '1'){
                    return true;
                }
                //diagonal
                if(i == 0 && j == 0 && grid[1][1] == '1' && grid[2][2] == '1'){
                    return true;
                }
                else if(i == 0 && j == 2 && grid[1][1] == '1' && grid[2][0] == '1'){
                    return true;
                }
                else if(i == 2 && j == 0 && grid[1][1] == '1' && grid[0][2] == '1'){
                    return true;
                }
                else if(i == 2 && j == 2 && grid[1][1] == '1' && grid[0][0] == '1'){
                    return true;
                }
            }
        }
    }
    return false;
}

/*
(1, 1) (1, 2) (1, 3)
(2, 1) (2, 2) (2, 3)
(3, 1) (3, 2) (3, 3)
*/

bool isValid(string position) {
    //first check if this position is possible to end on
    //0 : blank, 1 : O, 2 : M
    vector<string> grid(3);
    for(int i = 0; i < 3; i++){
        grid[i] = position.substr(i * 3, 3);
    }
    if(!checkForWin(grid)){
        return false;
    }
    //now identify tiles that when we remove them, it's no longer a winning position. If there are none, then the grid is invalid
    set<string> winTiles;
    set<string> visitableTiles;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(grid[i][j] != '0'){
                char temp = grid[i][j];
                grid[i][j] = '0';
                bool win = checkForWin(grid);
                grid[i][j] = temp;
                if(!win){   //if when we remove it, it isn't winning, then we have to place this tile last
                    winTiles.insert((grid[i][j] == '1'? "O" : "M") + pairToString(i, j));
                }
                else{   //we can place these tiles in any order
                    visitableTiles.insert((grid[i][j] == '1'? "O" : "M") + pairToString(i, j));
                }
            }
        }
    }
    vector<string> g = {
        "000",
        "000",
        "000"
    };
    //now we know that it is possible to win, do floodfill on board
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    stack<string> vEndTiles;
    stack<pair<int, int>> vEndLoc;
    set<pair<int, int>> v;
    stack<pair<int, int>> s;
    s.push({startX, startY});
    v.insert({startX, startY});
    while(s.size() != 0){
        int curX = s.top().first;
        int curY = s.top().second;
        s.pop();
        for(int i = 0; i < 4; i++){
            int nextX = curX + dx[i];
            int nextY = curY + dy[i];
            if(nextX >= 0 && nextX < board.size() && nextY >= 0 && nextY < board.size() && v.find({nextX, nextY}) == v.end()){
                string nextTile = board[nextX][nextY]; 
                bool placed = false;
                if(nextTile != "..." && nextTile != "###"){
                    int gx = stoi(string(1, nextTile[1])) - 1;
                    int gy = stoi(string(1, nextTile[2])) - 1;
                    placed = g[gx][gy] != '0';
                }
                if(placed){
                    v.insert({nextX, nextY});
                    s.push({nextX, nextY});
                }
                else if(nextTile == "..."){
                    v.insert({nextX, nextY});
                    s.push({nextX, nextY});
                }
                else if(visitableTiles.find(nextTile) != visitableTiles.end()){
                    visitableTiles.erase(nextTile);
                    v.insert({nextX, nextY});
                    s.push({nextX, nextY});
                    int gx = stoi(string(1, nextTile[1])) - 1;
                    int gy = stoi(string(1, nextTile[2])) - 1;
                    g[gx][gy] = 1;
                }
                else if(winTiles.find(nextTile) != winTiles.end()){
                    vEndTiles.push(nextTile);
                    vEndLoc.push({nextX, nextY});
                }
            }
        }
    }
    
    //checking if there is any tile locked behind an end tile
    bool noneBehind = false;
    while(vEndTiles.size() != 0){
        s = stack<pair<int, int>>();
        v = set<pair<int, int>>();
        //cout << vEndTiles.top() << endl;
        s.push({vEndLoc.top().first, vEndLoc.top().second});
        v.insert({vEndLoc.top().first, vEndLoc.top().second});
        winTiles.erase(vEndTiles.top());
        vEndTiles.pop();
        vEndLoc.pop();
        bool curNoneBehind = true;
        while(s.size() != 0){
            int curX = s.top().first;
            int curY = s.top().second;
            s.pop();
            for(int i = 0; i < 4; i++){
                int nextX = curX + dx[i];
                int nextY = curY + dy[i];
                if(nextX >= 0 && nextX < board.size() && nextY >= 0 && nextY < board.size() && v.find({nextX, nextY}) == v.end()){
                    string nextTile = board[nextX][nextY]; 
                    //cout << "NEXT: " + nextTile << endl;
                    bool placed = false;
                    if(nextTile != "..." && nextTile != "###"){
                        int gx = stoi(string(1, nextTile[1])) - 1;
                        int gy = stoi(string(1, nextTile[2])) - 1;
                        placed = g[gx][gy] != '0';
                    }
                    if(placed){
                        v.insert({nextX, nextY});
                        s.push({nextX, nextY});
                    }
                    else if(nextTile == "..."){
                        v.insert({nextX, nextY});
                        s.push({nextX, nextY});
                    }
                    else if(visitableTiles.find(nextTile) != visitableTiles.end()){
                        curNoneBehind = false;
                        visitableTiles.erase(nextTile);
                        v.insert({nextX, nextY});
                        s.push({nextX, nextY});
                        int gx = stoi(string(1, nextTile[1])) - 1;
                        int gy = stoi(string(1, nextTile[2])) - 1;
                        g[gx][gy] = 1;
                    }
                    else if(winTiles.find(nextTile) != winTiles.end()){
                        curNoneBehind = false;
                        vEndTiles.push(nextTile);
                        vEndLoc.push({nextX, nextY});
                    }
                }
            }
        }
        //cout << curNoneBehind << endl;
        noneBehind |= curNoneBehind;
    }
    //cout << noneBehind << endl;
    if(noneBehind && visitableTiles.size() == 0 && winTiles.size() == 0){
        return true;
    }
    return false;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    startX = 0;
    startY = 0;
    board = vector<vector<string>>(n);
    for(int i = 0; i < n; i++){
        board[i] = vector<string>(n);
        string line;
        cin >> line;
        for(int j = 0; j < n; j++){
            string next = line.substr(j * 3, 3);
            if(next == "BBB"){
                startX = i;
                startY = j;
                next = "...";   //we can always pass through the starting position
            }
            board[i][j] = next;
        }
    }
    //generate all possible board positions
    int counter = 0;
    int ans = 0;
    while(true){
        string base3 = convertToBase3(counter);
        if(base3.size() > 9){
            break;
        }
        while(base3.size() < 9){
            base3 = "0" + base3;
        }
        counter ++;
        if(isValid(base3)){
            ans ++;
        }
    }
    cout << ans << endl;
    
    return 0;
}
