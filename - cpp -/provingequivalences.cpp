#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 10 D

//this boils down to finding the minimum amount of additional edges to add to make a graph strongly connected. 

//we can turn the graph into a DAG by finding all the strongly connected components and treating them each like
//one node. 

//to find the minimum amount of additional edges to make a DAG strongly connected, we can count the number of 
//nodes with an in-degree of 0, x, and the amount of nodes with an out-degree of zero, y. Then the answer is
//just max(x, y). 

//one special case: if there is only one node in the graph, then the answer is 0. 

void visit(int i, vector<vector<int>>& c, vector<bool>& v, stack<int>& s){
    if(v[i]){
        return;
    }
    v[i] = true;
    for(int j = 0; j < c[i].size(); j++){
        visit(c[i][j], c, v, s);
    }
    s.push(i);
}

void assign(int i, int root, vector<vector<int>>& rc, vector<bool>& v, vector<int>& ans) {
    if(v[i]) {
        return;
    }
    v[i] = true;
    ans[i] = root;
    for(int j = 0; j < rc[i].size(); j++){
        assign(rc[i][j], root, rc, v, ans);
    }
}

vector<int> findSCC(int n, vector<vector<int>>& c) {
    vector<vector<int>> rc(n, vector<int>(0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            rc[c[i][j]].push_back(i);
        }
    }
    vector<int> ans(n, 0);
    stack<int> s;
    vector<bool> v(n, false);
    for(int i = 0; i < n; i++){
        visit(i, c, v, s);
    }
    fill(v.begin(), v.end(), false);
    while(s.size() != 0){
        int i = s.top();
        s.pop();
        assign(i, i, rc, v, ans);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            c[a].push_back(b);
        }
        map<int, int> nMap;
        map<int, pair<bool, bool>> naMap;
        vector<int> scc = findSCC(n, c);
        for(int i = 0; i < n; i++){
            nMap.insert({i, scc[i]});
            if(naMap.find(scc[i]) == naMap.end()) {
                naMap.insert({scc[i], {false, false}});
            }
        }
        int inCnt = 0;
        int outCnt = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < c[i].size(); j++){
                if(nMap.find(i) -> second == nMap.find(c[i][j]) -> second) {
                    continue;
                }
                naMap.find(nMap.find(i) -> second) -> second.first = true;
                naMap.find(nMap.find(c[i][j]) -> second) -> second.second = true;
            }
        }
        for(auto i = naMap.begin(); i != naMap.end(); i++){
            outCnt += !i -> second.first;
            inCnt += !i -> second.second;
        }
        if(naMap.size() == 1){
            cout << "0\n";
        }
        else {
            cout << max(inCnt, outCnt) << "\n";
        }
    }
    
    return 0;
}
