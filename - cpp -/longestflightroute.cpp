#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSES - 1680

//to figure out the longest path in a DAG from node a to b, first prune out any node that isn't a child of a. 
//note that if b is not a child of a, then it is impossible to get from a to b. 

//once done, topological sort the remaining nodes, then do edge relaxation stuff on each node in order of the topological sort. 

//for each node, keep track of the previous node so that you can reconstruct the answer. 

//this should work for variable weights as well. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
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
    vector<int> dist(n, 0);
    vector<int> prev(n, 0);
    vector<bool> v(n, false);
    v[0] = true;
    stack<int> s;
    s.push(0);
    while(s.size()) {
        int cur = s.top();
        s.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(v[next]) {
                continue;
            }
            v[next] = true;
            s.push(next);
        }
    }
    if(!v[n - 1]) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vector<int> in(n, 0);
    for(int i = 0; i < n; i++){
        if(!v[i]) {
            continue;
        }
        for(int j = 0; j < c[i].size(); j++){
            in[c[i][j]] ++;
        }
    }
    s = stack<int>();
    for(int i = 0; i < n; i++){
        if(!v[i]) {
            continue;
        }
        if(!in[i]) {
            s.push(i);
        }
    }
    while(s.size()) {
        int cur = s.top();
        s.pop();
        for(int i = 0; i < c[cur].size(); i++) {
            int next = c[cur][i];
            in[next] --;
            if(dist[next] < dist[cur] + 1) {
                dist[next] = dist[cur] + 1;
                prev[next] = cur;
            }
            if(!in[next]) {
                s.push(next);
            }
        }
    }
    cout << dist[n - 1] + 1 << "\n";
    int x = n - 1;
    vector<int> ans(0);
    while(x) {
        ans.push_back(x);
        x = prev[x];
    }
    ans.push_back(x);
    for(int i = ans.size() - 1; i >= 0; i--){
        cout << ans[i] + 1 << " \n"[!i];
    }
    
    return 0;
}
