#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2019 E

//we can solve every connected component seperately, so from now on, we'll assume the graph is one connected component. 

//if the graph does not have any cycles, then the graph is a tree. In this case, we need to put the signs on all of the leaf nodes.

//if the graph does have cycles, then we can mark all the nodes that are in a cycle. Then, if a node that is in a cycle is adjacent 
//to a node that is not in any cycles, we should put a sign on the edge. 

vector<bool> cycle;
vector<bool> v;

vector<int> group;

vector<vector<int>> c;

//return true if it is a dead end
bool dfs(int cur, int p, vector<int>& st, set<int>& s) {
    //cout << "CUR : " << cur << endl;
    s.insert(cur);
    st.push_back(cur);
    group.push_back(cur);
    v[cur] = true;
    bool isDeadEnd = true;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            //cout << "NEXT IS PARENT : " << next << "\n";
            continue;
        }
        if(v[next]) {
            //cout << "NEXT IS VISITED : " << next << "\n";
            isDeadEnd = false;
            continue;
        }
        isDeadEnd &= dfs(next, cur, st, s);
    }   
    s.erase(cur);
    st.pop_back();
    //cout << "IS DEAD END : " << cur << " " << isDeadEnd << "\n";
    cycle[cur] = !isDeadEnd;
    return isDeadEnd;
}

int dfs_cycle(int cur, int p, vector<int>& st, set<int>& s) {
    //cout << cur << endl;
    s.insert(cur);
    st.push_back(cur);
    v[cur] = true;
    bool hasCycle = false;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        //cout << "NEXT : " << next << endl;
        if(s.find(next) != s.end()) {
            return next;
        }
        if(v[next]) {
            continue;
        }
        int cans = dfs_cycle(next, cur, st, s);
        if(cans != -1){
            return cans;
        }
    }   
    s.erase(cur);
    st.pop_back();
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m, {0, 0});
    c = vector<vector<int>>(n, vector<int>(0));
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
        edges[i] = {a, b};
    }
    cycle = vector<bool>(n, false);
    v = vector<bool>(n, false);
    vector<pair<int, int>> ans(0);
    for(int i = 0; i < n; i++){
        if(v[i] ){
            continue;
        }
        vector<int> st(0);
        set<int> s;
        group = vector<int>(0);
        bool isDeadEnd = dfs(i, -1, st, s);
        if(isDeadEnd) {
            for(int j = 0; j < group.size(); j++){
                int cur = group[j];
                if(c[cur].size() != 1) {
                    continue;
                }
                ans.push_back({cur + 1, c[cur][0] + 1});
            }
            continue;
        }
        {
            for(int j = 0; j < group.size(); j++){
                v[group[j]] = false;
            }
        }
        int startInd = dfs_cycle(i, -1, st, s);
        //cout << "START IND : " << startInd << "\n";
        st.clear();
        s.clear();
        {
            for(int j = 0; j < group.size(); j++){
                v[group[j]] = false;
                cycle[group[j]] = false;
            }
        }
        dfs(startInd, -1, st, s);
    }
    // for(int i = 0; i < n; i++){
    //     cout << cycle[i] << " ";
    // }
    // cout << "\n";
    for(int i = 0; i < m; i++){
        int a = edges[i].first;
        int b = edges[i].second;
        if(cycle[a] ^ cycle[b]) {
            if(cycle[b]){
                swap(a, b);
            }
            ans.push_back({a + 1, b + 1});
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    
    return 0;
}
