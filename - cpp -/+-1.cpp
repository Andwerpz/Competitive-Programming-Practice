#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1971H

//notice that 2SAT works here. If we replace 1 and -1 with true and false, then we want at least 2 values in every
//column to be true. Equivalently, we can say that there can be at most one false element, and for 3 elements, 
//it's equivalent to say that for every pair of elements, at most 1 can be false. 
//If a, b, c are the values in the column, then (a || b) && (b || c) && (c || a) works.

vector<vector<int>> find_scc(int n, vector<vector<int>>& adj) {
    vector<vector<int>> adj_rev(n, vector<int>(0));
    vector<bool> used(n, false);
    vector<int> order(0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adj[i].size(); j++){
            adj_rev[adj[i][j]].push_back(i);
        }
    }
    function<void(int)> dfs1 = [&used, &adj, &order, &dfs1](int v) -> void {
        used[v] = true;
        for (auto u : adj[v]) {
            if (!used[u]) {
                dfs1(u);
            }
        }
        order.push_back(v);
    };
    for(int i = 0; i < n; i++){
        if(used[i]) {
            continue;
        }
        dfs1(i);
    }
    fill(used.begin(), used.end(), false);
    reverse(order.begin(), order.end());
    function<void(int, vector<int>&)> dfs2 = [&used, &adj_rev, &dfs2](int v, vector<int>& component) -> void {
        used[v] = true;
        component.push_back(v);
        for (auto u : adj_rev[v]) {
            if (!used[u]) {
                dfs2(u, component);
            }
        }
    };
    vector<vector<int>> ans(0);
    for(int i = 0; i < n; i++){
        if(used[order[i]]){
            continue;
        }
        vector<int> component(0);
        dfs2(order[i], component);
        ans.push_back(component);
    }
    return ans;
}

struct TSAT {
    int n;
    vector<vector<int>> node_id; //{false, true}
    vector<vector<int>> c;

    TSAT(int n) {
        this->n = n;

        int ptr = 0;
        this->node_id = vector<vector<int>>(n, {0, 0});
        for(int i = 0; i < n; i++){
            node_id[i][0] = ptr ++;
            node_id[i][1] = ptr ++;
        }

        this->c = vector<vector<int>>(n * 2, vector<int>(0));
    }

    //clears all implications
    void clear() {
        this->c = vector<vector<int>>(n * 2, vector<int>(0));
    }

    //a being a_state implies b being b_state
    void imply(int a, bool a_state, int b, bool b_state) {
        int a_id = node_id[a][a_state];
        int b_id = node_id[b][b_state];
        c[a_id].push_back(b_id);            //positive
        c[b_id ^ 1].push_back(a_id ^ 1);    //contrapositive
    }

    //forces a to be state
    void set(int a, int state) {
        imply(a, !state, a, state);         //if a is !state, then we have a contradiction, so a must be state. 
    }

    //at least one of a has to be a_state or b has to be b_state
    void addOR(int a, bool a_state, int b, bool b_state) {
        imply(a, !a_state, b, b_state);     //if a is not good, then b has to be
    }

    //exactly one of a has to be a_state or b has to be b_state
    void addXOR(int a, bool a_state, int b, bool b_state) {
        imply(a, !a_state, b, b_state);     //normal or
        imply(a, a_state, b, !b_state);     //if a is good, then b can't be
    }

    //either both a and b are good, or both a and b are not good
    void addXNOR(int a, bool a_state, int b, bool b_state) {
        imply(a, a_state, b, b_state);      //if a is good, then b has to be good
        imply(b, b_state, a, a_state);      //if b is good, then a has to be good
    }

    //a and b both have to be good
    //equivalent to set(a, a_state); set(b, b_state);
    void addAND(int a, bool a_state, int b, bool b_state) {
        imply(a, a_state, b, b_state);      //if a is good, then b has to be good
        imply(b, b_state, a, a_state);      //if b is good, then a has to be good
        set(a, a_state);                    //make sure that a is good
    }

    //if a solution exists, returns a possible configuration of the variables. 
    //otherwise, returns an empty vector
    vector<bool> generateSolution() {
        //first, split into sccs. 
        vector<vector<int>> scc = find_scc(n * 2, c);
        //check for contradictions, eg if a and !a are in the same scc
        vector<int> node_scc(n * 2);
        for(int i = 0; i < scc.size(); i++){
            for(int j = 0; j < scc[i].size(); j++){
                int id = scc[i][j];
                node_scc[id] = i;
            }
        }
        for(int i = 0; i < n; i++){
            if(node_scc[i * 2 + 0] == node_scc[i * 2 + 1]){
                return {};
            }
        }
        //otherwise, a solution always exists
        vector<bool> v(n, false);
        vector<bool> ans(n, false);
        //toposort scc
        vector<vector<int>> scc_c(scc.size(), vector<int>(0));
        for(int i = 0; i < node_scc.size(); i++){
            int cur = i;
            int cur_scc = node_scc[i];
            for(int j = 0; j < this->c[cur].size(); j++){
                int next = this->c[cur][j];
                int next_scc = node_scc[next];
                if(next_scc != cur_scc) {
                    scc_c[cur_scc].push_back(next_scc);
                }
            }
        }
        vector<int> scc_indeg(scc.size(), 0);
        for(int i = 0; i < scc_c.size(); i++){
            for(int j = 0; j < scc_c[i].size(); j++){
                int next_scc = scc_c[i][j];
                scc_indeg[next_scc] ++;
            }
        }
        queue<int> q;
        for(int i = 0; i < scc_indeg.size(); i++){
            if(scc_indeg[i] == 0){
                q.push(i);
            }
        }
        vector<int> toporder;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            toporder.push_back(cur);
            for(int i = 0; i < scc_c[cur].size(); i++){
                int next = scc_c[cur][i];
                scc_indeg[next] --;
                if(scc_indeg[next] == 0){
                    q.push(next);
                }
            }
        }
        //assign the answers in reverse topological order
        for(int i = toporder.size() - 1; i >= 0; i--){
            int cur_scc = toporder[i];
            for(int j = 0; j < scc[cur_scc].size(); j++){
                int cur = scc[cur_scc][j];
                bool state = cur % 2;
                cur /= 2;
                if(v[cur]) {
                    break;
                }
                v[cur] = true;
                ans[cur] = state;
            }
        }
        return ans;
    }

    bool solutionExists() {
        return generateSolution().size() != 0;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        TSAT sat(n);
        vvi g(3, vi(n, 0));
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < n; j++){
                cin >> g[i][j];
            }
        }
        for(int i = 0; i < n; i++){
            vi ind(3); vb state(3);
            for(int j = 0; j < 3; j++){
                state[j] = g[j][i] > 0;
                ind[j] = abs(g[j][i]) - 1;
            }
            sat.addOR(ind[0], state[0], ind[1], state[1]);
            sat.addOR(ind[1], state[1], ind[2], state[2]);
            sat.addOR(ind[2], state[2], ind[0], state[0]);
        }
        cout << (sat.solutionExists()? "YES" : "NO") << "\n";
    }
    
    return 0;
}