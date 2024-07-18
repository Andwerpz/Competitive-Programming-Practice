#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

#include "stronglyconnectedcomponent.cpp"

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
