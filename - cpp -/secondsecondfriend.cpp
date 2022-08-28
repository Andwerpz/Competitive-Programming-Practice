#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Meta Hacker Cup 2022 B2

//notice that some tiles only have 1 or 0 neighbors. We can call these tiles disconnected, since 
//a tree there would not be able to have the required 2 friends. 

//disconnected tiles can in turn make other tiles disconnected as well, as placing a tree in a disconnected
//tile is a non-option. 

//so, the key is to first check every tile to see if it's disconnected, and then if there are trees in 
//disconnected tiles, then it is impossible to give all trees 2 friends. 

//else, you can just fill all the connected tiles with trees, and that is a valid painting. 

vector<int> dx = {0, 0, -1, 1};
vector<int> dy = {-1, 1, 0, 0};

bool canCollapse(vector<vector<char>>& g, vector<vector<bool>>& coll, int i, int j){
    int cnt = 0;
    for(int k = 0; k < 4; k++){
        int r = i + dx[k];
        int c = j + dy[k];
        if(r < 0 || c < 0 || r >= g.size() || c >= g[0].size()){
            cnt ++;
        }
        else if(g[r][c] == '#' || coll[r][c]){
            cnt ++;
        }
    }
    return cnt >= 3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream fin("second_second_friend_input.txt");
    ofstream fout("second_second_friend_output.txt");
    
    int t;
    fin >> t;
    int caseNum = 1;
    while(t-- > 0){
        int r, c;
        fin >> r >> c;
        vector<vector<bool>> coll(r, vector<bool>(c));
        vector<vector<char>> g(r, vector<char>(c));
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                fin >> g[i][j];
            }
        }
        bool isValid = true;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                if(coll[i][j]){
                    continue;
                }
                stack<pair<int, int>> s;
                s.push({i, j});
                while(s.size() != 0){
                    int row = s.top().first;
                    int col = s.top().second;
                    s.pop();
                    if(row < 0 || col < 0 || row >= r || col >= c || coll[row][col]){
                        continue;
                    }
                    if(!canCollapse(g, coll, row, col)){
                        continue;
                    }
                    coll[row][col] = true;
                    for(int k = 0; k < 4; k++){
                        s.push({row + dx[k], col + dy[k]});
                    }
                }
            }
        }
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                if(g[i][j] == '^' && coll[i][j]){
                    isValid = false;
                }
            }
        }
        if(!isValid){
            fout << "Case #" << caseNum << ": Impossible\n";
            caseNum ++;
            continue;
        }
        fout << "Case #" << caseNum << ": Possible\n";
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                if(g[i][j] == '#'){
                    fout << "#";
                }
                else if(g[i][j] == '^'){
                    fout << "^";
                }
                else if(g[i][j] == '.'){
                    fout << (coll[i][j]? "." : "^");
                }
            }
            fout << "\n";
        }
        caseNum++;
    }
    
    return 0;
}
