#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC 2023–2024 NERC H

//let's say the edges in the graph are the starting locations and the destinations of all the people.
//we can solve this seperately for every weakly connected component. 

//if a weakly connected component is acyclic, then we can simply launch the catapults in the topological
//ordering of the graph. 

//otherwise, we need to solve the case where the component is not acyclic. Since some catapult must launch first, 
//we can simply try out all the catapults to launch first. Let's say the catapult in city 'a' launches first. 
//Observe that any person who starts at 'a' will always get to their destination, and any person who wants to go to
//'a' will always get there, since we are making one big loop ending at 'a'. 
//In order for this to be valid, the remaining cities must have a valid topological ordering, or in other
//words, removing city 'a' makes the component acyclic. Since n*m is 10^8, we can simply try out all 
//cities. 

//in terms of minimizing the number of launches, there really isn't that much we can do. If a component of size n 
//is acyclic, then the best we can do is n - 1 launches, otherwise it requires n launches if a solution exists. 

vector<int> generate_toporder(vector<vector<int>>& c, int start = -1) {
    int n = c.size();
    vector<int> indeg(n, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            indeg[c[i][j]] ++;
        }
    }
    queue<int> q;
    if(start != -1){
        q.push(start);
    }
    for(int i = 0; i < n; i++){
        if(i == start){
            continue;
        }
        if(indeg[i] == 0){
            q.push(i);
        }
    }
    vector<int> order(0);
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        order.push_back(cur);
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(next == start){
                continue;
            }
            indeg[next] --;
            if(indeg[next] == 0){
                q.push(next);
            }
        }
    }
    if(order.size() == n){
        return order;
    }
    return {};
}

bool solve(vector<vector<int>>& c, vector<int>& comp, vector<pair<int, int>>& ans) {
    int n = comp.size();
    map<int, int> comp_ind;
    for(int i = 0; i < n; i++){
        comp_ind.insert({comp[i], i});
    }
    vector<vector<int>> nc(n, vector<int>(0));
    for(int i = 0; i < n; i++){
        int cur = comp[i];
        int u = comp_ind[cur];
        for(int j = 0; j < c[cur].size(); j++){
            int next = c[cur][j];
            int v = comp_ind[next];
            nc[u].push_back(v);
        }
    }
    //check if is acyclic
    {
        vector<int> order = generate_toporder(nc);
        if(order.size() != 0){
            //it is acyclic. 
            for(int i = 0; i < order.size() - 1; i++){
                int u = order[i];
                int v = order[(i + 1) % order.size()];
                ans.push_back({comp[u], comp[v]});
            }
            return true;
        }
    }
    for(int i = 0; i < n; i++){
        vector<int> order = generate_toporder(nc, i);
        if(order.size() == 0){
            continue;
        }
        for(int j = 0; j < order.size(); j++){
            int u = order[j];
            int v = order[(j + 1) % order.size()];
            ans.push_back({comp[u], comp[v]});
        }
        return true;
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int>(0)), c_ud(n, vector<int>(0));
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c_ud[a].push_back(b);
        c_ud[b].push_back(a);
    }
    //find weakly connected components
    vector<vector<int>> w_c(0);
    vector<bool> v(n, false);
    for(int i = 0; i < n; i++){
        if(v[i]){
            continue;
        }
        vector<int> comp(0);
        v[i] = true;
        stack<int> s;
        s.push(i);
        while(s.size() != 0){
            int cur = s.top();
            s.pop();
            comp.push_back(cur);
            for(int j = 0; j < c_ud[cur].size(); j++){
                int next = c_ud[cur][j];
                if(v[next]){
                    continue;
                }
                v[next] = true;
                s.push(next);
            }
        }
        w_c.push_back(comp);
    }
    bool is_valid = true;
    vector<pair<int, int>> ans(0);
    for(int i = 0; i < w_c.size(); i++){
        vector<pair<int, int>> n_ans(0);
        bool status = solve(c, w_c[i], ans);
        if(!status) {
            is_valid = false;
            break;
        }
        for(int j = 0; j < n_ans.size(); j++){
            ans.push_back(n_ans[j]);
        }
    }
    if(!is_valid) {
        cout << "-1\n";
        return 0;
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
    }
    
    return 0;
}
