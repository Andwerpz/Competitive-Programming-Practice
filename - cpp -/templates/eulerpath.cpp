#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//an euler tour only exists if the degrees of all vertices are even
//an euler path only exists if the number of vertices with odd degrees are two, or zero, in which case an euler cycle exists. 
//and of course, the graph is sufficiently connected. 
//this function doesn't check any of those. TODO make it do that

//for undirected, i assume that each edge is mentioned twice, one in each direction. 
//this can handle multigraphs and self edges. 
//If there is a self edge at node i, then it should be mentioned twice in c[i].
void euler_path_undirected(vector<vector<int>>& c, vector<vector<int>>& eid, vector<int>& ptr, vector<bool>& rm, vector<int>& ans, int i) {
    while(ptr[i] < c[i].size()){
        if(rm[eid[i][ptr[i]]]){
            ptr[i] ++;
            continue;
        }
        int next = c[i][ptr[i]];
        rm[eid[i][ptr[i]]] = true;
        ptr[i] ++;
        euler_path_undirected(c, eid, ptr, rm, ans, next);
    }
    ans.push_back(i);
}

vector<int> euler_path_undirected(vector<vector<int>>& _c, int i){
    int n = _c.size();
    int m = 0;
    vector<vector<int>> eid(n), c(n);
    vector<int> ptr(n, 0), ans(0);
    vector<bool> se(n, false);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < _c[i].size(); j++){
            int next = _c[i][j];
            if(next >= i){
                if(next == i){
                    se[i] = !se[i];
                    if(!se[i]){
                        continue;
                    }
                }
                eid[i].push_back(m);
                c[i].push_back(next);
                eid[next].push_back(m);
                c[next].push_back(i);
                m ++;
            }
        }
    }
    vector<bool> rm(m, false);
    euler_path_undirected(c, eid, ptr, rm, ans, i);
    return ans;
}

//in the directed case, i believe the indegree has to equal the outdegree for all nodes
void euler_path_directed(vector<vector<int>>& c, vector<int>& ptr, vector<int>& ans, int i) {
    while(ptr[i] < c[i].size()) {
        int next = c[i][ptr[i] ++];
        euler_path_directed(c, ptr, ans, next);
    }
    ans.push_back(i);
}

vector<int> euler_path_directed(vector<vector<int>>& c, int i) {
    int n = c.size();
    vector<int> ptr(n, 0);
    vector<int> ans(0);
    euler_path_directed(c, ptr, ans, i);
    return ans;
}
