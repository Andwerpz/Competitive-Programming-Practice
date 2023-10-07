#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 1691

//just have to find an eulerian tour of the graph. 

//one case to keep in mind is if a node has no edges connected to it, we are not required to visit it. 

set<pair<int, int>> edge_used;

void euler_path(vector<vector<int>>& c, vector<int>& ptr, vector<int>& ans, int i) {
    while(ptr[i] < c[i].size()) {
        int next = c[i][ptr[i] ++];
        if(edge_used.find({i, next}) != edge_used.end()) {
            continue;
        }
        if(edge_used.find({next, i}) != edge_used.end()) {
            continue;
        }
        edge_used.insert({next, i});
        euler_path(c, ptr, ans, next);
    }
    ans.push_back(i);
}

//an euler tour only exists if the degrees of all vertices are even
//an euler path only exists if the number of vertices with odd degrees are two, or zero, in which case an euler cycle exists. 
//and of course, the graph is sufficiently connected. 

//this function doesn't check any of those. TODO make it do that
vector<int> euler_path(vector<vector<int>>& c, int i) {
    int n = c.size();
    vector<int> ptr(n, 0);
    vector<int> ans(0);
    euler_path(c, ptr, ans, i);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int m;
    cin >> m;
    vector<vector<int>> c(n, vector<int>(0));
    vector<int> d(n, 0);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        d[a] ++;
        d[b] ++;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    bool isValid = true;
    for(int i = 0; i < n; i++){
        if(d[i] % 2 == 1){
            isValid = false;
        }
    }
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
    for(int i = 0; i < n; i++){
        if(!v[i] && d[i] != 0){
            isValid = false;
        }
    }
    if(!isValid) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vector<int> ans = euler_path(c, 0);
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] + 1 << " ";
    }
    cout << "\n";
    
    return 0;
}
