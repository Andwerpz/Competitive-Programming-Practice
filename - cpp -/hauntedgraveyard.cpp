#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 10 B

//treat grid as graph, and relax weights. 

//if after (w * h) ^ 2 relaxations, there can still be relaxations, then there is a negative cycle, and return "Never". 

//else, return the distance, or impossible if he can't get to the end. 

//make sure, when doing the search to relax, don't have any outgoing nodes at the exit node, since the exit node cannot
//be part of a negative cycle. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int w, h;
    cin >> w >> h;
    while(w != 0){
        vector<vector<int>> arr(w, vector<int>(h, 0));
        int g;
        cin >> g;
        for(int i = 0; i < g; i++){
            int x, y;
            cin >> x >> y;
            arr[x][y] = 1;
        }
        vector<vector<vector<vector<int>>>> c(w, vector<vector<vector<int>>>(h, vector<vector<int>>(0)));
        int e;
        cin >> e;
        for(int i = 0; i < e; i++){
            int a, b, u, v, t;
            cin >> a >> b >> u >> v >> t;
            c[a][b].push_back({u, v, t});
        } 
        int cnt = 0;
        queue<pair<int, int>> s;
        vector<vector<ll>> d(w, vector<ll>(h, INT32_MAX));
        d[0][0] = 0;
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};
        s.push({0, 0});
        while(s.size() != 0 && cnt < w * h * 100){
            int curR = s.front().first;
            int curC = s.front().second;
            ll curDist = d[curR][curC];
            cnt ++;
            s.pop();
            if(curR == w - 1 && curC == h - 1){
                continue;
            }
            if(c[curR][curC].size() == 0){
                for(int i = 0; i < 4; i++){
                    int nextR = curR + dr[i];
                    int nextC = curC + dc[i];
                    if(nextR < 0 || nextC < 0 || nextR >= w || nextC >= h) {
                        continue;
                    }
                    if(arr[nextR][nextC] == 1){
                        continue;
                    }
                    ll nextDist = curDist + 1;
                    if(nextDist >= d[nextR][nextC]) {
                        continue;
                    }
                    d[nextR][nextC] = nextDist;
                    s.push({nextR, nextC});
                }
            }
            else {
                for(int i = 0; i < c[curR][curC].size(); i++){
                    int nextR = c[curR][curC][i][0];
                    int nextC = c[curR][curC][i][1];
                    ll nextDist = curDist + c[curR][curC][i][2];
                    if(nextDist >= d[nextR][nextC]){
                        continue;
                    }
                    d[nextR][nextC] = nextDist;
                    s.push({nextR, nextC});
                }
            }
            
        }
        if(cnt > w * h * 50) {
            cout << "Never\n";
        }
        else if(d[w - 1][h - 1] == INT32_MAX) {
            cout << "Impossible\n";
        }
        else {
            cout << d[w - 1][h - 1] << "\n";
        }
        cin >> w >> h;
    }
    
    return 0;
}
