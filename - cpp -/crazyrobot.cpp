#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problemset 5H

//if from a cell, you can force the robot to the lab, then we call that cell a forced cell. 

//In order for a cell to be a forced cell, that cell must only be adjacent to at most 1 empty cell. 

//when turning an empty cell into a forced cell, there is a possiblity that the adjacent empty cells, 
//if there are any, can become forced cells as well. You can check if they can. 

//since each cell only has 4 neighbohrs, each cell can only be visited at most 4 times, leading to a O(4 * n * m) runtime. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<string> a(n);
        int lr = 0;
        int lc = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            for(int j = 0; j < m; j++){
                if(a[i][j] == 'L') {
                    lr = i;
                    lc = j;
                }
            }
        }
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};
        stack<pair<int, int>> s;
        s.push(pair<int, int>(lr, lc));
        while(s.size() != 0){
            pair<int, int> next = s.top();
            s.pop();
            int r = next.first;
            int c = next.second;
            bool isValid = true;
            int eCnt = 0;
            for(int k = 0; k < 4; k++){
                int nr = r + dr[k];
                int nc = c + dc[k];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    continue;
                }
                if(a[nr][nc] == '.'){
                    eCnt ++;
                }
            }
            if(eCnt > 1 && a[r][c] != 'L') {
                continue;
            }
            if(a[r][c] != 'L'){
                a[r][c] = '+';
            }
            for(int k = 0; k < 4; k++){
                int nr = r + dr[k];
                int nc = c + dc[k];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    continue;
                }
                if(a[nr][nc] == '.'){
                    s.push(pair<int, int>(nr, nc));
                }
            }
        }
        for(string s : a){
            cout << s << "\n";
        }
    }
    
    return 0;
}
