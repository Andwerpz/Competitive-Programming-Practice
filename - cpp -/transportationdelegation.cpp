#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 12 H

//max flow. 

//for each transportation company, have an in node, and an out node to enforce that each transportation company can only handle
//capacity of one. 

//then, you can connect the sink to all of the states with raw materials, and states with factories to the sink. 

ll dinic(int n, vector<vector<pair<int, ll>>> c, int source, int sink) {
    ll ans = 0;
    //redo organization of edges
    vector<pair<int, ll>> edges(0);
    vector<vector<int>> adj(n, vector<int>(0));
    int m = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            int u = i;
            int v = c[i][j].first;
            ll cap = c[i][j].second;
            adj[u].push_back(m);
            adj[v].push_back(m + 1);
            edges.push_back({v, cap});
            edges.push_back({u, 0});
            m += 2;
        }
    }
    while(true) {
        //create level graph
        vector<int> level(n, -1);
        queue<int> q;
        vector<bool> v(n, false);
        v[source] = true;
        q.push(source);
        level[source] = 0;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < adj[cur].size(); i++) {
                int nEdge = adj[cur][i];
                int next = edges[nEdge].first;
                if(v[next]) {
                    continue;
                }
                if(edges[nEdge].second == 0){
                    //no flow
                    continue;
                }
                v[next] = true;
                q.push(next);
                level[next] = level[cur] + 1;
            }
        }
        if(!v[sink]){
            //we're done here
            break;
        }
        while(true) {
            //do dfs until there is no path from source to sink along level graph
            stack<int> s;
            s.push(source);
            stack<int> est;
            stack<int> ist;
            ist.push(0);
            while(s.size() != 0){
                int cur = s.top();
                if(cur == sink) {   
                    //we've found path from source to sink
                    break;
                }
                bool foundNext = false;
                for(int i = ist.top(); i < adj[cur].size(); i++){
                    int nEdge = adj[cur][i];
                    int next = edges[nEdge].first;
                    if(level[next] <= level[cur]){
                        continue;
                    }
                    if(edges[nEdge].second == 0){
                        continue;
                    }
                    s.push(next);
                    est.push(nEdge);
                    ist.pop();
                    ist.push(i + 1);
                    ist.push(0);
                    foundNext = true;
                    break;
                }
                if(!foundNext) {
                    s.pop();
                    ist.pop();
                    if(est.size() != 0){
                        est.pop();
                    }
                    //mark this node as a dead end
                    level[cur] = -1;
                }
            }
            if(s.size() != 0 && s.top() == sink) {
                //found a path yay, now we update flow for edges on path
                ll bn = 1e18;
                vector<int> path(est.size(), 0);
                for(int i = 0; i < path.size(); i++){
                    path[i] = est.top();
                    est.pop();
                    bn = min(bn, edges[path[i]].second);
                }
                for(int i = 0; i < path.size(); i++){
                    //forward edge
                    edges[path[i]].second -= bn;
                    //backwards edge
                    edges[path[i] ^ 1].second += bn;
                }
                ans += bn;
            }
            else {
                //the maximum flow for this level configuration has been reached. 
                break;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int s, r, f, t;
    cin >> s >> r >> f >> t;
    map<string, int> nMap;
    vector<int> stateID(s, 0);
    int ptr = 0;
    for(int i = 0; i < s; i++){
        stateID[i] = ptr++;
    }
    vector<int> type(s, 0);
    int nptr = 0;
    for(int i = 0; i < r; i++){
        string next;
        cin >> next;
        type[nptr] = 1;
        nMap.insert({next, nptr++});
    }
    for(int i = 0; i < f; i++){
        string next;
        cin >> next;
        type[nptr] = 2;
        nMap.insert({next, nptr++});
    }
    vector<int> tinID(t, 0);
    vector<int> toutID(t, 0);
    for(int i = 0; i < t; i++){
        tinID[i] = ptr++;
        toutID[i] = ptr++;
    }
    vector<vector<int>> tarr(t, vector<int>(0));
    for(int i = 0; i < t; i++){
        int amt;
        cin >> amt;
        for(int j = 0; j < amt; j++){
            string next;
            cin >> next;
            if(nMap.find(next) == nMap.end()) {
                nMap.insert({next, nptr++});
            }
            int ind = nMap.find(next) -> second;
            tarr[i].push_back(ind);
        }
    }
    int source = ptr++;
    int sink = ptr++;
    vector<vector<pair<int, ll>>> c(ptr, vector<pair<int, ll>>(0));
    for(int i = 0; i < s; i++){
        if(type[i] == 1) {
            c[source].push_back({stateID[i], 1});
        }
        else if(type[i] == 2){
            c[stateID[i]].push_back({sink, 1});
        }
    }
    for(int i = 0; i < t; i++){
        for(int j = 0; j < tarr[i].size(); j++){
            int ind = tarr[i][j];
            c[stateID[ind]].push_back({tinID[i], 1});
            c[toutID[i]].push_back({stateID[ind], 1});
        }
        c[tinID[i]].push_back({toutID[i], 1});
    }
    cout << dinic(ptr, c, source, sink) << "\n";
    
    return 0;
}
