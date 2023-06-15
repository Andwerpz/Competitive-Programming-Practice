#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSES - 1678

//the problem is pretty much just asking us to find a cycle. 

//we can just do dfs using a stack, and only visiting each node once. If the current node can travel
//to another node that is currently on the dfs stack, then we know we have a cycle. 

//the crucial observation is that we only have to visit each node once. Note that if a node is part of a cycle, 
//then a dfs from that node will always reveal that cycle. 

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
    stack<int> s;
    vector<bool> v(n, false);
    vector<int> ind(n, 0);
    for(int i = 0; i < n; i++){
        if(v[i]){
            continue;
        }
        s = stack<int>();
        set<int> con;
        s.push(i);
        con.insert(i);
        v[i] = true;
        bool found = false;
        while(s.size() != 0) {
            int cur = s.top();
            //cout << "CUR : " << cur << "\n";
            int nextInd = ind[cur];
            while(nextInd < c[cur].size() && v[c[cur][nextInd]] == true && con.find(c[cur][nextInd]) == con.end()) {
                ind[cur] ++;
                nextInd ++;
            }
            if(nextInd == c[cur].size()) {
                //cout << "NO LOOP : " << cur << "\n";
                s.pop();
                con.erase(cur);
            }
            else {
                ind[cur] ++;
                int next = c[cur][nextInd];
                s.push(next);
                if(con.find(next) != con.end()) {
                    //cout << "FOUND LOOP : " << next << "\n";
                    found = true;
                    break;
                }
                con.insert(next);
                v[next] = true;
                //cout << "VISIT : " << next << "\n";
            }
        }
        //cout << "EXIT LOOP\n";
        if(found) {
            break;
        }
    }
    if(s.size() == 0){
        cout << "IMPOSSIBLE";
        return 0;
    }
    set<int> st;
    vector<int> ans(0);
    while(st.find(s.top()) == st.end()) {
        int next = s.top();
        s.pop();
        ans.push_back(next);
        st.insert(next);
    }
    ans.push_back(s.top());
    reverse(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] + 1 << " \n"[i == ans.size() - 1];
    }
    
    return 0;
}
