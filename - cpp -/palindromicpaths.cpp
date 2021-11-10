
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1366C

//this problem needs an implementation tag

//just look at the diagonals. The diagonals need to be palindromic, except for the center, which doesn't matter. 

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> nums(n);
        for(int i = 0; i < n; i++){
            nums[i] = vector<int>(m);
            for(int j = 0; j < m; j++){
                cin >> nums[i][j];
            }
        }
        vector<pair<int, int>> dict(n + m - 1);
        int xStart = 0;
        int yStart = 0;
        int pointer = 0;
        while(true){
            int zero = 0;
            int one = 0;
            int x = xStart;
            int y = yStart;
            while(x >= 0 && y < n){
                //cout << x << " " << y << endl;
                int next = nums[y][x];
                if(next == 0){
                    zero ++;
                }
                else {
                    one ++;
                }
                x --;
                y ++;
            }
            dict[pointer] = pair<int, int>{zero, one};
            if(xStart != m - 1){
                xStart ++;
            }
            else {
                yStart ++;
            }
            if(yStart == n){
                break;
            }
            pointer ++;
        }
        int l = 0;
        int r = dict.size() - 1;
        int ans = 0;
        while(true){
            ans += min(dict[l].first + dict[r].first, dict[l].second + dict[r].second);
            l ++;
            r --;
            if(l >= r){
                break;
            }
        }
        cout << ans << endl;
    }

    return 0;
}



