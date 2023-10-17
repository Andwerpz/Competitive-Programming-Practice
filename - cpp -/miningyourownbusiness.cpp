#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2011 - H

//let's first find all of the articulation points of the graph. Note that if an articulation point
//collapses, then the graph will always become split, so we'll at least need an escape vent in each of the
//connected components that are created. 

//Now, let's say that somehow all of the articulation points collapsed. Do we need an escape path in all
//of the resulting connected components? The answer is no, and here is why; if a connected component touches
//two or more articulation points, then we do not need an escape in that component. Since only one articulation
//point can collapse at a time, anyone within that connected component can just go to another connected component
//to escape. 

//thinking about it a little more, you can see that if a connected component only touches 1 articulation point, 
//you must put an escape route in, because if that one articulation point collapses, then it's cut off from
//the rest of the graph. 

//one edge case is where there are no articulation points in the graph. In that case, you just put 2 escapes
//anywhere in the graph. 

vector<bool> find_articulation_points(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    vector<int> tin(n, -1);
    vector<int> low(n, -1);
    vector<bool> is_articulation_point(n, false);
    int timer = 0;
    function<void(int, int)> dfs = [&visited, &tin, &low, &is_articulation_point, &timer, &adj, &dfs](int v, int p) -> void {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        int children=0;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] >= tin[v] && p!=-1)
                    is_articulation_point[v] = true;
                ++children;
            }
        }
        if(p == -1 && children > 1)
            is_articulation_point[v] = true;
    };
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs (i, -1);
    }
    return is_articulation_point;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int caseno = 0;
    while(n != 0){
        caseno ++;
        cout << "Case " << caseno << ": ";
        vector<vector<int>> c(n + 1, vector<int>(0));
        for(int i = 0; i < n; i++){
            int s, t;
            cin >> s >> t;
            s --;
            t --;
            c[s].push_back(t);
            c[t].push_back(s);
        }
        vector<bool> is_at = find_articulation_points(n + 1, c);
        int nr_escape = 0;
        ll nr_comb = 1;
        vector<bool> v(n + 1, false);
        for(int i = 0; i < n + 1; i++){
            if(is_at[i]){
                continue;
            }
            if(v[i]){
                continue;
            }
            v[i] = true;
            stack<int> s;
            s.push(i);
            set<int> t_at;
            int nr_v = 0;
            while(s.size()) {
                int cur = s.top();
                s.pop();
                nr_v ++;
                for(int j = 0; j < c[cur].size(); j++){
                    int next = c[cur][j];
                    if(is_at[next]) {
                        t_at.insert(next);
                        continue;
                    }
                    if(v[next]) {
                        continue;
                    }
                    v[next] = true;
                    s.push(next);
                }
            }
            if(t_at.size() == 1) {
                nr_escape ++;
                nr_comb *= (ll) nr_v;
            }
        }
        if(nr_escape == 0){
            nr_escape = 2;
            ll nr_junctions = 0;
            for(int i = 0; i < n + 1; i++){
                if(c[i].size() != 0){
                    nr_junctions ++;
                }
            }
            nr_comb = (ll) nr_junctions * (ll) (nr_junctions - 1) / 2ll;
        }
        cout << nr_escape << " " << nr_comb << "\n";
        cin >> n;
    }
    
    return 0;
}
