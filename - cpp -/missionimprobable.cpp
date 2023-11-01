#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2017 - C

ll dinic(ll n, vector<vector<pair<ll, ll>>> c, ll source, ll sink) {
    ll ans = 0;
    //redo organization of edges
    vector<pair<ll, ll>> edges(0);
    vector<vector<ll>> adj(n, vector<ll>(0));
    ll m = 0;
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < c[i].size(); j++){
            ll u = i;
            ll v = c[i][j].first;
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
        vector<ll> level(n, -1);
        queue<ll> q;
        vector<bool> v(n, false);
        v[source] = true;
        q.push(source);
        level[source] = 0;
        while(q.size() != 0){
            ll cur = q.front();
            q.pop();
            for(ll i = 0; i < adj[cur].size(); i++) {
                ll nEdge = adj[cur][i];
                ll next = edges[nEdge].first;
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
            stack<ll> s;
            s.push(source);
            stack<ll> est;
            stack<ll> ist;
            ist.push(0);
            while(s.size() != 0){
                ll cur = s.top();
                if(cur == sink) {   
                    //we've found path from source to sink
                    break;
                }
                bool foundNext = false;
                for(ll i = ist.top(); i < adj[cur].size(); i++){
                    ll nEdge = adj[cur][i];
                    ll next = edges[nEdge].first;
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
                vector<ll> path(est.size(), 0);
                for(ll i = 0; i < path.size(); i++){
                    path[i] = est.top();
                    est.pop();
                    bn = min(bn, edges[path[i]].second);
                }
                for(ll i = 0; i < path.size(); i++){
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
    
    ll r, c;
    cin >> r >> c;
    vector<vector<ll>> g(r, vector<ll>(c, 0));
    for(ll i = 0; i < r; i++){
        for(ll j = 0; j < c; j++){
            cin >> g[i][j];
        }
    }
    vector<ll> r_max(r, 0);
    vector<ll> c_max(c, 0);
    for(ll i = 0; i < r; i++){
        for(ll j = 0; j < c; j++){
            r_max[i] = max(r_max[i], g[i][j]);
        }
    }
    for(ll i = 0; i < c; i++){
        for(ll j = 0; j < r; j++){
            c_max[i] = max(c_max[i], g[j][i]);
        }
    }
    vector<bool> r_pair(r, false);
    vector<bool> c_pair(c, false);
    set<ll> order;
    for(ll i = 0; i < r; i++){
        order.insert(r_max[i]);
    }
    for(ll i = 0; i < c; i++){
        order.insert(c_max[i]);
    }
    ll new_boxes = 0;
    ll nr_stacks = 0;
    for(auto next_nr = order.rbegin(); next_nr != order.rend(); next_nr++){
        ll next = *next_nr;
        if(next == 0){
            continue;
        }
        ll ptr = 0;
        ll ssource = ptr ++;
        ll ssink = ptr ++;
        vector<ll> r_ind(0);
        vector<ll> c_ind(0);
        vector<ll> r_nodes(0);
        vector<ll> c_nodes(0);
        for(ll i = 0; i < r; i++){
            if(r_max[i] != next) {
                continue;
            }
            r_nodes.push_back(ptr ++);
            r_ind.push_back(i);
        }
        for(ll i = 0; i < c; i++){
            if(c_max[i] != next) {
                continue;
            }
            c_nodes.push_back(ptr ++);
            c_ind.push_back(i);
        }
        vector<vector<pair<ll, ll>>> c(ptr, vector<pair<ll, ll>>(0));
        //source to r_nodes
        for(ll i = 0; i < r_nodes.size(); i++){
            c[ssource].push_back({r_nodes[i], 1});
        }
        //r_nodes to c_nodes
        for(ll i = 0; i < r_nodes.size(); i++){
            for(ll j = 0; j < c_nodes.size(); j++){
                ll i_ind = r_ind[i];
                ll j_ind = c_ind[j];
                if(g[i_ind][j_ind] == 0){
                    continue;
                }
                c[r_nodes[i]].push_back({c_nodes[j], 1});
            }
        }
        //c_nodes to source
        for(ll i = 0; i < c_nodes.size(); i++){
            c[c_nodes[i]].push_back({ssink, 1});
        }
        ll nr_pairs = dinic(ptr, c, ssource, ssink);
        ll nr_boxes = r_nodes.size() + c_nodes.size() - nr_pairs;
        new_boxes += nr_boxes * next;
        nr_stacks += nr_boxes;
        //cout << "VAL : " << next << " " << nr_pairs << " " << nr_boxes << "\n";
    }
    // cout << "RMAX : " << "\n";
    // for(ll i = 0; i < r; i++){
    //     cout << r_max[i] << " ";
    // }
    // cout << "\n";
    // cout << "CMAX : " << "\n";
    // for(ll i = 0; i < c; i++){
    //     cout << c_max[i] << " ";
    // }
    // cout << "\n";
    ll tot_boxes = 0;
    ll nr_nonzero = 0;
    for(ll i = 0; i < r; i++){
        for(ll j = 0; j < c; j++){
            if(g[i][j] != 0){
                nr_nonzero ++;
            }
            tot_boxes += g[i][j];
        }
    }
    new_boxes += nr_nonzero - nr_stacks;
    //cout << "BOXES : " << tot_boxes << " " << new_boxes << "\n";
    cout << tot_boxes - new_boxes << "\n";
    
    return 0;
}
