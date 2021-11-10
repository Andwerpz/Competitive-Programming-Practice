
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1015E1

//just greedy. For each location, see if you can draw a star, and if you can, then just draw the biggest star you can.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n);
    for(int i = 0; i < n; i++){
        grid[i] = vector<int>(m);
    }
    for(int i = 0; i < n; i++){
        string in;
        cin >> in;
        for(int j = 0; j < m; j++){
            if(in[j] == '.'){
                grid[i][j] = 0;
            }
            else{
                grid[i][j] = 1;
            }
        }
    }
    vector<vector<int>> ans;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == 1 || grid[i][j] == 2){
                int x1 = i; int x2 = i; int x3 = i; int x4 = i;
                int y1 = j; int y2 = j; int y3 = j; int y4 = j;
                x1 --;
                x2 ++;
                y3 --;
                y4 ++;
                int counter = 0;
                while(min(min(x1, x2), min(x3, x4)) >= 0 && 
                max(max(x1, x2), max(x3, x4)) < n && 
                min(min(y1, y2), min(y3, y4)) >= 0 && 
                max(max(y1, y2), max(y3, y4)) < m &&
                (grid[x1][y1] == 1 || grid[x1][y1] == 2) &&
                (grid[x2][y2] == 1 || grid[x2][y2] == 2) &&
                (grid[x3][y3] == 1 || grid[x3][y3] == 2) &&
                (grid[x4][y4] == 1 || grid[x4][y4] == 2)){
                    grid[x1][y1] = 2;
                    grid[x2][y2] = 2;
                    grid[x3][y3] = 2;
                    grid[x4][y4] = 2;
                    x1 --;
                    x2 ++;
                    y3 --;
                    y4 ++;
                    counter ++;
                }
                if(counter != 0){
                    ans.push_back({i + 1, j + 1, counter});
                    grid[i][j] = 2;
                }
            }
        }
    }
    bool isValid = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == 1){
                isValid = false;
            }
        }
    }
    if(isValid){
        cout << ans.size() << endl;
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << endl;
        }
    }
    else{
        cout << "-1\n";
    }

    return 0;
}



