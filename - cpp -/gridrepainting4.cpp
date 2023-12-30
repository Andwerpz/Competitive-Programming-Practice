#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC131B

//since each grid has 5 color options, and only 4 neighbors, it's impossible to run out of colors. 
//just greedily pick colors for each cell. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int h, w;
    cin >> h >> w;
    vector<string> grid(h);
    for(int i = 0; i < h; i++){
        cin >> grid[i];
    }
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if(grid[i][j] != '.') {
                continue;
            }
            set<int> taken;
            for(int k = 0; k < 4; k++){
                int nr = i + dr[k];
                int nc = j + dc[k];
                if(nr < 0 || nc < 0 || nr >= h || nc >= w) {
                    continue;
                }
                taken.insert(grid[nr][nc]);
            }
            char next = '.';
            for(int k = 1; k <= 5; k++){
                if(taken.find('0' + k) == taken.end()) {
                    next = '0' + k;
                    break;
                }
            }
            grid[i][j] = next;
        }
    }
    for(int i = 0; i < h; i++){
        cout << grid[i] << "\n";
    }
    
    return 0;
}
