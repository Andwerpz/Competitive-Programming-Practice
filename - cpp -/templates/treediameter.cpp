#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//the diameter of a tree is the maximum distance between any two nodes of the tree. 
//this was tested on a leetcode problem, so be wary of it's correctness. 
int find_diameter(int n, vector<vector<int>>& c) {
    vector<int> dist(n, 1e9);
    queue<int> q;
    q.push(0);
    dist[0] = 0;
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(dist[cur] + 1 < dist[next]) {
                dist[next] = dist[cur] + 1;
                q.push(next);
            }
        }
    }
    int ind = 0;
    for(int i = 0; i < n; i++){
        if(dist[i] > dist[ind]) {
            ind = i;
        }
    }
    dist = vector<int>(n, 1e9);
    q.push(ind);
    dist[ind] = 0;
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(dist[cur] + 1 < dist[next]) {
                dist[next] = dist[cur] + 1;
                q.push(next);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans = max(ans, dist[i]);
    }
    return ans;
}