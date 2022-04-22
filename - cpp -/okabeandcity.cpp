
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

vector<int> cost;

//Codeforces - 821D

//a naive approach is for each cell, generate an adjacency list and do a normal bfs search to find
//the minimum cost to the end. 

//from a given cell with row i and column j, you can reach all cells that are at most 2 rows or columns different
//by only lighting up 1 row or column. 

//the problem with the naive solution is that there could be too many edges. 

//we can make an observations about the problem:
//you only need to light up each row or column only once during your search.

//lighting up a row or column twice would be redundant, as when you lit it up in the first
//pass, you could already access all of the lit cells. 

//thus, you need to maintain a row and col visited arr as well as a cell specific
//visited arr. 

//depending on whether or not the end cell is lit, you may have to write some special cases. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> cr(n, vector<pair<int, int>>());   //for each row, save lit cell columns and ids
    vector<vector<pair<int, int>>> cc(m, vector<pair<int, int>>());   //for each column, save lit cell rows and ids
    vector<bool> v(k, false);
    vector<pair<int, int>> lit(0);
    map<pair<int, int>, int> litMap;   //so we can do adjacency checks
    bool endLit = false;
    int endId = -1;
    for(int i = 0; i < k; i++){
        int r, c;
        cin >> r >> c;
        r--;
        c--;
        cr[r].push_back({c, i});
        cc[c].push_back({r, i});
        lit.push_back({r, c});
        litMap.insert({{r, c}, i});
        if(r == n - 1 && c == m - 1){
            //cout << "END LIT\n";
            endLit = true;
            endId = i;
        }
    }
    vector<bool> vr(n, false);  //we only want to light up each row or col once. 
    vector<bool> vc(m, false);
    cost = vector<int>(k, 1e9);
    cost[0] = 0;
    auto compare = [] (int a, int b) {return cost[a] == cost[b]? a < b : cost[a] < cost[b];};
    set<int, decltype(compare)> s(compare);
    s.insert(0);
    v[0] = true;
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    int ans = 1e9;
    while(s.size() != 0){
        int cur = *s.begin();
        int curR = lit[cur].first;
        int curC = lit[cur].second;
        //cout << "V: " << curR << " " << curC  << " " << cur << " " << cost[cur] << endl;
        s.erase(cur);
        //check if we can go to exit
        if(curR == n - 1 && curC == m - 1){ //at end
            //cout << "AT: " << curR << " " << curC << endl;
            ans = min(ans, cost[cur]);
        }
        else if((endLit && (curR >= n - 3 || curC >= m - 3)) || (!endLit && (curR >= n - 2 || curC >= m - 2))){ //can light up tiles to go to end
            //cout << "VISIT: " << curR << " " << curC << endl;
            ans = min(ans, cost[cur] + 1);
        }
        //check rows and cols up to 2 away
        for(int i = -2; i <= 2; i++){
            int nextR = curR + i;
            int nextC = curC + i;
            if(nextR >= 0 && nextR < n && !vr[nextR]){
                vr[nextR] = true;
                for(pair<int, int> p : cr[nextR]){
                    int c = p.first;
                    int next = p.second;
                    //upd cost
                    int diff = abs(nextR - curR) + abs(c - curC);
                    int updCost = cost[cur] + (diff <= 1? 0 : 1);   //if the node is adjacent or the current node, don't add to cost.
                    if(s.find(next) != s.end()){
                        s.erase(next);
                        cost[next] = min(cost[next], updCost);
                        s.insert(next);
                    }
                    else{
                        cost[next] = min(cost[next], updCost);
                    }
                    if(!v[next]){
                        v[next] = true;
                        s.insert(next);
                    }
                }
            }
            if(nextC >= 0 && nextC < m && !vc[nextC]){
                vc[nextC] = true;
                for(pair<int, int> p : cc[nextC]){
                    int r = p.first;
                    int next = p.second;
                    //upd cost
                    int diff = abs(r - curR) + abs(nextC - curC);
                    int updCost = cost[cur] + (diff <= 1? 0 : 1);   //if the node is adjacent or the current node, don't add to cost.
                    if(s.find(next) != s.end()){
                        s.erase(next);
                        cost[next] = min(cost[next], updCost);
                        s.insert(next);
                    }
                    else{
                        cost[next] = min(cost[next], updCost);
                    }
                    if(!v[next]){
                        v[next] = true;
                        s.insert(next);
                    }
                }
            }
        }
        //check for adjacent lit nodes
        for(int i = 0; i < 4; i++){
            int nextR = curR + dr[i];
            int nextC = curC + dc[i];
            if(litMap.find({nextR, nextC}) != litMap.end()){
                //cout << "ADJ: " << nextR << " " << nextC << endl;
                //upd cost
                int next = litMap.find({nextR, nextC}) -> second;
                if(s.find(next) != s.end()){
                    s.erase(next);
                    cost[next] = min(cost[next], cost[cur]);
                    s.insert(next);
                }
                else{
                    cost[next] = min(cost[next], cost[cur]);
                }
                if(!v[next]){
                    v[next] = true;
                    s.insert(next);
                }
            }
        }
    }
    cout << (ans == 1e9? -1 : ans) << endl;
    
    return 0;
}
