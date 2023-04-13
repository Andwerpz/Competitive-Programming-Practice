#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 10 E

//i used kosajaru's algorithm here, apparently tarjans is better for finding scc

//if the entire graph is not one scc, then it is possible that one node cannot get to another node. 

//then, just brute force reverse roads, until you either reversed all of them, or one makes the entire graph one scc. 

void visit(int i, stack<int>& s, vector<vector<int>>& c, vector<bool>& v) {
    if(v[i]){
        return;
    }
    v[i] = true;
    for(int j = 0; j < c[i].size(); j++){
        visit(c[i][j], s, c, v);
    }
    s.push(i);
}

void assign(int i, int root, vector<vector<int>>& c, vector<bool>& v, vector<int>& ans) {
    if(v[i]){
        return;
    }
    v[i] = true;
    ans[i] = root;
    for(int j = 0; j < c[i].size(); j++){
        assign(c[i][j], root, c, v, ans);
    }
}

bool findSCC(int n, vector<vector<bool>>& adj) {
    vector<vector<int>> c(n, vector<int>(0));
    vector<vector<int>> rc(n, vector<int>(0));
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j < n; j++){
            if(adj[i][j]) {
                c[i].push_back(j);
                rc[j].push_back(i);
            }
        }
    }
    vector<bool> v(n, false);
    stack<int> s;
    for(int i = 0; i < n; i++){
        visit(i, s, c, v);
    }
    vector<int> ans(n, 0);
    fill(v.begin(), v.end(), false);
    while(s.size() != 0){
        int next = s.top();
        s.pop();
        assign(next, next, rc, v, ans);
    }
    for(int i = 1; i < n; i++){
        if(ans[i] != ans[0]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    int cnt = 0;
    while(!cin.eof()){
        cnt ++;
        vector<vector<bool>> c(n, vector<bool>(n, false));
        vector<pair<int, int>> rList(m, {0, 0});
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            c[a][b] = true;
            rList[i] = {a, b};
        }
        cout << "Case " << cnt << ": ";
        cout.flush();
        if(findSCC(n, c)) {
            cout << "valid\n";
        }
        else {
            bool isValid = false;
            int a = -1;
            int b = -1;
            for(int i = 0; i < m; i++){
                int u = rList[i].first;
                int v = rList[i].second;
                c[u][v] = false;
                c[v][u] = true;
                if(findSCC(n, c)) {
                    a = u;
                    b = v;
                    isValid = true;
                    break;
                }
                c[v][u] = false;
                c[u][v] = true;
            }
            if(!isValid) {
                cout << "invalid\n";
            }
            else {
                cout << a << " " << b << "\n";
            }
        }
        cout.flush();
        cin >> n >> m;
    }
    
    return 0;
}
